#include "Common.h"
#include "Policies/SingletonImp.h"
#include "PlayerBotMgr.h"
#include "ObjectMgr.h"
#include "World.h"
#include "WorldSession.h"
#include "AccountMgr.h"
#include "Config/Config.h"
#include "Chat.h"
#include "Player.h"
#include "Group.h"
#include "PlayerBotAI.h"
#include "PartyBotAI.h"
#include "BattleBotAI.h"
#include "BattleBotWaypoints.h"
#include "Language.h"
#include "Spell.h"

INSTANTIATE_SINGLETON_1(PlayerBotMgr);


PlayerBotMgr::PlayerBotMgr()
{
    m_totalChance = 0;
    m_maxAccountId = 0;

    // Config
    m_confMinRandomBots         = 3;
    m_confMaxRandomBots         = 10;
    m_confRandomBotsRefresh     = 60000;
    m_confUpdateDiff            = 10000;
    m_enableRandomBots          = false;
    m_confDebug                 = false;

    // Time
    m_elapsedTime = 0;
    m_lastBotsRefresh = 0;
    m_lastUpdate = 0;
}

PlayerBotMgr::~PlayerBotMgr()
{

}

void PlayerBotMgr::LoadConfig()
{
    m_enableRandomBots = sConfig.GetBoolDefault("RandomBot.Enable", false);
    m_confMinRandomBots = sConfig.GetIntDefault("RandomBot.MinBots", 3);
    m_confMaxRandomBots = sConfig.GetIntDefault("RandomBot.MaxBots", 10);
    m_confRandomBotsRefresh = sConfig.GetIntDefault("RandomBot.Refresh", 60000);
    m_confDebug = sConfig.GetBoolDefault("PlayerBot.Debug", false);
    m_confUpdateDiff = sConfig.GetIntDefault("PlayerBot.UpdateMs", 10000);

    if (!sWorld.getConfig(CONFIG_BOOL_FORCE_LOGOUT_DELAY))
        m_tempBots.clear();
}

void PlayerBotMgr::Load()
{
    // 1- Clean
    DeleteAll();
    m_bots.clear();
    m_tempBots.clear();
    m_totalChance = 0;

    // 2- Configuration
    LoadConfig();

    // 3- Load usable account ID
    QueryResult* result = LoginDatabase.PQuery(
                              "SELECT MAX(`id`)"
                              " FROM `account`");
    if (!result)
    {
        sLog.outError("Playerbot: unable to load max account id.");
        return;
    }
    Field* fields = result->Fetch();
    m_maxAccountId = fields[0].GetUInt32() + 10000;
    delete result;

    // 4- LoadFromDB
    sLog.outString(">> [PlayerBotMgr] Loading Bots ...");
    result = CharacterDatabase.PQuery(
                 "SELECT char_guid, chance, ai"
                 " FROM playerbot");
    if (!result)
        sLog.outString("Table `playerbot` is empty.");
    else
    {
        do
        {
            fields = result->Fetch();
            uint32 guid = fields[0].GetUInt32();
            uint32 acc = GenBotAccountId();
            uint32 chance = fields[1].GetUInt32();

            PlayerBotEntry* entry = new PlayerBotEntry(guid,
                    acc, chance);
            entry->ai = CreatePlayerBotAI(fields[2].GetCppString());
            entry->ai->botEntry = entry;
            if (!sObjectMgr.GetPlayerNameByGUID(guid, entry->name))
                entry->name = "<Unknown>";
            entry->ai->OnBotEntryLoad(entry);
            m_bots[entry->playerGUID] = entry;
            m_totalChance += chance;
        }
        while (result->NextRow());
        delete result;
        sLog.outString("%u bots charges", m_bots.size());
    }

    // 5- Check config/DB
    if (m_confMinRandomBots >= m_bots.size() && !m_bots.empty())
        m_confMinRandomBots = m_bots.size() - 1;
    if (m_confMaxRandomBots > m_bots.size())
        m_confMaxRandomBots = m_bots.size();
    if (m_confMaxRandomBots <= m_confMinRandomBots)
        m_confMaxRandomBots = m_confMinRandomBots + 1;

    // 6- Start initial bots
    if (m_enableRandomBots)
    {
        for (uint32 i = 0; i < m_confMinRandomBots; i++)
            AddRandomBot();
    }

    // 7- Fill stats info
    m_stats.confMaxOnline = m_confMaxRandomBots;
    m_stats.confMinOnline = m_confMinRandomBots;
    m_stats.totalBots = m_bots.size();
    m_stats.confRandomBotsRefresh = m_confRandomBotsRefresh;
    m_stats.confUpdateDiff = m_confUpdateDiff;

    // 8- Show stats if debug
    if (m_confDebug)
    {
        sLog.outString("[PlayerBotMgr] Between %u and %u bots online", m_confMinRandomBots, m_confMaxRandomBots);
        sLog.outString("[PlayerBotMgr] %u now loading", m_stats.loadingCount);
    }
}

void PlayerBotMgr::DeleteAll()
{
    m_stats.onlineCount = 0;
    m_stats.loadingCount = 0;

    std::map<uint32, PlayerBotEntry*>::iterator i;
    for (i = m_bots.begin(); i != m_bots.end(); i++)
    {
        if (i->second->state != PB_STATE_OFFLINE)
        {
            OnBotLogout(i->second);
            m_totalChance += i->second->chance;
        }
    }
    m_tempBots.clear();

    if (m_confDebug)
        sLog.outString("[PlayerBotMgr] Deleting all bots [OK]");
}

void PlayerBotMgr::OnBotLogin(PlayerBotEntry *e)
{
    e->state = PB_STATE_ONLINE;
    if (m_confDebug)
        sLog.outString("[PlayerBot][Login]  '%s' GUID:%u Acc:%u", e->name.c_str(), e->playerGUID, e->accountId);
}
void PlayerBotMgr::OnBotLogout(PlayerBotEntry *e)
{
    e->state = PB_STATE_OFFLINE;
    if (m_confDebug)
        sLog.outString("[PlayerBot][Logout] '%s' GUID:%u Acc:%u", e->name.c_str(), e->playerGUID, e->accountId);
}

void PlayerBotMgr::OnPlayerInWorld(Player* player)
{
    if (PlayerBotEntry* e = player->GetSession()->GetBot())
    {
        player->SetAI(e->ai);
        e->ai->SetPlayer(player);
        e->ai->OnPlayerLogin();
    }
}

PlayerBotEntry* PlayerBotMgr::GetBotWithName(std::string name)
{
    for (const auto& itr : m_bots)
    {
        if (itr.second->name == name)
            return itr.second;
    }

    return nullptr;
}

void PlayerBotMgr::Update(uint32 diff)
{
    // Temporary bots.
    std::map<uint32, uint32>::iterator it;
    for (it = m_tempBots.begin(); it != m_tempBots.end(); ++it)
    {
        if (it->second < diff)
            it->second = 0;
        else
            it->second -= diff;
    }
    it = m_tempBots.begin();
    while (it != m_tempBots.end())
    {
        if (!it->second)
        {
            // Update of "chatBot" too.
            for (std::map<uint32, PlayerBotEntry*>::iterator iter = m_bots.begin(); iter != m_bots.end(); ++iter)
                if (iter->second->accountId == it->first)
                {
                    iter->second->state = PB_STATE_OFFLINE; // Will get logged out at next WorldSession::Update call
                    m_bots.erase(iter);
                    break;
                }
            m_tempBots.erase(it);
            it = m_tempBots.begin();
        }
        else
            ++it;
    }

    m_elapsedTime += diff;
    if (!((m_elapsedTime - m_lastUpdate) > m_confUpdateDiff))
        return; // No need to update
    m_lastUpdate = m_elapsedTime;

    std::map<uint32, PlayerBotEntry*>::iterator iter;
    for (iter = m_bots.begin(); iter != m_bots.end(); ++iter)
    {
        if (!m_enableRandomBots && !iter->second->customBot)
            continue;

        if (iter->second->state == PB_STATE_ONLINE)
        {
            if (!iter->second->m_pendingResponses.empty() &&
                iter->second->ai && iter->second->ai->me)
            {
                std::vector<uint16> pendingResponses = iter->second->m_pendingResponses;
                iter->second->m_pendingResponses.clear();
                for (const auto opcode : pendingResponses)
                {
                    iter->second->ai->SendFakePacket(opcode);
                }
            }

            if (iter->second->requestRemoval)
            {
                if (iter->second->ai && iter->second->ai->me)
                    iter->second->ai->me->RemoveFromGroup();

                DeleteBot(iter);

                if (WorldSession* sess = sWorld.FindSession(iter->second->accountId))
                    sess->LogoutPlayer(false);

                iter->second->requestRemoval = false;
                continue;
            }
        }

        // Connection of pending bots
        if (iter->second->state != PB_STATE_LOADING)
            continue;

        WorldSession* sess = sWorld.FindSession(iter->second->accountId);

        if (!sess)
        {
            // This may happen : just wait for the World to add the session.
            //sLog.outString("/!\\ PlayerBot in queue but Session not in World ... Account : %u, GUID : %u", iter->second->accountId, iter->second->playerGUID);
            continue;
        }
        if (iter->second->ai->OnSessionLoaded(iter->second, sess))
        {
            OnBotLogin(iter->second);
            m_stats.loadingCount--;

            if (iter->second->isChatBot)
                m_stats.onlineChat++;
            else
                m_stats.onlineCount++;
        }
        else
        {
            sLog.outError("PLAYERBOT: Unable to load session id %u", iter->second->accountId);
            DeleteBot(iter);
        }
    }

    if (!m_enableRandomBots)
        return;

    uint32 updatesCount = (m_elapsedTime - m_lastBotsRefresh) / m_confRandomBotsRefresh;
    for (uint32 i = 0; i < updatesCount; ++i)
    {
        AddOrRemoveBot();
        m_lastBotsRefresh += m_confRandomBotsRefresh;
    }
}

/*
Toutes les X minutes, ajoute ou enleve un bot.
*/
bool PlayerBotMgr::AddOrRemoveBot()
{
    uint32 alea = urand(m_confMinRandomBots, m_confMaxRandomBots);
    /*
    10 --- --- --- --- --- --- --- --- --- --- 20 bots
                NumActuel
    [alea ici : remove    ][    ici, add    ]
    */
    if (alea > m_stats.onlineCount)
        return AddRandomBot();
    else
        return DeleteRandomBot();

}

bool PlayerBotMgr::AddBot(PlayerBotAI* ai)
{
    // Find a correct accountid ?
    PlayerBotEntry* e = new PlayerBotEntry();
    e->ai = ai;
    e->accountId = GenBotAccountId();
    e->playerGUID = sObjectMgr.GeneratePlayerLowGuid();
    e->customBot = true;
    ai->botEntry = e;
    m_bots[e->playerGUID] = e;
    return AddBot(e->playerGUID, false);
}

bool PlayerBotMgr::AddBot(uint32 playerGUID, bool chatBot)
{
    uint32 accountId = 0;
    PlayerBotEntry *e = nullptr;
    std::map<uint32, PlayerBotEntry*>::iterator iter = m_bots.find(playerGUID);
    if (iter == m_bots.end())
        accountId = sObjectMgr.GetPlayerAccountIdByGUID(playerGUID);
    else
        accountId = iter->second->accountId;
    if (!accountId)
    {
        DETAIL_LOG("Compte du joueur %u introuvable ...", playerGUID);
        return false;
    }

    if (iter != m_bots.end())
        e = iter->second;
    else
    {
        DETAIL_LOG("Adding temporary PlayerBot.");
        e = new PlayerBotEntry();
        e->state        = PB_STATE_LOADING;
        e->playerGUID   = playerGUID;
        e->chance       = 10;
        e->accountId    = accountId;
        e->isChatBot    = chatBot;
        e->ai           = new PlayerBotAI(nullptr);
        m_bots[playerGUID] = e;
    }

    e->state = PB_STATE_LOADING;
    WorldSession* session = new WorldSession(accountId, nullptr, sAccountMgr.GetSecurity(accountId), 0, LOCALE_enUS);
    session->SetBot(e);
    sWorld.AddSession(session);
    m_stats.loadingCount++;
    if (chatBot)
        AddTempBot(accountId, 20000);
    return true;
}

bool PlayerBotMgr::AddRandomBot()
{
    uint32 alea = urand(0, m_totalChance);
    std::map<uint32, PlayerBotEntry*>::iterator it;
    bool done = false;
    for (it = m_bots.begin(); it != m_bots.end() && !done; it++)
    {
        if (it->second->state != PB_STATE_OFFLINE)
            continue;
        if (it->second->customBot)
            continue;
        uint32 chance = it->second->chance;

        if (chance >= alea)
        {
            AddBot(it->first);
            done = true;
        }
        alea -= chance;
    }
    return done;
}

void PlayerBotMgr::AddTempBot(uint32 account, uint32 time)
{
    m_tempBots[account] = time;
}

void PlayerBotMgr::RefreshTempBot(uint32 account)
{
    if (m_tempBots.find(account) != m_tempBots.end())
    {
        uint32& delay = m_tempBots[account];
        if (delay < 1000)
            delay = 1000;
    }
}

bool PlayerBotMgr::DeleteBot(uint32 playerGUID)
{
    std::map<uint32, PlayerBotEntry*>::iterator iter = m_bots.find(playerGUID);
    if (iter == m_bots.end())
        return false;

    return DeleteBot(iter);
}

bool PlayerBotMgr::DeleteBot(std::map<uint32, PlayerBotEntry*>::iterator iter)
{
    if (iter->second->state == PB_STATE_LOADING)
        m_stats.loadingCount--;
    else if (iter->second->state == PB_STATE_ONLINE)
        m_stats.onlineCount--;

    OnBotLogout(iter->second);
    return true;
}

bool PlayerBotMgr::DeleteRandomBot()
{
    if (m_stats.onlineCount < 1)
        return false;
    uint32 idDelete = urand(0, m_stats.onlineCount);
    uint32 onlinePassed = 0;
    std::map<uint32, PlayerBotEntry*>::iterator iter;
    for (iter = m_bots.begin(); iter != m_bots.end(); iter++)
    {
        if (!iter->second->customBot && !iter->second->isChatBot && iter->second->state == PB_STATE_ONLINE)
        {
            onlinePassed++;
            if (onlinePassed == idDelete)
            {
                OnBotLogout(iter->second);
                m_stats.onlineCount--;
                return true;
            }
        }
    }
    return false;
}

bool PlayerBotMgr::ForceAccountConnection(WorldSession* sess)
{
    if (sess->GetBot())
        return sess->GetBot()->state != PB_STATE_OFFLINE;

    // Temporary bots.
    return m_tempBots.find(sess->GetAccountId()) != m_tempBots.end();
}

bool PlayerBotMgr::IsPermanentBot(uint32 playerGUID)
{
    std::map<uint32, PlayerBotEntry*>::iterator iter = m_bots.find(playerGUID);
    return iter != m_bots.end();
}

bool PlayerBotMgr::IsChatBot(uint32 playerGuid)
{
    std::map<uint32, PlayerBotEntry*>::iterator iter = m_bots.find(playerGuid);
    return iter != m_bots.end() && iter->second->isChatBot;
}

void PlayerBotMgr::AddAllBots()
{
    std::map<uint32, PlayerBotEntry*>::iterator it;
    for (it = m_bots.begin(); it != m_bots.end(); it++)
    {
        if (!it->second->isChatBot && it->second->state == PB_STATE_OFFLINE)
            AddBot(it->first);
    }
}

bool ChatHandler::HandleBotReloadCommand(char * args)
{
    sPlayerBotMgr.Load();
    SendSysMessage("PlayerBot system reloaded");
    return true;
}

bool ChatHandler::HandleBotAddRandomCommand(char * args)
{
    uint32 count = 1;
    char* sCount = strtok((char*)args, " ");
    if (sCount)
        count = uint32(atoi(sCount));
    for (uint32 i = 0; i < count; ++i)
        sPlayerBotMgr.AddRandomBot();
    PSendSysMessage("%u bots added", count);
    return true;
}

bool ChatHandler::HandleBotStopCommand(char * args)
{
    sPlayerBotMgr.DeleteAll();
    SendSysMessage("Tous les bots ont ete decharges.");
    return true;
}

bool ChatHandler::HandleBotAddAllCommand(char * args)
{
    sPlayerBotMgr.AddAllBots();
    SendSysMessage("Tous les bots ont ete connecte");
    return true;
}

bool ChatHandler::HandleBotAddCommand(char* args)
{
    uint32 guid = 0;
    char *charname = nullptr;
    if (*args)
    {
        charname = strtok((char*)args, " ");
        if (charname && strcmp(charname, "") == 0)
            return false;

        guid = sObjectMgr.GetPlayerGuidByName(charname).GetCounter();
        if (!guid)
        {
            PSendSysMessage("Player not found : '%s'", charname);
            SetSentErrorMessage(true);
            return false;
        }
    }
    if (!guid || !sPlayerBotMgr.AddBot(guid))
    {
        SendSysMessage("[PlayerBotMgr] Unable to load bot.");
        return true;
    }
    PSendSysMessage("[PlayerBotMgr] Bot added : '%s', GUID=%u", charname ? charname : "NULL", guid);
    return true;
}

bool ChatHandler::HandleBotDeleteCommand(char * args)
{
    char *charname = strtok((char*)args, " ");

    if (!charname || strcmp(charname, "") == 0)
    {
        SendSysMessage("Syntaxe : $nomDuJoueur");
        SetSentErrorMessage(true);
        return false;
    }
    uint32 lowGuid = sObjectMgr.GetPlayerGuidByName(charname).GetCounter();
    if (!lowGuid)
    {
        PSendSysMessage("Unable to find player: '%s'", charname);
        SetSentErrorMessage(true);
        return false;
    }
    if (sPlayerBotMgr.DeleteBot(lowGuid))
    {
        PSendSysMessage("Bot %s (GUID:%u) disconnected.", charname, lowGuid);
        return true;
    }
    else
    {
        PSendSysMessage("Bot %s (GUID:%u) : unable to disconnect.", charname, lowGuid);
        SetSentErrorMessage(true);
        return false;
    }
}

bool ChatHandler::HandleBotInfoCommand(char * args)
{
    uint32 online = sWorld.GetActiveSessionCount();

    PlayerBotStats stats = sPlayerBotMgr.GetStats();
    SendSysMessage("-- PlayerBot stats --");
    PSendSysMessage("Min:%u Max:%u Total:%u", stats.confMinOnline, stats.confMaxOnline, stats.totalBots);
    PSendSysMessage("Loading : %u, Online : %u, Chat : %u", stats.loadingCount, stats.onlineCount, stats.onlineChat);
    PSendSysMessage("%up + %ub = %u",
                    (online - stats.onlineCount), stats.onlineCount, online);
    return true;
}

bool ChatHandler::HandleBotStartCommand(char * args)
{
    sPlayerBotMgr.Start();
    return true;
}

//Function: 隨機選擇職業之種族
uint8 SelectRandomRaceForClass(uint8 playerClass, Team playerTeam)
{
    switch (playerClass)
    {
        case CLASS_WARRIOR:
        {
            if (playerTeam == ALLIANCE)
                return PickRandomValue(RACE_HUMAN, RACE_DWARF, RACE_NIGHTELF, RACE_GNOME);
            else
                return PickRandomValue(RACE_ORC, RACE_UNDEAD, RACE_TAUREN, RACE_TROLL);
            break;
        }
        case CLASS_PALADIN:
        {
            return urand(0, 1) ? RACE_HUMAN : RACE_DWARF;
        }
        case CLASS_HUNTER:
        {
            if (playerTeam == ALLIANCE)
                return urand(0, 1) ? RACE_DWARF : RACE_NIGHTELF;
            else
                return PickRandomValue(RACE_ORC, RACE_TAUREN, RACE_TROLL);
            break;
        }
        case CLASS_ROGUE:
        {
            if (playerTeam == ALLIANCE)
                return PickRandomValue(RACE_HUMAN, RACE_DWARF, RACE_NIGHTELF, RACE_GNOME);
            else
                return PickRandomValue(RACE_ORC, RACE_UNDEAD, RACE_TROLL);
            break;
        }
        case CLASS_PRIEST:
        {
            if (playerTeam == ALLIANCE)
                return PickRandomValue(RACE_HUMAN, RACE_DWARF, RACE_NIGHTELF);
            else
                return urand(0, 1) ? RACE_UNDEAD : RACE_TROLL;
            break;
        }
        case CLASS_SHAMAN:
        {
            return PickRandomValue(RACE_ORC, RACE_TAUREN, RACE_TROLL);
        }
        case CLASS_MAGE:
        {
            if (playerTeam == ALLIANCE)
                return urand(0, 1) ? RACE_HUMAN : RACE_GNOME;
            else
                return urand(0, 1) ? RACE_UNDEAD : RACE_TROLL;
            break;
        }
        case CLASS_WARLOCK:
        {
            if (playerTeam == ALLIANCE)
                return urand(0, 1) ? RACE_HUMAN : RACE_GNOME;
            else
                return urand(0, 1) ? RACE_ORC : RACE_UNDEAD;
            break;
        }
        case CLASS_DRUID:
        {
            return playerTeam == ALLIANCE ? RACE_NIGHTELF : RACE_TAUREN;
        }
    }

    return 0;
}

bool ChatHandler::PartyBotAddRequirementCheck(Player const* pPlayer, Player const* pTarget)
{
    if (pPlayer->IsTaxiFlying())
    {
        SendSysMessage("不能在飛行中加入機器人。");
        return false;
    }

    // Spawning bots inside BG will cause server crash on BG end.
    if (pPlayer->InBattleGround())
    {
        SendSysMessage("戰場中不能加入機器人。");
        return false;
    }

    if (pPlayer->GetGroup() && (pPlayer->GetGroup()->IsFull() || sWorld.getConfig(CONFIG_UINT32_PARTY_BOT_MAX_BOTS) &&
        (pPlayer->GetGroup()->GetMembersCount() - 1 >= sWorld.getConfig(CONFIG_UINT32_PARTY_BOT_MAX_BOTS))))
    {
        SendSysMessage("無法再加入更多機器人。隊伍已滿。");
        return false;
    }

    if (Map const* pMap = pPlayer->GetMap())
    {
        if (pMap->IsDungeon() &&
            pMap->GetPlayers().getSize() >= pMap->GetMapEntry()->maxPlayers)
        {
            SendSysMessage("無法再加入更多機器人。團隊已滿。");
            return false;
        }
    }

    if (pTarget && pTarget->GetTeam() != pPlayer->GetTeam())
    {
        SendSysMessage("不能複製敵對陣營人物成機器人。");
        return false;
    }

    // Restrictions when the command is made public to avoid abuse.
    if (GetSession()->GetSecurity() <= SEC_PLAYER && !sWorld.getConfig(CONFIG_BOOL_PARTY_BOT_SKIP_CHECKS))
    {
        if (pPlayer->IsDead())
        {
            SendSysMessage("死亡時不能加入機器人。");
            return false;
        }

        if (pPlayer->IsInCombat())
        {
            SendSysMessage("戰鬥中不能加入機器人。");
            return false;
        }

        if (pPlayer->GetMap()->IsDungeon())
        {
            SendSysMessage("在副本內不能加入機器人。");
            return false;
        }

        // Clone command.
        if (pTarget)
        {
            if (pTarget->IsDead())
            {
                SendSysMessage("不能對複製已死亡的人物。");
                return false;
            }

            if (pTarget->IsInCombat())
            {
                SendSysMessage("不能複製戰鬥中的人物。");
                return false;
            }

            //if (pTarget->GetLevel() > pPlayer->GetLevel() + 10) Prevent player clone higher level bot
			if (pTarget->GetLevel() > pPlayer->GetLevel())
			{
                SendSysMessage("不能對複製高等的人物。");
                return false;
            }
        }
    }

    return true;
}

//Function- partybot add機器人命令
bool ChatHandler::HandlePartyBotAddCommand(char* args)
{
    Player* pPlayer = m_session->GetPlayer();
    if (!pPlayer)
        return false;

    if (!PartyBotAddRequirementCheck(pPlayer, nullptr))
    {
        SetSentErrorMessage(true);
        return false;
    }
	//硬限制玩家在下面的條件下不能呼叫機器人
	if (pPlayer->IsDead())
	{
		SendSysMessage("死亡時不能加入機器人。");
		return false;
	}

	if (pPlayer->IsInCombat())
	{
		SendSysMessage("戰鬥中不能加入機器人。");
		return false;
	}

	/*if (pPlayer->GetMap()->IsDungeon())
	{
		SendSysMessage("在副本內不能加入機器人。");
		return false;
	}*/

    if (!args)
    {
        SendSysMessage("語法錯誤。必須是身分(dps/tank/healer)或職業(warrior/mage..etc)。且敵對陣營職業不可用。");
        SetSentErrorMessage(true);
        return false;
    }

    uint8 botClass = 0;
    uint32 botLevel = pPlayer->GetLevel();  //讀取玩家等級，如沒額外輸入第二參數，預設機器人等級就是玩家等級
	uint32 botGender = urand(0, 1); //加入性別屬性供定義
	CombatBotRoles botRole = ROLE_INVALID;

    if (char* arg1 = ExtractArg(&args)) //判斷參數arg1=玩家輸入命令partbot add後的參數args=職業
    {
        std::string option = arg1;
		if (option == "warrior")
			botClass = CLASS_WARRIOR;
		else if (option == "mwarrior")
			(botClass = CLASS_WARRIOR) && (botRole = ROLE_MELEE_DPS);
        else if (option == "paladin" && pPlayer->GetTeam() == ALLIANCE)
            botClass = CLASS_PALADIN;
		else if (option == "mpaladin" && pPlayer->GetTeam() == ALLIANCE)
			(botClass = CLASS_PALADIN) && (botRole = ROLE_MELEE_DPS);
		else if (option == "hpaladin" && pPlayer->GetTeam() == ALLIANCE)
			(botClass = CLASS_PALADIN) && (botRole = ROLE_HEALER);
		else if (option == "hunter")
            botClass = CLASS_HUNTER;
        else if (option == "rogue")
            botClass = CLASS_ROGUE;
        else if (option == "priest")
            botClass = CLASS_PRIEST;
		else if (option == "rpriest")
			(botClass = CLASS_PRIEST) && (botRole = ROLE_RANGE_DPS);
		else if (option == "hpriest")
			(botClass = CLASS_PRIEST) && (botRole = ROLE_HEALER);
		else if (option == "shaman" && pPlayer->GetTeam() == HORDE)
            botClass = CLASS_SHAMAN;
		else if (option == "mshaman" && pPlayer->GetTeam() == HORDE)
			(botClass = CLASS_SHAMAN) && (botRole = ROLE_MELEE_DPS);
		else if (option == "rshaman" && pPlayer->GetTeam() == HORDE)
			(botClass = CLASS_SHAMAN) && (botRole = ROLE_RANGE_DPS);
		else if (option == "hshaman" && pPlayer->GetTeam() == HORDE)
			(botClass = CLASS_SHAMAN) && (botRole = ROLE_HEALER);
		else if (option == "mage")
            botClass = CLASS_MAGE;
        else if (option == "warlock")
            botClass = CLASS_WARLOCK;
        else if (option == "druid")
            botClass = CLASS_DRUID;
		else if (option == "mdruid")
			(botClass = CLASS_DRUID) && (botRole = ROLE_MELEE_DPS);
		else if (option == "rdruid")
			(botClass = CLASS_DRUID) && (botRole = ROLE_RANGE_DPS);
		else if (option == "hdruid")
			(botClass = CLASS_DRUID) && (botRole = ROLE_HEALER);
		else if (option == "dps")
        {
			if (pPlayer->GetTeam() == ALLIANCE)
				botClass = PickRandomValue(CLASS_WARRIOR, CLASS_HUNTER, CLASS_ROGUE, CLASS_MAGE, CLASS_WARLOCK, CLASS_PALADIN); //聯盟dps randon加入CLASS_PALADIN
			else
				botClass = PickRandomValue(CLASS_WARRIOR, CLASS_HUNTER, CLASS_ROGUE, CLASS_MAGE, CLASS_WARLOCK, CLASS_SHAMAN); //部落dps randon加入CLASS_SHAMAN
			botRole = CombatBotBaseAI::IsMeleeDamageClass(botClass) ? ROLE_MELEE_DPS : ROLE_RANGE_DPS;
        }
        else if (option == "healer")
        {
            std::vector<uint32> dpsClasses = { CLASS_PRIEST, CLASS_DRUID };
            if (pPlayer->GetTeam() == HORDE)
                dpsClasses.push_back(CLASS_SHAMAN);
            else
                dpsClasses.push_back(CLASS_PALADIN);
            botClass = SelectRandomContainerElement(dpsClasses);
            botRole = ROLE_HEALER;
        }
        else if (option == "tank")
        {
            //botClass = CLASS_WARRIOR;
			std::vector<uint32> tankClasses = { CLASS_WARRIOR, CLASS_DRUID };
			if (pPlayer->GetTeam() == ALLIANCE)
				tankClasses.push_back(CLASS_PALADIN); //如果陣營為聯盟則回傳聖騎
			botClass = SelectRandomContainerElement(tankClasses);
			botRole = ROLE_TANK;
        }
		else if (option == "wtank") //防戰
		{
			botClass = CLASS_WARRIOR;
			botRole = ROLE_TANK;
		}
		else if (option == "dtank") //熊坦
		{
			botClass = CLASS_DRUID;
			botRole = ROLE_TANK;
		}
		else if (option == "ptank" && pPlayer->GetTeam() == ALLIANCE) //防騎
		{
			botClass = CLASS_PALADIN;
			botRole = ROLE_TANK;
		}

        //ExtractUInt32(&args, botLevel); //prevent player add level argument禁止使用第二個參數=botlevel
		ExtractUInt32(&args, botGender); //使用第二個參數=botGender
    }

	if (!botClass) //命令沒有輸入職業的話
    {
        SendSysMessage("語法錯誤。必須是類型(如dps/tank/healer)或職業(如warrior/mage)。另外也不能徵召敵對陣營專屬職業");
        SetSentErrorMessage(true);
        return false;
    }

	if (botGender >1)
	{
		SendSysMessage("性別參數必須是0(男)或1(女)");
		SetSentErrorMessage(true);
		return false;
	}

    uint8 botRace = SelectRandomRaceForClass(botClass, pPlayer->GetTeam()); //種族用亂數選擇

    float x, y, z;
    pPlayer->GetNearPoint(pPlayer, x, y, z, 0, 5.0f, frand(0.0f, 6.0f));

    PartyBotAI* ai = new PartyBotAI(pPlayer, nullptr, botRole, botRace, botGender, botClass, botLevel, pPlayer->GetMapId(), pPlayer->GetMap()->GetInstanceId(), x, y, z, pPlayer->GetOrientation());
    if (sPlayerBotMgr.AddBot(ai)) //前面的條件皆通過，執行產生機器人function
        SendSysMessage("加入一位機器人。");
    else
    {
        SendSysMessage("Error spawning bot.");
        SetSentErrorMessage(true);
        return false;
    }

    return true;
}

//Function: 克隆機器人命令
bool ChatHandler::HandlePartyBotCloneCommand(char* args)
{
    Player* pPlayer = m_session->GetPlayer();
    if (!pPlayer)
        return false;

    Player* pTarget = GetSelectedPlayer();
    if (!pTarget)
    {
        SendSysMessage(LANG_NO_CHAR_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (!PartyBotAddRequirementCheck(pPlayer, pTarget))
    {
        SetSentErrorMessage(true);
        return false;
    }

    uint8 botRace = pTarget->GetRace();
    uint8 botClass = pTarget->GetClass();
	uint8 botGender = pTarget->GetGender();

    float x, y, z;
    pPlayer->GetNearPoint(pPlayer, x, y, z, 0, 5.0f, frand(0.0f, 6.0f));

    PartyBotAI* ai = new PartyBotAI(pPlayer, pTarget, ROLE_INVALID, botRace, botGender, botClass, pPlayer->GetLevel(), pPlayer->GetMapId(), pPlayer->GetMap()->GetInstanceId(), x, y, z, pPlayer->GetOrientation());
    if (sPlayerBotMgr.AddBot(ai))
        SendSysMessage("加入一位機器人。");
    else
    {
        SendSysMessage("Error spawning bot.");
        SetSentErrorMessage(true);
        return false;
    }

    return true;
}

//Function: 指定機器人身分命令
bool ChatHandler::HandlePartyBotSetRoleCommand(char* args)
{
    if (!args)
        return false;

    Player* pTarget = GetSelectedPlayer();
    if (!pTarget)
    {
        SendSysMessage(LANG_NO_CHAR_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    CombatBotRoles role = ROLE_INVALID;
    std::string roleStr = args;

    if (roleStr == "tank")
        role = ROLE_TANK;
    else if (roleStr == "dps")
        role = CombatBotBaseAI::IsMeleeDamageClass(pTarget->GetClass()) ? ROLE_MELEE_DPS : ROLE_RANGE_DPS;
    else if (roleStr == "meleedps")
        role = ROLE_MELEE_DPS;
    else if (roleStr == "rangedps")
        role = ROLE_RANGE_DPS;
    else if (roleStr == "healer")
        role = ROLE_HEALER;

    if (role == ROLE_INVALID)
        return false;

    if (pTarget->AI())
    {
		Player* pPlayer = m_session->GetPlayer();
		if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pTarget->AI()))
        {
			if (pTarget->IsDead() || pPlayer->IsDead())
			{
				SendSysMessage("死亡時不能變更身份。");
				return false;
			}

			if (pTarget->IsInCombat() || pPlayer->IsInCombat())
			{
				SendSysMessage("戰鬥中不能變更身份。");
				return false;
			}

			if (pTarget->GetMap()->IsDungeon() || pPlayer->GetMap()->IsDungeon())
			{
				SendSysMessage("在副本內不能變更身份。");
				return false;
			}
			pAI->m_role = role;
            pAI->ResetSpellData();
            pAI->PopulateSpellData();
			pAI->AutoEquipGear(sWorld.getConfig(CONFIG_UINT32_PARTY_BOT_AUTO_EQUIP)); //made bot auto change equipment when it assigned new role
            PSendSysMessage("%s 現在隊伍身分是 %s.", pTarget->GetName(), roleStr.c_str());
            return true;
        }
    }

    SendSysMessage("目標並非機器人。");
    SetSentErrorMessage(true);
    return false;
}

//機器人開始攻擊命令function
bool ChatHandler::HandlePartyBotAttackStartCommand(char* args)
{
    Player* pPlayer = GetSession()->GetPlayer();
    Unit* pTarget = GetSelectedUnit();
    if (!pTarget || (pTarget == pPlayer))
    {
        SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }
    
    Group* pGroup = pPlayer->GetGroup();
    if (!pGroup)
    {
        SendSysMessage("你不在隊伍中。");
        SetSentErrorMessage(true);
        return false;
    }

    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        if (Player* pMember = itr->getSource())
        {
            if (pMember == pPlayer)
                continue;

            if (pMember->AI())
            {
                if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pMember->AI()))
                {
                    if (pMember->IsValidAttackTarget(pTarget))
                        pAI->AttackStart(pTarget);
                }
            }            
        }
    }
    
    PSendSysMessage("全隊機器人開始攻擊目標 %s。", pTarget->GetName());
    return true;
}

bool ChatHandler::HandlePartyBotTankPullCommand(char* args)
{
	Player* pPlayer = GetSession()->GetPlayer();
	Unit* pTarget = GetSelectedUnit();
	if (!pTarget || (pTarget == pPlayer))
	{
		SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
		SetSentErrorMessage(true);
		return false;
	}

	Group* pGroup = pPlayer->GetGroup();
	if (!pGroup)
	{
		SendSysMessage("你不在隊伍中。");
		SetSentErrorMessage(true);
		return false;
	}

	for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
	{
		if (Player* pMember = itr->getSource())
		{
			if (pMember == pPlayer)
				continue;

			if (pMember->AI())
			{
				if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pMember->AI()))
				{
					if (pMember->IsValidAttackTarget(pTarget))
						pAI->TankPull(pTarget);
				}
			}
		}
	}
	//前面若收到回傳true，表示隊伍有坦克且執行了攻擊，則程式繼續往下，使隊伍中其他DPS暫停動作
	uint32 duration = 10 * IN_MILLISECONDS;
/*	if (char* arg1 = ExtractArg(&args)) //如有輸入額外參數=all
	{
		if (!(all = (strcmp(arg1, "all") == 0)) && pause)
			duration = atoi(arg1);

		if (char* arg2 = ExtractArg(&args))
		{
			if (!duration && pause)
				duration = atoi(arg2);
			else if (!all)
				all = strcmp(arg2, "all") == 0;
		}
	}*/
/*
	bool success = false;
	CombatBotRoles botRole = ROLE_INVALID;
	//botRole = CombatBotBaseAI::IsMeleeDamageClass(pMember->GetClass()) ? ROLE_MELEE_DPS : ROLE_RANGE_DPS;
	for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
	{
		if (Player* pMember = itr->getSource())
		{
			if (pMember == pPlayer)
				continue;
			botRole = CombatBotBaseAI::IsMeleeDamageClass(pMember->GetClass()) ? ROLE_MELEE_DPS : ROLE_RANGE_DPS;
			if ( botRole == ROLE_TANK || botRole == ROLE_HEALER)
				continue;
			if (HandlePartyBotDPSPauseApplyHelper(pMember, duration))
				success = true;
		}
	}

	if (success)
	*/
	PSendSysMessage("坦克開怪 %s ，DD們等待%u秒鐘再開打。", pTarget->GetName(), (duration / IN_MILLISECONDS));
	return true;
}

//機器人停止攻擊命令助手function
void StopPartyBotAttackHelper(PartyBotAI* pAI, Player* pBot)
{
    pBot->AttackStop(true);
    pBot->InterruptNonMeleeSpells(false);
    if (!pBot->IsStopped())
        pBot->StopMoving();
    if (pBot->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE)
        pBot->GetMotionMaster()->Clear();
    if (pAI->m_updateTimer.GetExpiry() < 3000)
        pAI->m_updateTimer.Reset(3000);
}

//機係人停止攻擊命令function
bool ChatHandler::HandlePartyBotAttackStopCommand(char* args)
{
    Player* pPlayer = GetSession()->GetPlayer();
    Unit* pTarget = GetSelectedUnit();
    if (!pTarget || (pTarget == pPlayer))
    {
        SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    Group* pGroup = pPlayer->GetGroup();
    if (!pGroup)
    {
        SendSysMessage("你不在隊伍中。");
        SetSentErrorMessage(true);
        return false;
    }

    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        if (Player* pMember = itr->getSource())
        {
            if (pMember == pPlayer)
                continue;

            if (pMember->AI())
            {
                if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pMember->AI()))
                {
                    if (pMember->GetVictim() == pTarget)
                        StopPartyBotAttackHelper(pAI, pMember);
                }
            }
        }
    }

    PSendSysMessage("全隊機器人停止攻擊目標 %s。", pTarget->GetName());
    return true;
}

bool ChatHandler::HandlePartyBotAoECommand(char* args)
{
    Player* pPlayer = GetSession()->GetPlayer();
    Unit* pTarget = GetSelectedUnit();
    if (!pTarget || !pPlayer->IsValidAttackTarget(pTarget, true))
    {
        SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    Group* pGroup = pPlayer->GetGroup();
    if (!pGroup)
    {
        SendSysMessage("你不在隊伍中。");
        SetSentErrorMessage(true);
        return false;
    }

    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        if (Player* pMember = itr->getSource())
        {
            if (pMember == pPlayer)
                continue;

            if (pMember->AI())
            {
                if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pMember->AI()))
                {
                    for (auto const& pSpell : pAI->m_spells.raw.spells)
                    {
                        if (pSpell && pSpell->IsAreaOfEffectSpell() &&
                           !pSpell->IsPositiveSpell() &&
                            pSpell->IsTargetInRange(pMember, pTarget))
                        {
                            if (pMember->GetCurrentSpell(CURRENT_GENERIC_SPELL) &&
                               !pMember->GetCurrentSpell(CURRENT_GENERIC_SPELL)->m_spellInfo->IsAreaOfEffectSpell())
                                pMember->InterruptSpell(CURRENT_GENERIC_SPELL);

                            if (pMember->CastSpell(pTarget, pSpell, false) == SPELL_CAST_OK)
                                break;
                        }
                    }
                }
            }
        }
    }

    PSendSysMessage("全隊機器人使用範圍法術攻擊目標 %s。", pTarget->GetName());
    return true;
}

static std::map<std::string, RaidTargetIcon> raidTargetIcons =
{
    { "star",     RAID_TARGET_ICON_STAR     },
    { "circle",   RAID_TARGET_ICON_CIRCLE   },
    { "diamond",  RAID_TARGET_ICON_DIAMOND  },
    { "triangle", RAID_TARGET_ICON_TRIANGLE },
    { "moon",     RAID_TARGET_ICON_MOON     },
    { "square",   RAID_TARGET_ICON_SQUARE   },
    { "cross",    RAID_TARGET_ICON_CROSS    },
    { "skull",    RAID_TARGET_ICON_SKULL    },
};

bool ChatHandler::HandlePartyBotControlMarkCommand(char* args)
{
    std::string mark = args;
    auto itrMark = raidTargetIcons.find(mark);
    if (itrMark == raidTargetIcons.end())
    {
        SendSysMessage("未知的標記。可使用的標記名稱：star, circle, diamond, triangle, moon, square, cross, skull");
        SetSentErrorMessage(true);
        return false;
    }

    Player* pPlayer = GetSession()->GetPlayer();
    Player* pTarget = GetSelectedPlayer();

    if (pTarget && (pTarget != pPlayer))
    {
        if (pTarget->AI())
        {
            if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pTarget->AI()))
            {
                PSendSysMessage("%s 將控場目標 %s。", pTarget->GetName(), args);
                pAI->m_marksToCC.push_back(itrMark->second);
                return true;
            }
        }
        SendSysMessage("目標並非機器人。");
        SetSentErrorMessage(true);
        return false;
    }

    Group* pGroup = pPlayer->GetGroup();
    if (!pGroup)
    {
        SendSysMessage("你不在隊伍中。");
        SetSentErrorMessage(true);
        return false;
    }

    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        if (Player* pMember = itr->getSource())
        {
            if (pMember == pPlayer)
                continue;

            if (pMember->AI())
            {
                if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pMember->AI()))
                {
                    pAI->m_marksToCC.push_back(itrMark->second);
                }
            }
        }
    }

    PSendSysMessage("全體機器人控場目標 %s。", args);
    return true;
}

bool ChatHandler::HandlePartyBotFocusMarkCommand(char* args)
{
    std::string mark = args;
    auto itrMark = raidTargetIcons.find(mark);
    if (itrMark == raidTargetIcons.end())
    {
        SendSysMessage("未知的標記。可使用的標記名稱：star, circle, diamond, triangle, moon, square, cross, skull");
        SetSentErrorMessage(true);
        return false;
    }

    Player* pPlayer = GetSession()->GetPlayer();
    Player* pTarget = GetSelectedPlayer();

    if (pTarget && (pTarget != pPlayer))
    {
        if (pTarget->AI())
        {
            if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pTarget->AI()))
            {
                PSendSysMessage("%s 專注目標在 %s.", pTarget->GetName(), args);
                pAI->m_marksToFocus.push_back(itrMark->second);
                return true;
            }
        }
        SendSysMessage("目標並非機器人。");
        SetSentErrorMessage(true);
        return false;
    }

    Group* pGroup = pPlayer->GetGroup();
    if (!pGroup)
    {
        SendSysMessage("你不在隊伍中。");
        SetSentErrorMessage(true);
        return false;
    }

    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        if (Player* pMember = itr->getSource())
        {
            if (pMember == pPlayer)
                continue;

            if (pMember->AI())
            {
                if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pMember->AI()))
                {
                    pAI->m_marksToFocus.push_back(itrMark->second);
                }
            }
        }
    }

    PSendSysMessage("全隊機器人專注目標在 %s。", args);
    return true;
}

bool ChatHandler::HandlePartyBotClearMarksCommand(char* args)
{
    Player* pPlayer = GetSession()->GetPlayer();
    Player* pTarget = GetSelectedPlayer();

    if (pTarget && (pTarget != pPlayer))
    {
        if (pTarget->AI())
        {
            if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pTarget->AI()))
            {
                PSendSysMessage("為 %s 清除標記。", pTarget->GetName());
                pAI->m_marksToCC.clear();
                pAI->m_marksToFocus.clear();
                return true;
            }
        }
        SendSysMessage("目標並非機器人。");
        SetSentErrorMessage(true);
        return false;
    }

    Group* pGroup = pPlayer->GetGroup();
    if (!pGroup)
    {
        SendSysMessage("你不在隊伍中。");
        SetSentErrorMessage(true);
        return false;
    }

    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        if (Player* pMember = itr->getSource())
        {
            if (pMember == pPlayer)
                continue;

            if (pMember->AI())
            {
                if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pMember->AI()))
                {
                    pAI->m_marksToCC.clear();
                    pAI->m_marksToFocus.clear();
                }
            }
        }
    }

    SendSysMessage("為全隊機器人清除標記。");
    return true;
}

//機器人回來命令助手function
bool HandlePartyBotComeToMeHelper(Player* pBot, Player* pPlayer)
{
    if (pBot->AI() && pBot->IsAlive() && pBot->IsInMap(pPlayer) && !pBot->HasUnitState(UNIT_STAT_NO_FREE_MOVE))
    {
        if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pBot->AI()))
        {
            if (pBot->GetVictim())
                StopPartyBotAttackHelper(pAI, pBot);

            if (pBot->GetStandState() != UNIT_STAND_STATE_STAND)
                pBot->SetStandState(UNIT_STAND_STATE_STAND);

            pBot->InterruptSpellsWithInterruptFlags(SPELL_INTERRUPT_FLAG_MOVEMENT);
            pBot->MonsterMove(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ());
            return true;
        }
    }

    return false;
}

bool ChatHandler::HandlePartyBotComeToMeCommand(char* args)
{
    Player* pPlayer = GetSession()->GetPlayer();
    Player* pTarget = GetSelectedPlayer();

    bool ok = false;

    if (pTarget && pTarget != pPlayer)
    {
        if (ok = HandlePartyBotComeToMeHelper(pTarget, pPlayer))
            PSendSysMessage("%s 將回到你的位置。", pTarget->GetName());
        else
            PSendSysMessage("%s 非機器人或是無法移動。", pTarget->GetName());
        return ok;
    }
    else if (Group* pGroup = pPlayer->GetGroup())
    {
        bool ok = false;
        for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            if (Player* pMember = itr->getSource())
            {
                if (pMember == pPlayer)
                    continue;

                ok = HandlePartyBotComeToMeHelper(pMember, pPlayer) || ok;
            }
        }

        if (ok)
            SendSysMessage("全隊機器人將回到你的位置。");
        else
            SendSysMessage("隊伍中無機器人或是無法移動。");
        return ok;
    }

    SendSysMessage("你不在隊伍中。");
    SetSentErrorMessage(true);
    return false;
}

bool HandlePartyBotUseGObjectHelper(Player* pTarget, GameObject* pGo)
{
    if (pTarget->AI())
    {
        if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pTarget->AI()))
        {
            if (pTarget->IsWithinDist(pGo, INTERACTION_DISTANCE))
            {
                pGo->Use(pTarget);
                return true;
            }
        }
    }

    return false;
}

//機器人使用物件命令function
bool ChatHandler::HandlePartyBotUseGObjectCommand(char* args)
{
    Player* pPlayer = GetSession()->GetPlayer();
    Player* pTarget = GetSelectedPlayer();

    GameObject* pGo = getSelectedGameObject();
    if (!pGo)
    {
        SendSysMessage(LANG_COMMAND_NOGAMEOBJECTFOUND);
        return false;
    }

    bool ok = false;

    if (pTarget && pTarget != pPlayer)
    {
        if (ok = HandlePartyBotUseGObjectHelper(pTarget, pGo))
            PSendSysMessage("%s 使用此物件。", pTarget->GetName());
        else
            PSendSysMessage("%s 非機器人或物件不在其所及範圍內。", pTarget->GetName());
        return ok;
    }
    else if (Group* pGroup = pPlayer->GetGroup())
    {
        for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            if (Player* pMember = itr->getSource())
                ok = HandlePartyBotUseGObjectHelper(pMember, pGo) || ok;
        }

        if (ok)
            SendSysMessage("全隊機器人使用了範圍可及的物件。");
        else
            SendSysMessage("物件不在機器人所及範圍內。");
        return ok;
    }

    SendSysMessage("你不在隊伍中。");
    SetSentErrorMessage(true);
    return false;
}

//機器人暫定動作應用function
bool HandlePartyBotPauseApplyHelper(Player* pTarget, uint32 duration)
{
    if (pTarget->AI())
    {
        if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pTarget->AI()))
        {
            pAI->m_updateTimer.Reset(duration);

            if (duration)
            {
                pTarget->StopMoving();
                pTarget->GetMotionMaster()->MoveIdle();
            }

            return true;
        }
    }

    return false;
}

//機器人暫停動作命令助手function
bool ChatHandler::HandlePartyBotPauseHelper(char* args, bool pause)
{
    bool all = false;
    uint32 duration = 0;
    if (char* arg1 = ExtractArg(&args)) //如有輸入額外參數=all
    {
        if (!(all = (strcmp(arg1, "all") == 0)) && pause)
            duration = atoi(arg1);

        if (char* arg2 = ExtractArg(&args))
        {
            if (!duration && pause)
                duration = atoi(arg2);
            else if (!all)
                all = strcmp(arg2, "all") == 0;
        }
    }

    if (pause && !duration)
        duration = 5 * MINUTE * IN_MILLISECONDS;

    if (all)
    {
        Player* pPlayer = GetSession()->GetPlayer();
        Group* pGroup = pPlayer->GetGroup();
        if (!pGroup)
        {
            SendSysMessage("你不在隊伍中。");
            SetSentErrorMessage(true);
            return false;
        }

        bool success = false;
        for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            if (Player* pMember = itr->getSource())
            {
                if (pMember == pPlayer)
                    continue;

                if (HandlePartyBotPauseApplyHelper(pMember, duration))
                    success = true;
            }
        }

        if (success)
        {
            if (pause)
                PSendSysMessage("全隊機器人暫停動作 %u 秒。", (duration / IN_MILLISECONDS));
            else
                SendSysMessage("全隊機器人全隊機器人解除暫停");
        }
        else
            SendSysMessage("隊伍中無機器人。");
    }
    else
    {
        Player* pTarget = GetSelectedPlayer();//對著指定的機器人下達暫停指令
        if (!pTarget)
        {
            SendSysMessage(LANG_NO_CHAR_SELECTED);
            SetSentErrorMessage(true);
            return false;
        }

        if (HandlePartyBotPauseApplyHelper(pTarget, duration))
        {
            if (pause)
                PSendSysMessage("%s 暫停動作 %u 秒。", pTarget->GetName(), (duration / IN_MILLISECONDS));
            else
                PSendSysMessage("%s 解除暫停。", pTarget->GetName());
        }
            
        else
            SendSysMessage("目標並非機器人。");
    }

    return true;
}

bool ChatHandler::HandlePartyBotPauseCommand(char* args)
{
    return HandlePartyBotPauseHelper(args, true);
}

bool ChatHandler::HandlePartyBotUnpauseCommand(char* args)
{
    return HandlePartyBotPauseHelper(args, false);
}

bool ChatHandler::HandlePartyBotRemoveCommand(char* args)
{
    Player* pTarget = GetSelectedPlayer();
    if (!pTarget)
    {
        SendSysMessage(LANG_NO_CHAR_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (pTarget->AI())
    {
        if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pTarget->AI()))
        {
            pAI->botEntry->requestRemoval = true;
            return true;
        }
    }

    SendSysMessage("目標並非機器人。");
    SetSentErrorMessage(true);
    return false;
}

//以下是戰場機器人命令
bool ChatHandler::HandleBattleBotAddAlteracCommand(char* args)
{
    return HandleBattleBotAddCommand(args, BATTLEGROUND_QUEUE_AV);
}

bool ChatHandler::HandleBattleBotAddArathiCommand(char* args)
{
    return HandleBattleBotAddCommand(args, BATTLEGROUND_QUEUE_AB);
}

bool ChatHandler::HandleBattleBotAddWarsongCommand(char* args)
{
    return HandleBattleBotAddCommand(args, BATTLEGROUND_QUEUE_WS);
}

bool ChatHandler::HandleBattleBotAddCommand(char* args, uint8 bg) //輸入兩個參數：args陣營名稱、bg戰場名稱
{
    Player* pPlayer = m_session->GetPlayer();
    if (!pPlayer)
        return false;

    if (!*args)
    {
        SendSysMessage("錯誤的語法。需指定陣營");
        SetSentErrorMessage(true);
        return false;
    }

    Team botTeam = HORDE;
    uint32 botLevel = sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL);
	uint32 playerLevel = pPlayer->GetLevel();

	if (playerLevel >= 10 && playerLevel <= 19)
	{
		botLevel = urand(10, 19);
	}
	else if (playerLevel >= 20 && playerLevel <= 29)
	{
		botLevel = urand(20, 29);
	}
	else if (playerLevel >= 30 && playerLevel <= 39)
	{
		botLevel = urand(30, 39);
	}
	else if (playerLevel >= 40 && playerLevel <= 49)
	{
		botLevel = urand(40, 49);
	}
	else if (playerLevel >= 50 && playerLevel <= 59)
	{
		botLevel = urand(50, 59);
	}
	else if (playerLevel = 60)
	{
		botLevel = 60;
	}

    std::string option;
    if (char* arg1 = ExtractArg(&args))
    {
        option = arg1;
        if (option == "horde")
            botTeam = HORDE;
        else if (option == "alliance")
            botTeam = ALLIANCE;
        else
        {
            SendSysMessage("錯誤的語法。需指定陣營");
            SetSentErrorMessage(true);
            return false;
        }

        ExtractUInt32(&args, botLevel);
    }

    std::vector<uint32> dpsClasses = { CLASS_WARRIOR, CLASS_HUNTER, CLASS_ROGUE, CLASS_MAGE, CLASS_WARLOCK, CLASS_PRIEST, CLASS_DRUID };
    if (botTeam == HORDE)
        dpsClasses.push_back(CLASS_SHAMAN);
    else
        dpsClasses.push_back(CLASS_PALADIN);
    uint8 botClass = SelectRandomContainerElement(dpsClasses);
    uint8 botRace = SelectRandomRaceForClass(botClass, botTeam);
	if (botTeam == ALLIANCE)
	{
		// Spawn alliance battlebot on GM Island
		BattleBotAI* ai = new BattleBotAI(botRace, botClass, botLevel, 1, 0, 16224.356f, 16284.763f, 13.175f, 4.56f, bg);
		sPlayerBotMgr.AddBot(ai);
	}
	if (botTeam == HORDE)
	{
		// Spawn horde battlebot on GM Island
		BattleBotAI* ai = new BattleBotAI(botRace, botClass, botLevel, 1, 0, 16227.326f, 16284.652f, 13.175f, 4.56f, bg);
		sPlayerBotMgr.AddBot(ai);
	}

    if (bg == BATTLEGROUND_QUEUE_WS)
        PSendSysMessage("戰歌峽谷，%s參戰！", option.c_str());
        
    if (bg == BATTLEGROUND_QUEUE_AB)
        PSendSysMessage("阿拉希盆地，%s參戰！", option.c_str());
    
    if (bg == BATTLEGROUND_QUEUE_AV)
        PSendSysMessage("奧特蘭克山谷，%s參戰！", option.c_str());

    return true;
}

bool ChatHandler::HandleBattleBotRemoveCommand(char* args)
{
    Player* pTarget = GetSelectedPlayer();
    if (!pTarget)
    {
        SendSysMessage(LANG_NO_CHAR_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (pTarget->AI())
    {
        if (BattleBotAI* pAI = dynamic_cast<BattleBotAI*>(pTarget->AI()))
        {
            pAI->botEntry->requestRemoval = true;
            return true;
        }
    }

    SendSysMessage("目標並非戰場機器人。");
    SetSentErrorMessage(true);
    return false;
}

#define SPELL_RED_GLOW 20370

void ShowBattleBotPathHelper(Map* pMap, BattleBotPath* pPath, uint32 id)
{
    for (const auto& point : *pPath)
    {
        if (Creature* pWaypoint = pMap->SummonCreature(VISUAL_WAYPOINT, point.x, point.y, point.z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 120000, true))
        {
            // Show path id as level to distinguish individual paths.
            pWaypoint->SetUInt32Value(UNIT_FIELD_LEVEL, id);

            // Mark points that have script attached.
            if (point.pFunc)
                pWaypoint->CastSpell(pWaypoint, SPELL_RED_GLOW, true);
        }
    }
}

bool ChatHandler::HandleBattleBotShowPathCommand(char* args)
{
    Player* pTarget = GetSelectedPlayer();
    if (!pTarget)
    {
        SendSysMessage(LANG_NO_CHAR_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (pTarget->AI())
    {
        if (BattleBotAI* pAI = dynamic_cast<BattleBotAI*>(pTarget->AI()))
        {
            if (pAI->m_currentPath)
                ShowBattleBotPathHelper(pTarget->GetMap(), pAI->m_currentPath, 1);
            else
                SendSysMessage("Target is not following a path.");

            return true;
        }
    }

    SendSysMessage("目標並非戰場機器人。");
    SetSentErrorMessage(true);
    return false;
}

bool ChatHandler::HandleBattleBotShowAllPathsCommand(char* args)
{
    Player* pPlayer = m_session->GetPlayer();
    BattleGround* pBG = pPlayer->GetBattleGround();
    if (!pBG)
    {
        SendSysMessage("你不在戰場中。");
        return false;
    }

    std::vector<BattleBotPath*> const* pPaths;

    switch (pBG->GetTypeID())
    {
        case BATTLEGROUND_AB:
        {
            pPaths = &vPaths_AB;
            break;
        }
        case BATTLEGROUND_AV:
        {
            pPaths = &vPaths_AV;
            break;
        }
        case BATTLEGROUND_WS:
        {
            pPaths = &vPaths_WS;
            break;
        }
        default:
            break;
    }

    uint32 id = 1;
    for (const auto& path : *pPaths)
    {
        ShowBattleBotPathHelper(pPlayer->GetMap(), path, id++);
    }

    PSendSysMessage("Showing %u paths for battleground.", id);
    return true;
}
