/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "PartyBotAI.h"
#include "CombatBotBaseAI.h"
#include "Player.h"
#include "CreatureAI.h"
#include "MotionMaster.h"
#include "GridNotifiersImpl.h"
#include "ObjectMgr.h"
#include "PlayerBotMgr.h"
#include "Opcodes.h"
#include "World.h"
#include "WorldPacket.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "Chat.h"
#include <string>
#include <random>

/*
enum PartyBotSpells //此處的法術定義是給機器人使用和施放用的，通常是較通用的法術，非特定職業的法術
{
    PB_SPELL_FOOD = 1131,
	PB_SPELL_DRINK_25 = 1133, // bot>=lv55
	PB_SPELL_DRINK_35 = 1135, // bot>=lv35
	PB_SPELL_DRINK_45 = 1137, //bot>=lv45 Restores 2934 mana over 30 sec
    PB_SPELL_DRINK_55 = 22734, // bot>=lv55
    PB_SPELL_AUTO_SHOT = 75,
    PB_SPELL_SHOOT_WAND = 5019,
    PB_SPELL_HONORLESS_TARGET = 2479,
    PB_SPELL_POT_REJUV = 22729, //回春藥水 效果回復1440 to 1760點法力值和生命值。
    PB_SPELL_ELX_MAGEBL = 24363, //魔血藥水 效果每5秒回復12點法力，持續1hour
    PB_SPELL_ELX_MOONG = 17538, //貓鼬藥劑 效果敏捷提高25點，爆擊率提高2%
    PB_SPELL_ELX_FORCE = 17537,
    PB_SPELL_FLASK_TITAN = 17626,
    PB_SPELL_FLASK_SPOWER = 17628,
    PB_SPELL_FLASK_WISDOM = 17627,

    //mounts definition of each race
	PB_SPELL_MOUNT_40_HUMAN = 470,
	PB_SPELL_MOUNT_40_NELF = 10787,
	PB_SPELL_MOUNT_40_DWARF = 6896,
	PB_SPELL_MOUNT_40_GNOME = 17456,
	PB_SPELL_MOUNT_40_TROLL = 10795,
	PB_SPELL_MOUNT_40_ORC = 581,
	PB_SPELL_MOUNT_40_TAUREN = 18363,
	PB_SPELL_MOUNT_40_UNDEAD = 8980,
	PB_SPELL_MOUNT_60_HUMAN = 22717,
	PB_SPELL_MOUNT_60_NELF = 22723,
	PB_SPELL_MOUNT_60_DWARF = 22720,
	PB_SPELL_MOUNT_60_GNOME = 22719,
	PB_SPELL_MOUNT_60_TROLL = 22721,
	PB_SPELL_MOUNT_60_ORC = 22724,
	PB_SPELL_MOUNT_60_TAUREN = 22718,
	PB_SPELL_MOUNT_60_UNDEAD = 22722,
	PB_SPELL_MOUNT_40_PALADIN = 13819,
	PB_SPELL_MOUNT_60_PALADIN = 23214,
	PB_SPELL_MOUNT_40_WARLOCK = 5784,
	PB_SPELL_MOUNT_60_WARLOCK = 23161,

    PB_SPELL_SHIELD_SLAM = 23922, //盾牌猛擊
    PB_SPELL_HOLY_SHIELD = 20925, //神聖之盾
    PB_SPELL_TOUCH_OF_SHADOW = 18791, //暗影之觸

	PB_SPELL_GOBLIN_SAPPER_CHARGE = 13241, //哥布林工事炸藥(對自己放)
	PB_SPELL_IRON_GRENADE = 4068, //鐵皮手雷(對敵人放)
	PB_SPELL_SHOOT_GUN = 7918, //槍射擊
	PB_SPELL_SHOOT_BOW = 2480, //弓射擊
	PB_SPELL_SHOOT_CROSSBOW = 7919, //十字弓射擊
	PB_SPELL_THROW = 2764, //投擲武器
};

enum MageBotSpells //[WIP]此處的法術定義是給法師機器人使用和施放用的
{
	PB_SPELL_PORTAL_IRON_FORGE = 11416, //傳送門：鐵爐堡
};

enum WarlockBotPetSpells //[TECHEASY]此處的法術定義是給術士機器人寵物使用和施放用的
{
	PB_SPELL_FIREBOLT_RANK1 = 3110, //火焰箭R1 需要等級1
	PB_SPELL_FIREBOLT_RANK2 = 7799, //火焰箭R2 需要等級8
	PB_SPELL_FIREBOLT_RANK3 = 7800, //火焰箭R3 需要等級18
	PB_SPELL_FIREBOLT_RANK4 = 7801, //火焰箭R4 需要等級28
	PB_SPELL_FIREBOLT_RANK5 = 7802, //火焰箭R5 需要等級38
	PB_SPELL_FIREBOLT_RANK6 = 11762, //火焰箭R6 需要等級48
	PB_SPELL_FIREBOLT_RANK7 = 11763, //火焰箭R7 需要等級58
	PB_SPELL_BLOODPACT_RANK1 = 6307, //血之契印R1 需要等級4
	PB_SPELL_BLOODPACT_RANK2 = 7802, //血之契印R2 需要等級14
	PB_SPELL_BLOODPACT_RANK3 = 7805, //血之契印R3 需要等級26
	PB_SPELL_BLOODPACT_RANK4 = 11766, //血之契印R4 需要等級38
	PB_SPELL_BLOODPACT_RANK5 = 11767, //血之契印R5 需要等級50
};
*/
/*
enum PartyBotSpecs //Partybot法師天賦
{
    PB_SPEC_MAGE_ARCANE = 81,
    PB_SPEC_MAGE_FIRE = 82,
    PB_SPEC_MAGE_FROST = 83,
};
*/
#define PB_UPDATE_INTERVAL 1000
#define PB_MIN_FOLLOW_DIST 3.0f
#define PB_MAX_FOLLOW_DIST 6.0f
#define PB_MIN_FOLLOW_ANGLE 0.0f
#define PB_MAX_FOLLOW_ANGLE 6.283f

//Function: 克隆自玩家
void PartyBotAI::CloneFromPlayer(Player const* pPlayer)
{
    if (!pPlayer)
        return;

    if (pPlayer->GetLevel() != me->GetLevel())
    {
        me->GiveLevel(pPlayer->GetLevel());
        me->InitTalentForLevel();
        me->SetUInt32Value(PLAYER_XP, 0);
    }

    // Learn all of the target's spells.
    for (const auto& spell : pPlayer->GetSpellMap())
    {
        if (spell.second.disabled)
            continue;

        if (spell.second.state == PLAYERSPELL_REMOVED)
            continue;

        SpellEntry const* pSpellEntry = sSpellMgr.GetSpellEntry(spell.first);
        if (!pSpellEntry)
            continue;

        uint32 const firstRankId = sSpellMgr.GetFirstSpellInChain(spell.first);
        if (!me->HasSpell(spell.first))
            me->LearnSpell(spell.first, false, (firstRankId == spell.first && GetTalentSpellPos(firstRankId)));
    }

    me->GetHonorMgr().SetHighestRank(pPlayer->GetHonorMgr().GetHighestRank());
    me->GetHonorMgr().SetRank(pPlayer->GetHonorMgr().GetRank());

    // Unequip current gear
    for (int i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
        me->AutoUnequipItemFromSlot(i);

    // Copy gear from target.
    for (int i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
    {
        if (Item* pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
        {
            me->SatisfyItemRequirements(pItem->GetProto());
            me->StoreNewItemInBestSlots(pItem->GetEntry(), 1);
        }   
    }
}

//Function: 獲得隊長
Player* PartyBotAI::GetPartyLeader() const
{
    Group* pGroup = me->GetGroup();
    if (!pGroup)
        return nullptr;

    if (Player* originalLeader = ObjectAccessor::FindPlayerNotInWorld(m_leaderGuid))
    {
        if (me->InBattleGround() == originalLeader->InBattleGround())
        {
            // In case the original spawner is not in the same group as the bots anymore.
            if (pGroup != originalLeader->GetGroup())
                return nullptr;

            // In case the current leader is the bot itself and it's not inside a Battleground.
            ObjectGuid currentLeaderGuid = pGroup->GetLeaderGuid();
            if (currentLeaderGuid == me->GetObjectGuid() && !me->InBattleGround())
                return nullptr;
        }

        return originalLeader;
    }
    return nullptr;
}

//從目標逃開邏輯function
void PartyBotAI::RunAwayFromTarget(Unit* pTarget)
{
    if (Player* pLeader = GetPartyLeader())
    {
        if (pLeader->IsInWorld() &&
            pLeader->GetMap() == me->GetMap())
        {
			float leaderDistance = me->GetDistance(pLeader);
			float leadToMonsDist = pLeader->GetDistance(pTarget);
			if (leaderDistance > 15.0f || leadToMonsDist > 15.0f)
			{
				me->GetMotionMaster()->MoveIdle();
				MoveToTarget(pLeader);
				return;
			}
        }
    }

    me->GetMotionMaster()->MoveDistance(pTarget, 12.0f);
}

//法師專用從目標逃開邏輯function
void PartyBotAI::MageRunAwayFromTarget(Unit* pTarget)
{
	if (Player* pLeader = GetPartyLeader())
	{
		if (pLeader->GetMap()->IsDungeon())
		{
			float leaderDistance = me->GetDistance(pLeader);
			float leadToMonsDist = pLeader->GetDistance(pTarget);
			if (leaderDistance > 15.0f || leadToMonsDist > 15.0f)
			{
				me->GetMotionMaster()->MoveIdle();
				MoveToTarget(pLeader);
				return;
			}
		}
		else if (pLeader->IsInWorld() && pLeader->GetMap() == me->GetMap())
		{
			float const distance = me->GetDistance(pLeader);
			if (distance >= 15.0f && distance <= 30.0f &&
				pLeader->GetDistance(pTarget) >= 15.0f)
			{
				me->MonsterMove(pLeader->GetPositionX(), pLeader->GetPositionY(), pLeader->GetPositionZ());
				return;
			}
		}
	}

	me->GetMotionMaster()->MoveDistance(pTarget, 8.5f);
}

//獵人專用從目標逃開邏輯function
bool PartyBotAI::HunterRunAwayFromTarget(Unit* pTarget)
{
	if (Player* pLeader = GetPartyLeader())
	{
		if (pLeader->GetMap()->IsDungeon())
		{
			me->MonsterMove(pLeader->GetPositionX(), pLeader->GetPositionY(), pLeader->GetPositionZ());
			return true;
		}
		else if (pLeader->IsInWorld() && pLeader->GetMap() == me->GetMap())
		{
			float const distance = me->GetDistance(pLeader);
			if (distance >= 15.0f && distance <= 30.0f &&
				pLeader->GetDistance(pTarget) >= 15.0f)
			{
				me->MonsterMove(pLeader->GetPositionX(), pLeader->GetPositionY(), pLeader->GetPositionZ());
				return true;
			}
		}
	}

	return me->GetMotionMaster()->MoveDistance(pTarget, 8.5f);
}

void PartyBotAI::RunAwayFromObject(GameObject* pObject, float distance, Unit* pTarget)
{
	if (m_distObjGuid &&
		m_distObjGuid == pObject->GetObjectGuid() &&
		me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
		return;

	float x, y, z;
	float angle = frand(PB_MIN_FOLLOW_ANGLE, PB_MAX_FOLLOW_ANGLE);

	if (pTarget)
		angle = ((2 * M_PI) - ((me->GetAngle(pTarget) + me->GetAngle(pObject)) / 2));

	pObject->GetNearPoint(me, x, y, z, 0.0f, distance, angle);

	me->GetMotionMaster()->Clear();
	me->GetMotionMaster()->MovePoint(0, x, y, z, MOVE_PATHFINDING);
}

void PartyBotAI::RunAwayFromAOE(float distance)
{
	if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
		return;

	float x, y, z;
	float angle = frand(1.0f, 2.0f);
	if (urand(0, 1))
		angle *= -1.0f;

	me->GetNearPoint(me, x, y, z, 0.0f, distance, angle);

	me->GetMotionMaster()->Clear();
	me->GetMotionMaster()->MovePoint(0, x, y, z, MOVE_PATHFINDING);
}


void PartyBotAI::MoveToTarget(Unit* pTarget, float distance)
{
	float x, y, z;
	float angle = frand(PB_MIN_FOLLOW_ANGLE, PB_MAX_FOLLOW_ANGLE);
	pTarget->GetNearPoint(me, x, y, z, 0, distance, angle);

	me->GetMotionMaster()->Clear();
	me->GetMotionMaster()->MovePoint(0, x, y, z, MOVE_PATHFINDING);
}

void PartyBotAI::ChaseTarget(Unit* pTarget)
{
	if (m_role == ROLE_RANGE_DPS)
		me->SetCasterChaseDistance(25.0f);
	else if (me->HasDistanceCasterMovement())
		me->SetCasterChaseDistance(0.0f);

	float angle = frand((M_PI - 0.5f), (M_PI + 0.5f));
	float distance = pTarget->GetMeleeReach();
	if (distance > 3.0f)
		distance *= frand(0.75, 0.9);
	me->GetMotionMaster()->MoveChase(pTarget, distance, m_role == ROLE_MELEE_DPS ? angle : 0.0f);
}

bool PartyBotAI::DrinkAndEat() //吃喝邏輯
{
    if (m_isBuffing)
        return false;

    if (me->GetVictim())
        return false;

    bool const needToEat = me->GetHealthPercent() < 90.0f;
    bool const needToDrink = (me->GetPowerType() == POWER_MANA) && (me->GetPowerPercent(POWER_MANA) < 85.0f);

    if (!needToEat && !needToDrink)
        return false;

    bool const isEating = me->HasAura(PB_SPELL_FOOD);
    bool const isDrinking = me->HasAura(PB_SPELL_DRINK_25) || me->HasAura(PB_SPELL_DRINK_35) || me->HasAura(PB_SPELL_DRINK_45) || me->HasAura(PB_SPELL_DRINK_55);

    if (!isEating && needToEat)
    {
        if (me->GetMotionMaster()->GetCurrentMovementGeneratorType())
        {
            me->StopMoving();
            me->GetMotionMaster()->Clear(false, true);
            me->GetMotionMaster()->MoveIdle();
        }
        if (SpellEntry const* pSpellEntry = sSpellMgr.GetSpellEntry(PB_SPELL_FOOD))
        {
            me->CastSpell(me, pSpellEntry, true);
            me->RemoveSpellCooldown(*pSpellEntry);
        }
        return true;
    }

    if (!isDrinking && needToDrink)
    {
        if (me->GetMotionMaster()->GetCurrentMovementGeneratorType())
        {
            me->StopMoving();
            me->GetMotionMaster()->Clear(false, true);
            me->GetMotionMaster()->MoveIdle();
        }
		if (me->GetLevel() < 35)
		{
			if (SpellEntry const* pSpellEntry = sSpellMgr.GetSpellEntry(PB_SPELL_DRINK_25))
			{
				me->CastSpell(me, pSpellEntry, true);
				me->RemoveSpellCooldown(*pSpellEntry);
			}
		}
		else if (me->GetLevel() >= 35 || me->GetLevel() < 45)
		{
			if (SpellEntry const* pSpellEntry = sSpellMgr.GetSpellEntry(PB_SPELL_DRINK_35))
			{
				me->CastSpell(me, pSpellEntry, true);
				me->RemoveSpellCooldown(*pSpellEntry);
			}
		}
		else if (me->GetLevel() >= 45 || me->GetLevel() < 55)
		{
			if (SpellEntry const* pSpellEntry = sSpellMgr.GetSpellEntry(PB_SPELL_DRINK_45))
			{
				me->CastSpell(me, pSpellEntry, true);
				me->RemoveSpellCooldown(*pSpellEntry);
			}
		}
		else
		{
			if (SpellEntry const* pSpellEntry = sSpellMgr.GetSpellEntry(PB_SPELL_DRINK_55))
			{
				me->CastSpell(me, pSpellEntry, true);
				me->RemoveSpellCooldown(*pSpellEntry);
			}
		}
		return true;
    }

    return needToEat || needToDrink;
}

//應自動復活function
bool PartyBotAI::ShouldAutoRevive() const
{
    if (me->GetDeathState() == DEAD)
        return true;

	Player* pLeader = GetPartyLeader();
	if (!pLeader || !pLeader->IsAlive())
		return false;

	if (pLeader->IsInWorld() &&
		pLeader->IsAlive() &&
        !pLeader->IsInCombat() &&
		(pLeader->GetMap() != me->GetMap() ||
			m_ressTimer > (2 * MINUTE * IN_MILLISECONDS)))
		return true;

	return false;
}

bool PartyBotAI::CanTryToCastSpell(Unit const* pTarget, SpellEntry const* pSpellEntry) const //可嘗試施法Function
{
    if (pSpellEntry->IsAreaOfEffectSpell() && !m_marksToCC.empty())
        return false;

    return CombatBotBaseAI::CanTryToCastSpell(pTarget, pSpellEntry);
}

bool PartyBotAI::CanUseCrowdControl(SpellEntry const* pSpellEntry, Unit* pTarget) const //可使用控場Function
{
    if (pSpellEntry->HasAuraInterruptFlag(AURA_INTERRUPT_DAMAGE_CANCELS) &&
        AreOthersOnSameTarget(pTarget->GetObjectGuid()))
        return false;

    if (pSpellEntry->HasSingleTargetAura())
    {
        auto const& singleAuras = me->GetSingleCastSpellTargets();
        if (singleAuras.find(pSpellEntry) != singleAuras.end())
            return false;
    }

    return true;
}

//對目標開始攻擊function
bool PartyBotAI::AttackStart(Unit* pVictim)
{
    m_isBuffing = false;

    if (me->IsMounted())
        me->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);

    if (me->Attack(pVictim, true))
    {
        ChaseTarget(pVictim);
        return true;
    }

    return false;
}

//機器人停止攻擊命令助手function
void StopTankBotAttackHelper(PartyBotAI* pAI, Player* pBot)
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

bool HandlePartyBotDPSPauseApplyHelper(Player* pTarget, uint32 duration)
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

//坦克開怪function
bool PartyBotAI::TankPull(Unit* pVictim)
{
	bool success = false;
	bool all = false;
	uint32 duration = 10 * IN_MILLISECONDS;
	/*	PartyBotAI* pAI;
	uint32 duration;
	duration = 10* IN_MILLISECONDS;


	if (m_role != ROLE_TANK &&
		((m_role = ROLE_MELEE_DPS) || (m_role = ROLE_RANGE_DPS))) //如果非坦職，且職業為DPS進行以下判斷
	{
		m_isBuffing = false;

		if (me->IsMounted())
			me->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);

		pAI->m_updateTimer.Reset(duration);

		if (duration)
		{
			me->StopMoving();
			me->GetMotionMaster()->MoveIdle();
		}
		return false;
	}
	else if (m_role = ROLE_HEALER) //如果是補職則離開function
		return false;
	else //如果是坦職則進行以下判斷*/
	if (m_role == ROLE_TANK)
	{
		m_isBuffing = false;

		if (me->IsMounted())
			me->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
		switch (me->GetClass())
		{
			case CLASS_WARRIOR:
			{
				if (me->Attack(pVictim, true))
				{
					if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE
						&& me->GetDistance(pVictim) > 30.0f) //如果目前移動行為為閒置且和敵人距離>30碼
					{
						me->GetMotionMaster()->MoveChase(pVictim, 10.0f); //則往敵人移動距離25碼
					}
					if (me->GetCombatDistance(me->GetVictim()) == 10.0f)
						me->AttackStop(true);
					me->InterruptNonMeleeSpells(false);

					if (!me->IsStopped())
						me->StopMoving();
					if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE)
						me->GetMotionMaster()->Clear();
					//me->GetMotionMaster()->MoveChase(pVictim, 10.0f); //則往敵人移動距離10碼
					//if (!me->IsStopped())
					//me->StopMoving();
					/*				if (me->HasSpell(PB_SPELL_SHOOT_BOW) &&
					!me->IsMoving() &&
					(me->GetCombatDistance(pVictim) > 8.0f) &&
					!me->IsNonMeleeSpellCasted()) //如果和敵人距離>8碼就射擊
					{
					switch (me->CastSpell(pVictim, PB_SPELL_SHOOT_BOW, false))
					{
					case SPELL_FAILED_NEED_AMMO:
					case SPELL_FAILED_NO_AMMO:
					{
					AddHunterAmmo();
					break;
					}
					}
					me->AttackStop(true);
					me->InterruptNonMeleeSpells(false);
					if (!me->IsStopped())
					me->StopMoving();
					}*/
					return true;
					if (me->GetDistance(pVictim) >= 8.0f && me->GetDistance(pVictim) <= 30.0f) //如果在8~30碼之間
					{
						if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE
							&& me->GetDistance(pVictim) > 30.0f) //如果目前移動行為為閒置且和敵人距離>30碼
						{
							me->GetMotionMaster()->MoveChase(pVictim, 10.0f); //則往敵人移動距離25碼
						}
						if (me->GetCombatDistance(me->GetVictim()) == 10.0f)
							me->AttackStop(true);
						me->InterruptNonMeleeSpells(false);

						if (!me->IsStopped())
							me->StopMoving();
						if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE)
							me->GetMotionMaster()->Clear();
						//me->GetMotionMaster()->MoveChase(pVictim, 8.0f); //則往敵人移動距離10碼
						//if (!me->IsStopped())
						//	me->StopMoving();
						/*					if (me->HasSpell(PB_SPELL_SHOOT_BOW) &&
						//(me->GetCombatDistance(pVictim) > 8.0f) &&
						!me->IsNonMeleeSpellCasted()) //如果和敵人距離>8碼就射擊
						{
						switch (me->CastSpell(pVictim, PB_SPELL_SHOOT_BOW, false))
						{
						case SPELL_FAILED_NEED_AMMO:
						case SPELL_FAILED_NO_AMMO:
						{
						AddHunterAmmo();
						break;
						}
						}
						//me->AttackStop(true);
						me->InterruptNonMeleeSpells(false);
						if (!me->IsStopped())
						me->StopMoving();
						if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE)
						me->GetMotionMaster()->Clear();

						break;
						}*/
						return true;
					}

					else if (me->GetDistance(pVictim) < 8.0f)
					{
						if (me->Attack(pVictim, true))//如果距離<8碼就上前攻擊
						{
							if (me->HasDistanceCasterMovement())
								me->SetCasterChaseDistance(0.0f);

							me->GetMotionMaster()->MoveChase(pVictim, 1.0f, 3.0f);
						}
						return true;
					}
				}
					return false;
			}
			case CLASS_PALADIN:
			case CLASS_DRUID:
			{
				if (me->Attack(pVictim, true))
					{
						if (me->HasDistanceCasterMovement())
							me->SetCasterChaseDistance(0.0f);
						me->GetMotionMaster()->MoveChase(pVictim, 1.0f, 3.0f);
					}
			}
			return true;
			}
	}
	else
		if (m_role == ROLE_MELEE_DPS || m_role == ROLE_RANGE_DPS)
		{
			if (HandlePartyBotDPSPauseApplyHelper(me, duration))
				success = true;
		}

	return false;
}

/*
//[WIP]法師開傳送門Function
bool PartyBotAI::MageOpenPortal()
{
	if (me->GetMotionMaster()->GetCurrentMovementGeneratorType())
	{
		me->StopMoving();
		me->GetMotionMaster()->Clear(false, true);
		me->GetMotionMaster()->MoveIdle();
	}
	if (SpellEntry const* pSpellEntry = sSpellMgr.GetSpellEntry(PB_SPELL_PORTAL_IRON_FORGE))
	{
		me->CastSpell(me, pSpellEntry, true);
		me->RemoveSpellCooldown(*pSpellEntry);
	}
	return true;
}
*/

Unit* PartyBotAI::GetMarkedTarget(RaidTargetIcon mark) const
{
    ObjectGuid targetGuid = me->GetGroup()->GetTargetWithIcon(mark);
    if (targetGuid.IsUnit())
        return me->GetMap()->GetUnit(targetGuid);

    return nullptr;
}

//Function-選擇攻擊目標
Unit* PartyBotAI::SelectAttackTarget(Player* pLeader) const
{
    if (!m_spamGuid.IsEmpty())
    {
        if (Unit* pTarget = me->GetMap()->GetUnit(m_spamGuid))
        {
            if (IsValidHostileTarget(pTarget))
                return pTarget;
        }
    }
    
    // Stick to marked target in combat.
    if (me->IsInCombat() || pLeader->GetVictim())
    {
        for (auto markId : m_marksToFocus)
        {
            ObjectGuid targetGuid = me->GetGroup()->GetTargetWithIcon(markId);
            if (targetGuid.IsUnit())
                if (Unit* pVictim = me->GetMap()->GetUnit(targetGuid))
                    if (IsValidHostileTarget(pVictim))
                        return pVictim;
        }
    }

    // Who is attacking me. 誰在攻擊我
    for (const auto pAttacker : me->GetAttackers())
    {
        if (IsValidHostileTarget(pAttacker))
            return pAttacker;
    }

    // Who is the leader attacking.
    if (Unit* pVictim = pLeader->GetVictim())
    {
       if (pLeader->IsInCombat() && IsValidHostileTarget(pVictim))
            return pVictim;
    }

	// Assist Pet
    if (Pet* pPet = me->GetPet())
    {
        if (Unit* pVictim = pPet->GetVictim())
            if (IsValidHostileTarget(pVictim))
                return pVictim;
        for (const auto pAttacker : pPet->GetAttackers())
        {
            if (IsValidHostileTarget(pAttacker))
                return pAttacker;
        }
    }

    // Check if other group members are under attack. 檢查遭受攻擊中的隊伍成員
    if (Unit* pPartyAttacker = SelectPartyAttackTarget())
        return pPartyAttacker;

    // Assist pet if its in combat. 寵物若在戰鬥中則協助牠
    if (Pet* pPet = me->GetPet())
    {
        if (Unit* pPetAttacker = pPet->GetAttackerForHelper())
            return pPetAttacker;
    }

    return nullptr;
}

//選擇隊伍攻擊的目標function
Unit* PartyBotAI::SelectPartyAttackTarget() const
{
    std::vector<Unit*> vAttackers;
    Group* pGroup = me->GetGroup();

    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        if (Player* pMember = itr->getSource())
        {
            // We already checked self.
            if (pMember == me)
                continue;

			if (m_role == ROLE_TANK)
			{
				// Do not attack other tanks tagert 多坦的條件下，不會互搶目標
				if (pMember->AI())
				{
					if (PartyBotAI* pAI = dynamic_cast<PartyBotAI*>(pMember->AI()))
					{
						if (pAI->m_role == ROLE_TANK)
							continue;
					}
				}
				else if (pMember->HasSpell(PB_SPELL_SHIELD_SLAM) ||
					pMember->HasSpell(PB_SPELL_HOLY_SHIELD) ||
					pMember->GetShapeshiftForm() == FORM_BEAR ||
					pMember->GetShapeshiftForm() == FORM_DIREBEAR)
					continue;
			}

            for (const auto pAttacker : pMember->GetAttackers())
            {
                if (!pAttacker->IsPlayer() &&
                    IsValidHostileTarget(pAttacker) &&
                    me->IsWithinDist(pAttacker, 50.0f))
                    vAttackers.push_back(pAttacker);
            }

            if (Pet* pPet = pMember->GetPet())
            {
                for (const auto pAttacker : pPet->GetAttackers())
                {
                    if (IsValidHostileTarget(pAttacker) &&
                        me->IsWithinDist(pAttacker, 50.0f))
						vAttackers.push_back(pAttacker);
                }
            }
        }
    }

	if (!vAttackers.empty())
	{
		uint8 rand = urand(0, (vAttackers.size() - 1));
		return vAttackers[rand];
	}

    return nullptr;
}

Unit* PartyBotAI::SelectSpellTargetDifferentFrom(SpellEntry const* pSpellEntry, Unit* pVictim, float distance) const
{
	if (!IsSpellReady(pSpellEntry))
		return nullptr;

	std::list<Unit*> targets;
	MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck u_check(pVictim, me, distance);
	MaNGOS::UnitListSearcher<MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
	Cell::VisitAllObjects(me, searcher, distance);

	// remove current target
	if (pVictim)
		targets.remove(pVictim);

	// remove not LoS targets, not valid target, or immune target
	for (std::list<Unit*>::iterator tIter = targets.begin(); tIter != targets.end();)
	{
		if ((!me->IsWithinLOSInMap(*tIter)) || !me->IsValidAttackTarget(*tIter) || !CanTryToCastSpell(*tIter, pSpellEntry))
		{
			std::list<Unit*>::iterator tIter2 = tIter;
			++tIter;
			targets.erase(tIter2);
		}
		else
			++tIter;
	}

	// no appropriate targets
	if (targets.empty())
		return nullptr;

	// select random
	uint32 rIdx = urand(0, targets.size() - 1);
	std::list<Unit*>::const_iterator tcIter = targets.begin();
	for (uint32 i = 0; i < rIdx; ++i)
		++tcIter;

	return *tcIter;
}

//選擇要復活的目標
Player* PartyBotAI::SelectResurrectionTarget() const
{
	std::vector<Player*> vRessTargets;
	Player* pTarget = nullptr;

	Group* pGroup = me->GetGroup();
	for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
	{
		if (Player* pMember = itr->getSource())
		{
			// Can't resurrect self.
			if (pMember == me)
				continue;

			if (pMember->GetDeathState() == CORPSE)
				vRessTargets.push_back(pMember);
		}
	}
	if (!vRessTargets.empty())
		pTarget = SelectRandomContainerElement(vRessTargets);

	return pTarget;
}

Player* PartyBotAI::SelectShieldTarget() const
{
    Group* pGroup = me->GetGroup();
    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        if (Player* pMember = itr->getSource())
        {
            // We already checked self.
            if (pMember == me)
                continue;

            if ((IsValidHealTarget(pMember, 50.0f)) &&
                !pMember->GetAttackers().empty() &&
                !pMember->IsImmuneToMechanic(MECHANIC_SHIELD))
                return pMember;
        }
    }

    return nullptr;
}

bool PartyBotAI::CrowdControlMarkedTargets()
{
    SpellEntry const* pSpellEntry = GetCrowdControlSpell();
    if (!pSpellEntry)
        return false;

    for (auto mark : m_marksToCC)
    {
        if (Unit* pTarget = GetMarkedTarget(mark))
        {
            if (!pTarget->HasUnitState(UNIT_STAT_CAN_NOT_REACT_OR_LOST_CONTROL) &&
                IsValidHostileTarget(pTarget) && !AreOthersOnSameTarget(pTarget->GetObjectGuid()))
            {
                if (CanTryToCastSpell(pTarget, pSpellEntry))
                {
                    if (DoCastSpell(pTarget, pSpellEntry) == SPELL_CAST_OK)
                    {
                        me->ClearUnitState(UNIT_STAT_MELEE_ATTACKING);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//加入玩家的隊伍
void PartyBotAI::AddToPlayerGroup()
{
    Player* pPlayer = ObjectAccessor::FindPlayer(m_leaderGuid);
    if (!pPlayer)
        return;

    Group* group = pPlayer->GetGroup();
    if (!group)
    {
        group = new Group;
        // new group: if can't add then delete
        if (!group->Create(pPlayer->GetObjectGuid(), pPlayer->GetName()))
        {
            delete group;
            return;
        }
        sObjectMgr.AddGroup(group);
    }

    group->AddMember(me->GetObjectGuid(), me->GetName());
}

void PartyBotAI::OnWhisper(Player* pWho, std::string text) //接受密語Function
{
    uint32 spellId = atoi(text.c_str());
    if (spellId)
    {
        m_spamSpell = sSpellMgr.GetSpellEntry(spellId);
        m_spamGuid = pWho->GetTargetGuid();

        std::string chatResponse = "I will now spam spell ";
        chatResponse += std::to_string(spellId) + " on ";
        chatResponse += m_spamGuid.GetString();
        me->MonsterWhisper(chatResponse.c_str(), pWho);
    }
    else
    {
        m_spamSpell = nullptr;
        m_spamGuid = ObjectGuid();
    }

}

//送出假封包
void PartyBotAI::SendFakePacket(uint16 opcode)
{
    switch (opcode)
    {
        case CMSG_LOOT_ROLL: //拾取骰裝
        {
            if (m_lootResponses.empty())
                return;

            auto loot = m_lootResponses.begin();
            WorldPacket data(CMSG_LOOT_ROLL);
            data << uint64((*loot).guid);
            data << uint32((*loot).slot);
            data << uint8(0); // pass
            m_lootResponses.erase(loot);
            me->GetSession()->HandleLootRoll(data);
            return;
        }
    }

    CombatBotBaseAI::SendFakePacket(opcode);
}

//定義BOT各種族騎乘的坐騎種類
uint32 PartyBotAI::GetMountSpellId() const
{
	if (me->GetLevel() >= 60)
	{
		if (me->GetClass() == CLASS_PALADIN)
			return PB_SPELL_MOUNT_60_PALADIN;
		if (me->GetClass() == CLASS_WARLOCK)
			return PB_SPELL_MOUNT_60_WARLOCK;

		switch (me->GetRace())
		{
		case RACE_HUMAN:
			return PB_SPELL_MOUNT_60_HUMAN;
		case RACE_NIGHTELF:
			return PB_SPELL_MOUNT_60_NELF;
		case RACE_DWARF:
			return PB_SPELL_MOUNT_60_DWARF;
		case RACE_GNOME:
			return PB_SPELL_MOUNT_60_GNOME;
		case RACE_TROLL:
			return PB_SPELL_MOUNT_60_TROLL;
		case RACE_ORC:
			return PB_SPELL_MOUNT_60_ORC;
		case RACE_TAUREN:
			return PB_SPELL_MOUNT_60_TAUREN;
		case RACE_UNDEAD:
			return PB_SPELL_MOUNT_60_UNDEAD;
		}
	}
	else if (me->GetLevel() >= 40)
	{
		if (me->GetClass() == CLASS_PALADIN)
			return PB_SPELL_MOUNT_40_PALADIN;
		if (me->GetClass() == CLASS_WARLOCK)
			return PB_SPELL_MOUNT_40_WARLOCK;

		switch (me->GetRace())
		{
		case RACE_HUMAN:
			return PB_SPELL_MOUNT_40_HUMAN;
		case RACE_NIGHTELF:
			return PB_SPELL_MOUNT_40_NELF;
		case RACE_DWARF:
			return PB_SPELL_MOUNT_40_DWARF;
		case RACE_GNOME:
			return PB_SPELL_MOUNT_40_GNOME;
		case RACE_TROLL:
			return PB_SPELL_MOUNT_40_TROLL;
		case RACE_ORC:
			return PB_SPELL_MOUNT_40_ORC;
		case RACE_TAUREN:
			return PB_SPELL_MOUNT_40_TAUREN;
		case RACE_UNDEAD:
			return PB_SPELL_MOUNT_40_UNDEAD;
		}
	}

	return 0;
}

void PartyBotAI::OnPacketReceived(WorldPacket const* packet)
{
    //printf("Bot received %s\n", LookupOpcodeName(packet->GetOpcode()));
    switch (packet->GetOpcode())
    {
        case SMSG_LEARNED_SPELL: //學習法術
        case SMSG_SUPERCEDED_SPELL:
        case SMSG_REMOVED_SPELL: //移除法術
        {
            if (m_initialized)
                m_resetSpellData = true;
            return;
        }
        case SMSG_LOOT_START_ROLL:
        {
            uint64 guid = *((uint64*)(*packet).contents());
            uint32 slot = *(((uint32*)(*packet).contents())+2);
            m_lootResponses.emplace_back(LootResponseData(guid, slot ));
            botEntry->m_pendingResponses.push_back(CMSG_LOOT_ROLL);
            return;
        }
    }

    CombatBotBaseAI::OnPacketReceived(packet);
}

void PartyBotAI::OnPlayerLogin()
{
    if (!m_initialized)
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SPAWNING);
}

//PARTYBOT更新AI FUNCTION
void PartyBotAI::UpdateAI(uint32 const diff)
{
    m_updateTimer.Update(diff);
    if (me->IsDead())
        m_ressTimer += diff;
	if (m_spellTimer1 > 0)
		m_spellTimer1 -= diff;
	if (m_aoeSpellTimer > 0)
		m_aoeSpellTimer -= diff;
    if (m_updateTimer.Passed())
        m_updateTimer.Reset(PB_UPDATE_INTERVAL);
    else
        return;

    if (!me->IsInWorld() || me->IsBeingTeleported())
        return;
	
    if (!m_initialized)
    {
        AddToPlayerGroup(); //加入玩家的隊伍

        if (m_level && m_level != me->GetLevel())
        {
            me->GiveLevel(m_level);
            me->InitTalentForLevel();
            me->SetUInt32Value(PLAYER_XP, 0);
        }

        if (!m_cloneGuid.IsEmpty())
        {
            CloneFromPlayer(sObjectAccessor.FindPlayer(m_cloneGuid));
            AutoAssignRole();
        }
        else
        {
            LearnPremadeSpecForClass();

            if (m_role == ROLE_INVALID)
                AutoAssignRole();

            AutoEquipGear(sWorld.getConfig(CONFIG_UINT32_PARTY_BOT_AUTO_EQUIP));

            // fix client bug causing some item slots to not be visible
            if (Player* pLeader = GetPartyLeader())
            {
                me->SetVisibility(VISIBILITY_OFF);
                pLeader->UpdateVisibilityOf(pLeader, me);
                me->SetVisibility(VISIBILITY_ON);
            }
        }

        ResetSpellData(); //重置法術資料
        PopulateSpellData(); //載入法術資料
        AddAllSpellReagents(); //加入施法材料
        me->UpdateSkillsToMaxSkillsForLevel(); //技能提升到MAX
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SPAWNING); //移除不可攻擊標記
        SummonPetIfNeeded(); //如果有需要則召喚寵物
        PopulateConsumableSpellData(); //呼叫使用消耗品函式
        //me->SetHealthPercent(100.0f); //設定生命值100%
        //me->SetPowerPercent(me->GetPowerType(), 100.0f); //設定能量值100

        uint32 newzone, newarea;
        me->GetZoneAndAreaId(newzone, newarea);
        me->UpdateZone(newzone, newarea);

        m_initialized = true; //以上function執行完後初始化狀態為真
        return;
    }

    if (m_resetSpellData)
    {
        ResetSpellData();
        PopulateSpellData();
        m_resetSpellData = false;
    }

    Player* pLeader = GetPartyLeader();
    if (!pLeader)
    {
        botEntry->requestRemoval = true;
        return;
    }

    if (!pLeader->IsInWorld())
        return;

    if (pLeader->InBattleGround() &&
        !me->InBattleGround())
    {
        if (m_receivedBgInvite)
        {
            SendFakePacket(CMSG_BATTLEFIELD_PORT); //傳送戰場
            m_receivedBgInvite = false;
            return;
        }
        
        // Remain idle until we can join battleground.
        return;
    }

    if (pLeader->IsTaxiFlying() || pLeader->GetTransport())
    {
        if (me->GetMotionMaster()->GetCurrentMovementGeneratorType())
        {
            //me->GetMotionMaster()->Clear(false, true);
            me->GetMotionMaster()->MoveIdle();
        }
        return;
    }

    /*if (me->HasUnitState(UNIT_STAT_FEIGN_DEATH) && me->HasAuraType(SPELL_AURA_FEIGN_DEATH) &&
       !me->IsInCombat() && (!me->GetPet() || !me->GetPet()->IsInCombat()) &&
       !me->SelectRandomUnfriendlyTarget(nullptr, 20.0f, false, true))
        me->RemoveSpellsCausingAura(SPELL_AURA_FEIGN_DEATH); 此為VM原版代碼，先註解慢慢研究
    */

    if (me->HasAuraType(SPELL_AURA_FEIGN_DEATH))
	{
        if (me->GetEnemyCountInRadiusAround(me, 20.0f) > 0)
            return;
        else
            me->RemoveSpellsCausingAura(SPELL_AURA_FEIGN_DEATH);
    }

    if (me->HasUnitState(UNIT_STAT_CAN_NOT_REACT_OR_LOST_CONTROL))
        return;

    if (me->IsDead())
    {
        if (me->InBattleGround()) //如果在戰場中
        {
            if (me->GetDeathState() == CORPSE)
            {
                me->BuildPlayerRepop();
                me->RepopAtGraveyard();
            }
        }
        else //如果不在戰場中
        {
            if (ShouldAutoRevive()) //如果應自動復活成立
            {
				m_ressTimer = 0;
                me->SetCheatGod(true);
                me->ResurrectPlayer(0.5f); //復活自己後生命值50%
                me->SpawnCorpseBones(); //產生地上的骷髏
                me->CastSpell(me, PB_SPELL_HONORLESS_TARGET, true); //非榮譽目標法術
                char name[128] = {};
                strcpy(name, pLeader->GetName());
                ChatHandler(me).HandleGonameCommand(name);
            }
        }
        
        return;
    }
    else if (m_ressTimer > 0)
        m_ressTimer = 0;

    if (me->IsGod())
        me->SetCheatGod(false);

    if (me->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL))
    {
        // Stop auto shot if no target.
        if (!me->GetVictim())
            me->InterruptSpell(CURRENT_AUTOREPEAT_SPELL, true);
        else if (me->GetClass() == CLASS_HUNTER)
        {
            if (me->GetCombatDistance(me->GetVictim()) < 8.0f) //如果與敵人距離小於8碼則停止自動射擊
                me->InterruptSpell(CURRENT_AUTOREPEAT_SPELL, true);
            //else
            //    UpdateInCombatAI_Hunter();
        }

        //return;
    }

    if (me->IsNonMeleeSpellCasted(false, false, true))
        return;

    if (me->GetTargetGuid() == me->GetObjectGuid())
        me->ClearTarget();

	// First, check if there are enemies available
	Unit* pVictim;
	pVictim = me->GetVictim();

	if (m_role != ROLE_HEALER && !pLeader->IsMounted())
	{
		if (!pVictim || pVictim->IsDead() || pVictim->HasBreakableByDamageCrowdControlAura())
		{
			if (Unit* pVictim = SelectAttackTarget(pLeader))
			{
				AttackStart(pVictim);
				return;
			}
		}

		if (pVictim && !me->HasInArc(pVictim, 2 * M_PI_F / 3) && !me->IsMoving())
		{
			me->SetInFront(pVictim); //面向目標
			me->SendMovementPacket(MSG_MOVE_SET_FACING, false);
		}
	}

	// Engage combat ASAP
	if (!pLeader->IsMounted() && (pVictim || me->IsInCombat() || (m_role == ROLE_HEALER && pLeader->IsInCombat())))
	{
		UpdateInCombatAI();
		return;
	}

	// If channeling object, do not move
	if (me->GetChannelObjectGuid())
		return;
		UpdateInCombatAI();

	if (!pVictim && !me->IsInCombat())
    {
		float leaderDistance = 0.0f;

		// Distance to leader
		if (!pLeader->IsDead())
			leaderDistance = me->GetDistance(pLeader);

        // Teleport to leader if too far away. 離隊長達100碼，或bot離隊長高度大於20碼則傳送到身邊
        if (leaderDistance > (PB_MAX_FOLLOW_DIST * 15.0f) || me->GetDistanceZ(pLeader) > (PB_MAX_FOLLOW_DIST * 3.2f))
        {
            if (!me->IsStopped())
                me->StopMoving();
            me->GetMotionMaster()->Clear(false, true);
            me->GetMotionMaster()->MoveIdle();
            char name[128] = {};
            strcpy(name, pLeader->GetName());
            ChatHandler(me).HandleGonameCommand(name);
            return;
        }

		else if (leaderDistance > (PB_MAX_FOLLOW_DIST * 2.5f) &&
			me->HasAuraType(SPELL_AURA_MOD_STEALTH) &&
			!pLeader->GetVictim())
		{
			me->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);
		}

		if (leaderDistance > (PB_MAX_FOLLOW_DIST * 1.1f))
		{
			if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != FOLLOW_MOTION_TYPE)
                me->GetMotionMaster()->MoveFollow(pLeader, urand(PB_MIN_FOLLOW_DIST, PB_MAX_FOLLOW_DIST), frand(PB_MIN_FOLLOW_ANGLE, PB_MAX_FOLLOW_ANGLE));
        }
		else if (!me->IsMounted())
        {
            if (DrinkAndEat())
                return;

            UpdateOutOfCombatAI();

            if (m_isBuffing)
                return;

            if (me->IsNonMeleeSpellCasted())
                return;
        }

        // Mount if leader is mounted and we don't have a target.
        if (pLeader->IsMounted() && !me->GetVictim())
        {
            if (!me->IsMounted())
            {
                // Leave shapeshift before mounting.
                if (me->IsInDisallowedMountForm() &&
                    me->GetDisplayId() != me->GetNativeDisplayId() &&
                    me->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
                    me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT);

                auto auraList = pLeader->GetAurasByType(SPELL_AURA_MOUNTED);
                if (!auraList.empty())
                {
                    //bool oldState = me->HasCheatOption(PLAYER_CHEAT_NO_CAST_TIME);
                    me->SetCheatOption(PLAYER_CHEAT_NO_CAST_TIME, true);
                    //me->CastSpell(me, (*auraList.begin())->GetId(), true);
                    //me->SetCheatOption(PLAYER_CHEAT_NO_CAST_TIME, oldState);
                    me->CastSpell(me, GetMountSpellId(), true);
                    me->SetCheatOption(PLAYER_CHEAT_NO_CAST_TIME, false);
                }
            }
        }
        else if (me->IsMounted())
            me->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
    }

	if (me->GetStandState() != UNIT_STAND_STATE_STAND)
		me->SetStandState(UNIT_STAND_STATE_STAND);

	if (!me->IsMoving() && !pVictim && me->GetMotionMaster()->GetCurrentMovementGeneratorType() != FOLLOW_MOTION_TYPE)
		me->GetMotionMaster()->MoveFollow(pLeader, urand(PB_MIN_FOLLOW_DIST, PB_MAX_FOLLOW_DIST), frand(PB_MIN_FOLLOW_ANGLE, PB_MAX_FOLLOW_ANGLE));
}

//Function-更新非戰鬥時AI
void PartyBotAI::UpdateOutOfCombatAI()
{
    if (m_resurrectionSpell) //判斷復活目標
        if (Player* pTarget = SelectResurrectionTarget())
            if (CanTryToCastSpell(pTarget, m_resurrectionSpell))
                if (DoCastSpell(pTarget, m_resurrectionSpell) == SPELL_CAST_OK)
                    return;

    if (m_elixirSpell &&
        !me->HasAura(m_elixirSpell->Id)) //精煉藥劑
    {
        if (CanTryToCastSpell(me, m_elixirSpell))
        {
            if (DoCastSpell(me, m_elixirSpell) == SPELL_CAST_OK)
                return;
        }
    }

    if (m_flaskSpell &&
        me->GetGroup()->isRaidGroup() &&
        !me->HasAura(m_flaskSpell->Id)) //合劑
    {
        if (CanTryToCastSpell(me, m_flaskSpell))
        {
            if (DoCastSpell(me, m_flaskSpell) == SPELL_CAST_OK)
                return;
        }
    }

    if (m_role != ROLE_TANK && me->GetVictim() && CrowdControlMarkedTargets())
        return;

    switch (me->GetClass())
    {
        case CLASS_PALADIN:
            UpdateOutOfCombatAI_Paladin();
            break;
        case CLASS_SHAMAN:
            UpdateOutOfCombatAI_Shaman();
            break;
        case CLASS_HUNTER:
            UpdateOutOfCombatAI_Hunter();
            break;
        case CLASS_MAGE:
            UpdateOutOfCombatAI_Mage();
            break;
        case CLASS_PRIEST:
            UpdateOutOfCombatAI_Priest();
            break;
        case CLASS_WARLOCK:
            UpdateOutOfCombatAI_Warlock();
            break;
        case CLASS_WARRIOR:
            UpdateOutOfCombatAI_Warrior();
            break;
        case CLASS_ROGUE:
            UpdateOutOfCombatAI_Rogue();
            break;
        case CLASS_DRUID:
            UpdateOutOfCombatAI_Druid();
            break;
    }
}

//Function-更新戰鬥中AI
void PartyBotAI::UpdateInCombatAI()
{
	if (me->GetStandState() != UNIT_STAND_STATE_STAND)
		me->SetStandState(UNIT_STAND_STATE_STAND);

    Unit* pVictim = me->GetVictim();
	Unit* pLeader = GetPartyLeader();

	if (!CheckBossMechanics())
		return;		

    /*
    if (m_spamSpell)
    {
        if (Unit* pTarget = !m_spamGuid.IsEmpty() ? me->GetMap()->GetUnit(m_spamGuid) : me->GetVictim())
        {
            if (CanTryToCastSpell(pTarget, m_spamSpell))
                if (DoCastSpell(pTarget, m_spamSpell) == SPELL_CAST_OK)
                    return;
        }
    }
	*/
      
    if (m_role == ROLE_TANK)
    {
        // Defend party members.協防隊友
        if (!pVictim || pVictim->GetVictim() == me)
        {
            if (pVictim = SelectPartyAttackTarget())
            {
                me->AttackStop(true);
                AttackStart(pVictim);
            }
        }

        // Taunt target if its attacking someone else.如果隊友被攻擊則嘲諷敵人，從嘲諷法術陣列中挑選
        if (pVictim && pVictim->GetVictim() != me)
        {
            for (const auto& pSpellEntry : spellListTaunt)
            {
                if (CanTryToCastSpell(pVictim, pSpellEntry))
                {
                    if (DoCastSpell(pVictim, pSpellEntry) == SPELL_CAST_OK)
                        return;
                }
            }
        }
    }
    else if (CrowdControlMarkedTargets())
        return;

	if (m_role == ROLE_HEALER)
	{
		if (!pLeader->IsWithinLOSInMap(me))
			MoveToTarget(pLeader, 5.0f);
		else if (me->GetDistance(pLeader) < 20.0f)
		{
			me->GetMotionMaster()->Clear();
			me->GetMotionMaster()->MoveIdle();
		}
		else
		{
			MoveToTarget(pLeader, 15.0f);
		}
	}

	// Use potions
	// Restorative Potion
	if (m_restPotion &&
		IsValidDispelTarget(me, m_restPotion) &&
		CanTryToCastSpell(me, m_restPotion))
	{
		if (DoCastSpell(me, m_restPotion) == SPELL_CAST_OK)
			return;
	}

	// Emergency Healing Potion
	if (m_potionSpell &&
		(me->GetHealthPercent() <= 15.0f) &&
		CanTryToCastSpell(me, m_potionSpell))
	{
		if (DoCastSpell(me, m_potionSpell) == SPELL_CAST_OK)
			return;
	}

	if (pVictim)
	{
		if (!me->HasUnitState(UNIT_STAT_MELEE_ATTACKING) &&
			m_role != ROLE_HEALER &&
			IsValidHostileTarget(pVictim))
			AttackStart(pVictim);

		if (((m_role == ROLE_TANK || m_role == ROLE_MELEE_DPS) &&
			!pVictim->CanReachWithMeleeAutoAttack(me)) ||
			(m_role == ROLE_RANGE_DPS &&
				me->GetDistance(pVictim) > 28.0f))
		{
			ChaseTarget(pVictim);
		}
	}

    switch (me->GetClass())
    {
        case CLASS_PALADIN:
            UpdateInCombatAI_Paladin();
            break;
        case CLASS_SHAMAN:
            UpdateInCombatAI_Shaman();
            break;
        case CLASS_HUNTER:
            UpdateInCombatAI_Hunter();
            break;
        case CLASS_MAGE:
            UpdateInCombatAI_Mage();
            break;
        case CLASS_PRIEST:
            UpdateInCombatAI_Priest();
            break;
        case CLASS_WARLOCK:
            UpdateInCombatAI_Warlock();
            break;
        case CLASS_WARRIOR:
            UpdateInCombatAI_Warrior();
            break;
        case CLASS_ROGUE:
            UpdateInCombatAI_Rogue();
            break;
        case CLASS_DRUID:
            UpdateInCombatAI_Druid();
            break;
    }

    if (m_role == ROLE_TANK || m_role == ROLE_MELEE_DPS)
    {
		Unit* pVictim = me->GetVictim();
		if (pVictim && !pVictim->CanReachWithMeleeAutoAttack(me))
		{
			me->GetMotionMaster()->MoveChase(pVictim, 1.0f, 3.0f);
		}
    }

    if (me->GetVictim())
        UseTrinketEffects();
}

void PartyBotAI::UpdateOutOfCombatAI_Paladin()
{
    if (m_spells.paladin.pAura &&
        CanTryToCastSpell(me, m_spells.paladin.pAura))
    {
        if (DoCastSpell(me, m_spells.paladin.pAura) == SPELL_CAST_OK)
            return;
    }

    if (m_role == ROLE_TANK &&
        m_spells.paladin.pRighteousFury &&
        CanTryToCastSpell(me, m_spells.paladin.pRighteousFury)) //使用正義之怒
    {
        if (DoCastSpell(me, m_spells.paladin.pRighteousFury) == SPELL_CAST_OK)
            return;
    }

    if (m_spells.paladin.pBlessingBuff)
    {
		if (Player* pTarget = SelectBuffTarget(m_spells.paladin.pBlessingBuff, m_spells.paladin.pBlessingBuffRanged))
		{
			if (IsMeleeWeaponClass(pTarget->GetClass()) && CanTryToCastSpell(pTarget, m_spells.paladin.pBlessingBuff))
			{
				if (DoCastSpell(pTarget, m_spells.paladin.pBlessingBuff) == SPELL_CAST_OK)
				{
					m_isBuffing = true;
					return;
				}
			}

			if (!IsMeleeWeaponClass(pTarget->GetClass()) && CanTryToCastSpell(pTarget, m_spells.paladin.pBlessingBuffRanged))
			{
				if (DoCastSpell(pTarget, m_spells.paladin.pBlessingBuffRanged) == SPELL_CAST_OK)
				{
					m_isBuffing = true;
					return;
				}
			}
        }
    }

    if (m_isBuffing &&
       (!m_spells.paladin.pBlessingBuff ||
        !me->HasGCD(m_spells.paladin.pBlessingBuff)))
    {
        m_isBuffing = false;
    }

    if (m_spells.paladin.pCleanse) //清潔術
	{
		if (Unit* pFriend = SelectDispelTarget(m_spells.paladin.pCleanse))
		{
			if (CanTryToCastSpell(pFriend, m_spells.paladin.pCleanse))
			{
				if (DoCastSpell(pFriend, m_spells.paladin.pCleanse) == SPELL_CAST_OK)
					return;
			}
		}
    }

	if (m_role == ROLE_HEALER && FindAndHealInjuredAlly(90.0f))
        return;

	/*
	if (Unit* pVictim = me->GetVictim()) //嘗試用丟手雷進入戰鬥狀態
	{
		if (m_role == ROLE_TANK)
		{
			SpellEntry const* pSpellEntry = sSpellMgr.GetSpellEntry(PB_SPELL_IRON_GRENADE);
			if (me->GetEnemyCountInRadiusAround(pVictim, 5.0f) >= 2 && me->CastSpell(pVictim, pSpellEntry, true))//目標周圍3碼內敵人數量3個以上則丟手雷
			{
				if (DoCastSpell(pVictim, pSpellEntry) == SPELL_CAST_OK)
					return;
			}
		}
	}
	*/
}

void PartyBotAI::UpdateInCombatAI_Paladin()
{
    if (m_spells.paladin.pDivineShield &&
		(me->GetHealthPercent() < 25.0f) &&
       (m_role != ROLE_TANK) &&
        CanTryToCastSpell(me, m_spells.paladin.pDivineShield)) //聖盾術(無敵)
    {
        if (DoCastSpell(me, m_spells.paladin.pDivineShield) == SPELL_CAST_OK)
            return;
    }

    if (Unit* pFriend = me->FindLowestHpFriendlyUnit(30.0f, 70, true, me))
    {
        if (m_spells.paladin.pBlessingOfProtection &&
           !IsPhysicalDamageClass(pFriend->GetClass()) &&
            CanTryToCastSpell(pFriend, m_spells.paladin.pBlessingOfProtection))
        {
            if (DoCastSpell(pFriend, m_spells.paladin.pBlessingOfProtection) == SPELL_CAST_OK)
                return;
        }
        if (m_spells.paladin.pBlessingOfSacrifice &&
           (me->GetHealthPercent() > 80.0f) &&
            CanTryToCastSpell(pFriend, m_spells.paladin.pBlessingOfSacrifice))
        {
            if (DoCastSpell(pFriend, m_spells.paladin.pBlessingOfSacrifice) == SPELL_CAST_OK)
                return;
        }
        if (m_spells.paladin.pLayOnHands &&
           (pFriend->GetHealthPercent() < 15.0f) &&
            CanTryToCastSpell(pFriend, m_spells.paladin.pLayOnHands))
        {
            if (DoCastSpell(pFriend, m_spells.paladin.pLayOnHands) == SPELL_CAST_OK)
                return;
        }
    }

	// Critical Healing 危險狀態治療
	if (m_role == ROLE_TANK && me->GetHealthPercent() < 35.0f)
	{
		HealInjuredTargetDirect(me);
		return;
	}
	else
	{
		if (FindAndHealInjuredAlly(35.0f, 35.0f))
			return;
	}

	// Dispel
    if (m_spells.paladin.pCleanse) //清潔術
    {
        if (Unit* pFriend = SelectDispelTarget(m_spells.paladin.pCleanse)) //選擇要消除debuff的對象
        {
            if (CanTryToCastSpell(pFriend, m_spells.paladin.pCleanse))
            {
                if (DoCastSpell(pFriend, m_spells.paladin.pCleanse) == SPELL_CAST_OK)
                    return;
            }
        }
    }

    if (!me->GetAttackers().empty())
    {
        if (m_spells.paladin.pHolyShield &&
			GetAttackersInRangeCount(10.0f) <= 4 &&
            CanTryToCastSpell(me, m_spells.paladin.pHolyShield)) //神聖之盾
        {
            if (DoCastSpell(me, m_spells.paladin.pHolyShield) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.paladin.pTurnEvil &&
            m_role != ROLE_TANK)
        {
            Unit* pAttacker = SelectAttackerDifferentFrom(me->GetVictim());
            if (pAttacker && pAttacker->GetCreatureType() == CREATURE_TYPE_UNDEAD &&
                CanTryToCastSpell(pAttacker, m_spells.paladin.pTurnEvil))
            {
                if (DoCastSpell(pAttacker, m_spells.paladin.pTurnEvil) == SPELL_CAST_OK)
                    return;
            }
        }
    }
	//當身分是治療時
    if (m_role == ROLE_HEALER)
    {
        if (m_spells.paladin.pHolyShock &&
            me->GetHealthPercent() < 50.0f &&
            CanTryToCastSpell(me, m_spells.paladin.pHolyShock))
        {
            if (m_spells.paladin.pDivineFavor &&
                CanTryToCastSpell(me, m_spells.paladin.pDivineFavor))
            {
                DoCastSpell(me, m_spells.paladin.pDivineFavor);
            }

            if (DoCastSpell(me, m_spells.paladin.pHolyShock) == SPELL_CAST_OK)
                return;
        }

        if (FindAndHealInjuredAlly(85.0f, 45.0f))
            return;
    }
    else
    {

        if (Unit* pVictim = me->GetVictim())
        {

			bool const hasSeal = (m_spells.paladin.pSeal && me->HasAura(m_spells.paladin.pSeal->Id)) ||
				(m_spells.paladin.pSealOfWisdom && me->HasAura(m_spells.paladin.pSealOfWisdom->Id)) ||
				(m_spells.paladin.pSealOfCrusader && me->HasAura(m_spells.paladin.pSealOfCrusader->Id));

            if (!hasSeal)
			{
                if (me->GetPowerPercent(POWER_MANA) < 25.0f &&
					m_spells.paladin.pSealOfWisdom &&
					CanTryToCastSpell(me, m_spells.paladin.pSealOfWisdom))
					me->CastSpell(me, m_spells.paladin.pSealOfWisdom, false);
				else if (m_spells.paladin.pSealOfCrusader &&
					!(pVictim->HasAura(21183) || pVictim->HasAura(20303) || pVictim->HasAura(20302)
						|| pVictim->HasAura(20301) || pVictim->HasAura(20300) || pVictim->HasAura(20188)) &&
					CanTryToCastSpell(me, m_spells.paladin.pSealOfCrusader))
					me->CastSpell(me, m_spells.paladin.pSealOfCrusader, false);
				else if (m_spells.paladin.pSeal &&
					CanTryToCastSpell(me, m_spells.paladin.pSeal))
					me->CastSpell(me, m_spells.paladin.pSeal, false);
			}

            if (hasSeal && m_spells.paladin.pJudgement &&
               (me->GetPowerPercent(POWER_MANA) > 30.0f) &&
                CanTryToCastSpell(pVictim, m_spells.paladin.pJudgement)) //審判
            {
                if (DoCastSpell(pVictim, m_spells.paladin.pJudgement) == SPELL_CAST_OK)
                    return;
            }
            if (m_spells.paladin.pHammerOfJustice &&
               (pVictim->IsNonMeleeSpellCasted() ||
               (me->GetHealthPercent() < 20.0f && !me->GetAttackers().empty())) &&
                CanTryToCastSpell(pVictim, m_spells.paladin.pHammerOfJustice)) //制裁之錘(暈錘)
            {
                if (DoCastSpell(pVictim, m_spells.paladin.pHammerOfJustice) == SPELL_CAST_OK)
                    return;
            }
            if (m_spells.paladin.pHammerOfWrath &&
                pVictim->GetHealthPercent() < 20.0f &&
                CanTryToCastSpell(pVictim, m_spells.paladin.pHammerOfWrath)) //憤怒之錘
            {
                if (DoCastSpell(pVictim, m_spells.paladin.pHammerOfWrath) == SPELL_CAST_OK)
                    return;
            }
            if (m_spells.paladin.pConsecration &&
				((me->GetEnemyCountInRadiusAround(me, 10.0f) > 2) ||
				(me->HasAura(20059) && pVictim->CanReachWithMeleeAutoAttack(me))) &&
                CanTryToCastSpell(me, m_spells.paladin.pConsecration)) //10碼內敵人數量>=2則用奉獻
            {
                if (DoCastSpell(me, m_spells.paladin.pConsecration) == SPELL_CAST_OK)
                    return;
            }
            if (m_spells.paladin.pHolyShock &&
                CanTryToCastSpell(pVictim, m_spells.paladin.pHolyShock)) //神聖震擊
            {
                if (m_spells.paladin.pDivineFavor &&
                    CanTryToCastSpell(me, m_spells.paladin.pDivineFavor))
                {
                    DoCastSpell(me, m_spells.paladin.pDivineFavor);
                }

                if (DoCastSpell(pVictim, m_spells.paladin.pHolyShock) == SPELL_CAST_OK)
                    return;
            }
            if (m_spells.paladin.pExorcism &&
                pVictim->IsCreature() &&
                (pVictim->GetCreatureType() == CREATURE_TYPE_UNDEAD) &&
                CanTryToCastSpell(pVictim, m_spells.paladin.pExorcism)) //驅邪數
            {
                if (DoCastSpell(pVictim, m_spells.paladin.pExorcism) == SPELL_CAST_OK)
                    return;
            }
            if (m_spells.paladin.pHolyWrath &&
                pVictim->IsCreature() &&
               (pVictim->GetCreatureType() == CREATURE_TYPE_UNDEAD ||
                pVictim->GetCreatureType() == CREATURE_TYPE_DEMON) &&
               (me->GetAttackers().size() < 3) && // too much pushback
                CanTryToCastSpell(pVictim, m_spells.paladin.pHolyWrath)) //神聖憤怒
            {
                if (DoCastSpell(pVictim, m_spells.paladin.pHolyWrath) == SPELL_CAST_OK)
                    return;
            }
            /*if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE
                && !me->CanReachWithMeleeAutoAttack(pVictim))
            {
                me->GetMotionMaster()->MoveChase(pVictim);
            }*/
        }
    }

    if (m_spells.paladin.pBlessingOfFreedom &&
       (me->HasUnitState(UNIT_STAT_ROOT) || me->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED)) &&
        CanTryToCastSpell(me, m_spells.paladin.pBlessingOfFreedom)) //被定身時使用自由祝福解除
    {
        if (DoCastSpell(me, m_spells.paladin.pBlessingOfFreedom) == SPELL_CAST_OK)
            return;
    }

}

void PartyBotAI::UpdateOutOfCombatAI_Shaman()
{
    if (m_spells.shaman.pWeaponBuff &&
        CanTryToCastSpell(me, m_spells.shaman.pWeaponBuff))
    {
        if (CastWeaponBuff(m_spells.shaman.pWeaponBuff, EQUIPMENT_SLOT_MAINHAND) == SPELL_CAST_OK)
            return;
    }

    if (m_spells.shaman.pLightningShield &&
        CanTryToCastSpell(me, m_spells.shaman.pLightningShield))
    {
        if (DoCastSpell(me, m_spells.shaman.pLightningShield) == SPELL_CAST_OK)
            return;
    }

	if (m_role == ROLE_HEALER && FindAndHealInjuredAlly(90.0f))
        return;
	/*
    if (me->GetVictim())
    {
        if (SummonShamanTotems())
            return;

        UpdateInCombatAI_Shaman();
    }
	*/
}

void PartyBotAI::UpdateInCombatAI_Shaman()
{

    if (m_spells.shaman.pManaTideTotem &&
       (me->GetPowerPercent(POWER_MANA) < 50.0f) &&
        CanTryToCastSpell(me, m_spells.shaman.pManaTideTotem))
    {
        if (DoCastSpell(me, m_spells.shaman.pManaTideTotem) == SPELL_CAST_OK)
            return;
    }

	// Critical Healing
	if (FindAndHealInjuredAlly(35.0f, 35.0f))
		return;

	// Dispels
	if (m_spells.shaman.pCureDisease)
	{
		if (Unit* pFriend = SelectDispelTarget(m_spells.shaman.pCureDisease))
		{
			if (CanTryToCastSpell(pFriend, m_spells.shaman.pCureDisease))
			{
				if (DoCastSpell(pFriend, m_spells.shaman.pCureDisease) == SPELL_CAST_OK)
					return;
			}
		}
	}

	if (m_spells.shaman.pCurePoison)
	{
		if (Unit* pFriend = SelectDispelTarget(m_spells.shaman.pCurePoison))
		{
			if (CanTryToCastSpell(pFriend, m_spells.shaman.pCurePoison))
			{
				if (DoCastSpell(pFriend, m_spells.shaman.pCurePoison) == SPELL_CAST_OK)
					return;
			}
		}
	}

	if (m_role == ROLE_HEALER)
	{
		FindAndHealInjuredAlly(85.0f, 45.0f);
		return;
	}
	else
    {
        if (Unit* pVictim = me->GetVictim())
        {
            if (SummonShamanTotems())
                return;

            if (m_spells.shaman.pElementalMastery &&
                me->GetAttackers().empty() &&
                CanTryToCastSpell(me, m_spells.shaman.pElementalMastery))
            {
                if (DoCastSpell(me, m_spells.shaman.pElementalMastery) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.shaman.pEarthShock &&
                pVictim->IsNonMeleeSpellCasted(false, false, true) &&
                CanTryToCastSpell(pVictim, m_spells.shaman.pEarthShock))
            {
                if (DoCastSpell(pVictim, m_spells.shaman.pEarthShock) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.shaman.pFrostShock &&
                pVictim->IsMoving() &&
                CanTryToCastSpell(pVictim, m_spells.shaman.pFrostShock))
            {
                if (DoCastSpell(pVictim, m_spells.shaman.pFrostShock) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.shaman.pStormstrike &&
                CanTryToCastSpell(pVictim, m_spells.shaman.pStormstrike))
            {
                if (DoCastSpell(pVictim, m_spells.shaman.pStormstrike) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.shaman.pChainLightning &&
                CanTryToCastSpell(pVictim, m_spells.shaman.pChainLightning))
            {
                if (DoCastSpell(pVictim, m_spells.shaman.pChainLightning) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.shaman.pPurge &&
                IsValidDispelTarget(pVictim, m_spells.shaman.pPurge) &&
                CanTryToCastSpell(pVictim, m_spells.shaman.pPurge))
            {
                if (DoCastSpell(pVictim, m_spells.shaman.pPurge) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.shaman.pFlameShock &&
                CanTryToCastSpell(pVictim, m_spells.shaman.pFlameShock))
            {
                if (DoCastSpell(pVictim, m_spells.shaman.pFlameShock) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.shaman.pLightningBolt &&
               (m_role == ROLE_RANGE_DPS || !me->CanReachWithMeleeAutoAttack(pVictim)) &&
                CanTryToCastSpell(pVictim, m_spells.shaman.pLightningBolt))
            {
                if (DoCastSpell(pVictim, m_spells.shaman.pLightningBolt) == SPELL_CAST_OK)
                    return;
            }
        }
    }

    if (SummonShamanTotems())
        return;

}

//更新獵人戰鬥外AI function
void PartyBotAI::UpdateOutOfCombatAI_Hunter()
{
	if (m_spells.hunter.pAspectOfTheHawk &&
        CanTryToCastSpell(me, m_spells.hunter.pAspectOfTheHawk)) //雄鷹守護
    {
        if (DoCastSpell(me, m_spells.hunter.pAspectOfTheHawk) == SPELL_CAST_OK)
            return;
    }

	if (m_spells.hunter.pTrueshotAura &&
		CanTryToCastSpell(me, m_spells.hunter.pTrueshotAura))
	{
		if (DoCastSpell(me, m_spells.hunter.pTrueshotAura) == SPELL_CAST_OK)
		{
			m_isBuffing = true;
			return;
		}
	}

    SummonPetIfNeeded(); //沒有敵人則召喚寵物
    /*
    //如果取得了敵人則進行判斷
    if (Unit* pVictim = me->GetVictim())
    {
        if (m_spells.hunter.pHuntersMark &&
            CanTryToCastSpell(pVictim, m_spells.hunter.pHuntersMark)) //獵人印記
        {
            if (DoCastSpell(pVictim, m_spells.hunter.pHuntersMark) == SPELL_CAST_OK)
                return;
        }

        if (Pet* pPet = me->GetPet()) //如果有寵物則讓寵物攻擊
        {
            if (!pPet->GetVictim())
            {
                pPet->GetCharmInfo()->SetIsCommandAttack(true);
                pPet->AI()->AttackStart(pVictim);
            }
        }

        UpdateInCombatAI_Hunter(); //進入獵人戰鬥函式
    }
    */
    /*
	else if (Pet* pPet = me->GetPet()) //反之，非戰鬥中則進行判斷寵物召喚或復活
		{
			if (!pPet->IsAlive()  &&
				CanTryToCastSpell(pPet, m_spells.hunter.pRevivePet))
			{
				if (DoCastSpell(pPet, m_spells.hunter.pRevivePet) == SPELL_CAST_OK)
					return;
			}
		}
     */
}

//更新獵人戰鬥中AI function
void PartyBotAI::UpdateInCombatAI_Hunter()
{
    if (Unit* pVictim = me->GetVictim())
    {
		if (!me->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL) &&
			me->GetDistance(pVictim) <= 30.0f)
		{
			std::vector<const SpellEntry*> vTraps;

			if (m_spells.hunter.pFrostTrap &&
				CanTryToCastSpell(me, m_spells.hunter.pFrostTrap))
				vTraps.push_back(m_spells.hunter.pFrostTrap);
			if (m_spells.hunter.pFreezingTrap &&
				CanTryToCastSpell(me, m_spells.hunter.pFreezingTrap))
				vTraps.push_back(m_spells.hunter.pFreezingTrap);
			if (m_spells.hunter.pImmolationTrap &&
				CanTryToCastSpell(me, m_spells.hunter.pImmolationTrap))
				vTraps.push_back(m_spells.hunter.pImmolationTrap);
			if (m_spells.hunter.pExplosiveTrap &&
				CanTryToCastSpell(me, m_spells.hunter.pExplosiveTrap))
				vTraps.push_back(m_spells.hunter.pExplosiveTrap);

			if (!vTraps.empty())
			{
				const SpellEntry* pTrap = SelectRandomContainerElement(vTraps);
				if (DoCastSpell(me, pTrap) == SPELL_CAST_OK)
					return;
			}
		}

        if (Pet* pPet = me->GetPet())
        {
            if (!pPet->GetVictim())
            {
                pPet->GetCharmInfo()->SetIsCommandAttack(true);
                pPet->AI()->AttackStart(pVictim);
            }
        }

		if (m_spells.hunter.pHuntersMark &&
			CanTryToCastSpell(pVictim, m_spells.hunter.pHuntersMark))
		{
			if (DoCastSpell(pVictim, m_spells.hunter.pHuntersMark) == SPELL_CAST_OK)
				return;
		}

        if (me->HasSpell(PB_SPELL_AUTO_SHOT) &&
			!me->IsMoving() &&
			(me->GetCombatDistance(pVictim) > 8.0f) &&
			!me->IsNonMeleeSpellCasted()) //如果有自動射擊法術且不再移動中且與敵人相距>8碼且沒有近戰範圍法術使用中，則使用自動射擊
		{
			switch (me->CastSpell(pVictim, PB_SPELL_AUTO_SHOT, false))
			{
			case SPELL_FAILED_NEED_AMMO:
			case SPELL_FAILED_NO_AMMO:
			{
				AddHunterAmmo();
				break;
			}
			}
		}

		// Remove Frenzy
		if (pVictim->HasAuraType(SPELL_AURA_MOD_MELEE_HASTE) &&
			m_spells.hunter.pTranquilizingShot &&
			CanTryToCastSpell(pVictim, m_spells.hunter.pTranquilizingShot))
		{
			if (DoCastSpell(pVictim, m_spells.hunter.pTranquilizingShot) == SPELL_CAST_OK)
				return;
		}

        if (m_spells.hunter.pVolley &&
			m_aoeSpellTimer <= 0 &&
            pVictim->GetHealthPercent() < 75.0f &&
            (me->GetEnemyCountInRadiusAround(pVictim, 10.0f) > 3) &&
            CanTryToCastSpell(pVictim, m_spells.hunter.pVolley)) //如果有亂射法術且「目標10碼內敵人>」2且可嘗試使用亂射
        {
            if (DoCastSpell(pVictim, m_spells.hunter.pVolley) == SPELL_CAST_OK)
                return;
        }

		if (m_spells.hunter.pRapidFire &&
			(me->GetEnemyCountInRadiusAround(pVictim, 10.0f) > 2) &&
			CanTryToCastSpell(me, m_spells.hunter.pRapidFire)) //如果有亂射法術且「目標10碼內敵人>」2且可嘗試使用急速射擊。WIP-還須加上判斷敵方為精英的條件
		{
			if (DoCastSpell(pVictim, m_spells.hunter.pRapidFire) == SPELL_CAST_OK)
				return;
		}

        if (pVictim->IsMoving() &&
            !pVictim->HasUnitState(UNIT_STAT_ROOT) &&
            !pVictim->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED)) //若敵方移動且未定身且身上無減速debuff則使用以下技能
        {
            if (m_spells.hunter.pConcussiveShot &&
                CanTryToCastSpell(pVictim, m_spells.hunter.pConcussiveShot)) //震盪射擊
            {
                if (DoCastSpell(pVictim, m_spells.hunter.pConcussiveShot) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.hunter.pIntimidation &&
                CanTryToCastSpell(pVictim, m_spells.hunter.pIntimidation)) //脅迫
            {
                if (DoCastSpell(pVictim, m_spells.hunter.pIntimidation) == SPELL_CAST_OK)
                    return;
            }
        }

		if (m_spells.hunter.pBestialWrath &&
			CanTryToCastSpell(pVictim, m_spells.hunter.pBestialWrath)) //狂野怒火
		{
			if (DoCastSpell(pVictim, m_spells.hunter.pBestialWrath) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.hunter.pRapidFire &&
			pVictim->GetHealth() > (2 * me->GetMaxHealth()) &&
			CanTryToCastSpell(pVictim, m_spells.hunter.pRapidFire))
		{
			if (DoCastSpell(pVictim, m_spells.hunter.pRapidFire) == SPELL_CAST_OK)
				return;
		}

		// Apply Sting
		if (m_spells.hunter.pViperSting &&
			pVictim->IsCaster() &&
			pVictim->GetPowerPercent(POWER_MANA) > 10.0f)
		{
			if (CanTryToCastSpell(pVictim, m_spells.hunter.pViperSting) &&
				DoCastSpell(pVictim, m_spells.hunter.pSerpentSting) == SPELL_CAST_OK)
				return;
		}
		else if (m_spells.hunter.pSerpentSting &&
            CanTryToCastSpell(pVictim, m_spells.hunter.pSerpentSting)) //毒蛇釘刺
        {
            if (DoCastSpell(pVictim, m_spells.hunter.pSerpentSting) == SPELL_CAST_OK)
                return;
        }

		if (m_spells.hunter.pArcaneShot &&
			CanTryToCastSpell(pVictim, m_spells.hunter.pArcaneShot))
		{
			if (DoCastSpell(pVictim, m_spells.hunter.pArcaneShot) == SPELL_CAST_OK)
				return;
		}

        if (m_spells.hunter.pMultiShot &&
			m_aoeSpellTimer <= 0 &&
            CanTryToCastSpell(pVictim, m_spells.hunter.pMultiShot)) //多重射擊
        {
            if (DoCastSpell(pVictim, m_spells.hunter.pMultiShot) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.hunter.pAimedShot &&
            CanTryToCastSpell(pVictim, m_spells.hunter.pAimedShot)) //瞄準射擊
        {
            if (DoCastSpell(pVictim, m_spells.hunter.pAimedShot) == SPELL_CAST_OK)
                return;
        }

        if (GetAttackersInRangeCount(8.0f))
        {
            Unit* pAttacker = *me->GetAttackers().begin();

			if (m_spells.hunter.pDeterrence &&
				(me->GetHealthPercent() < 50.0f) &&
				CanTryToCastSpell(me, m_spells.hunter.pDeterrence)) //威攝
			{
				if (DoCastSpell(me, m_spells.hunter.pDeterrence) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.hunter.pFeignDeath &&
				(me->GetHealthPercent() < 15.0f) &&
				CanTryToCastSpell(me, m_spells.hunter.pFeignDeath)) //假死
			{
				if (DoCastSpell(me, m_spells.hunter.pFeignDeath) == SPELL_CAST_OK)
					return;
			}

            if (m_spells.hunter.pDisengage &&
                CanTryToCastSpell(pAttacker, m_spells.hunter.pDisengage)) //逃脫
            {
                if (DoCastSpell(pAttacker, m_spells.hunter.pDisengage) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.hunter.pAspectOfTheMonkey &&
                CanTryToCastSpell(me, m_spells.hunter.pAspectOfTheMonkey)) //靈猴守護
            {
                if (DoCastSpell(me, m_spells.hunter.pAspectOfTheMonkey) == SPELL_CAST_OK)
                    return;
            }

			if (m_spells.hunter.pScareBeast &&
				CanTryToCastSpell(pAttacker, m_spells.hunter.pScareBeast)) //恐嚇野獸
			{
				if (DoCastSpell(pAttacker, m_spells.hunter.pScareBeast) == SPELL_CAST_OK)
					return;
			}

        }

        if (pVictim->CanReachWithMeleeAutoAttack(me)) //獵人與敵方處於近身的情形
        {
            if (m_spells.hunter.pCounterattack &&
                CanTryToCastSpell(pVictim, m_spells.hunter.pCounterattack)) //反擊
            {
                if (DoCastSpell(pVictim, m_spells.hunter.pCounterattack))
                    return;
            }
            if (m_spells.hunter.pWingClip &&
                CanTryToCastSpell(pVictim, m_spells.hunter.pWingClip)) //摔拌
            {
                if (DoCastSpell(pVictim, m_spells.hunter.pWingClip))
                    return;
            }

            if (m_spells.hunter.pMongooseBite &&
                CanTryToCastSpell(pVictim, m_spells.hunter.pMongooseBite)) //貓鼬撕咬
            {
                if (DoCastSpell(pVictim, m_spells.hunter.pMongooseBite))
                    return;
            }

            if (m_spells.hunter.pRaptorStrike &&
                CanTryToCastSpell(pVictim, m_spells.hunter.pRaptorStrike)) //猛禽一擊
            {
                if (DoCastSpell(pVictim, m_spells.hunter.pRaptorStrike))
                    return;
            }
        }
        else
        {
            if (m_spells.hunter.pAspectOfTheHawk &&
                CanTryToCastSpell(me, m_spells.hunter.pAspectOfTheHawk)) //鷹眼術
            {
                if (DoCastSpell(me, m_spells.hunter.pAspectOfTheHawk) == SPELL_CAST_OK)
                    return;
            }
        }

        if (!me->HasUnitState(UNIT_STAT_ROOT) &&
            (me->GetCombatDistance(pVictim) < 8.0f) &&
            (m_role != ROLE_MELEE_DPS) &&
             me->GetMotionMaster()->GetCurrentMovementGeneratorType() != DISTANCING_MOTION_TYPE) //當獵人是「站立狀態」且「與被攻擊目標距離小於8碼」且「身分非進戰DD」且「未知條件?」
        {
			if (!me->IsStopped()) //如果本身動作未停止
                me->StopMoving(); //則停止移動
            me->GetMotionMaster()->Clear(); //清除移動狀態
            //if (HunterRunAwayFromTarget(pVictim))
			RunAwayFromTarget(pVictim);
            return;
        }
    }
}

void PartyBotAI::UpdateOutOfCombatAI_Mage()
{
    if (m_spells.mage.pArcaneBrilliance) //秘法光輝
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.mage.pArcaneBrilliance))
        {
            if (CanTryToCastSpell(pTarget, m_spells.mage.pArcaneBrilliance))
            {
                if (DoCastSpell(pTarget, m_spells.mage.pArcaneBrilliance) == SPELL_CAST_OK)
				{
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }
    else if (m_spells.mage.pArcaneIntellect) //秘法智慧
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.mage.pArcaneIntellect))
        {
            if (CanTryToCastSpell(pTarget, m_spells.mage.pArcaneIntellect))
            {
                if (DoCastSpell(pTarget, m_spells.mage.pArcaneIntellect) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }

    if (m_spells.mage.pIceArmor &&
        CanTryToCastSpell(me, m_spells.mage.pIceArmor)) //冰甲術
    {
        if (DoCastSpell(me, m_spells.mage.pIceArmor) == SPELL_CAST_OK)
        {
            m_isBuffing = true;
            return;
        }
    }

    if (m_isBuffing &&
       (!m_spells.mage.pArcaneIntellect ||
        !me->HasGCD(m_spells.mage.pArcaneIntellect)))
    {
        m_isBuffing = false;
    }

	// Decurse
	if (m_spells.mage.pRemoveLesserCurse) //解除次級詛咒
	{
		if (Unit* pFriend = SelectDispelTarget(m_spells.mage.pRemoveLesserCurse))
		{
			if (CanTryToCastSpell(pFriend, m_spells.mage.pRemoveLesserCurse))
			{
				if (DoCastSpell(pFriend, m_spells.mage.pRemoveLesserCurse) == SPELL_CAST_OK)
					return;
			}
		}
	}
    /*
    if (me->GetVictim())
        UpdateInCombatAI_Mage();
    */
}

void PartyBotAI::UpdateInCombatAI_Mage() //法師戰鬥中AI
{
    // Decurse - Priority for boss fights //解除詛咒，優先用於BOSS戰
    if (m_spells.mage.pRemoveLesserCurse)
    {
        if (Unit* pFriend = SelectDispelTarget(m_spells.mage.pRemoveLesserCurse))
        {
            if (CanTryToCastSpell(pFriend, m_spells.mage.pRemoveLesserCurse))
            {
                if (DoCastSpell(pFriend, m_spells.mage.pRemoveLesserCurse) == SPELL_CAST_OK)
                    return;
            }
        }
    }

    if (Unit* pVictim = me->GetVictim())
    {
        if (m_spells.mage.pCombustion &&
            CanTryToCastSpell(me, m_spells.mage.pCombustion))
        {
            if (DoCastSpell(me, m_spells.mage.pCombustion) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.mage.pPyroblast &&
           ((m_spells.mage.pPresenceOfMind && me->HasAura(m_spells.mage.pPresenceOfMind->Id)) ||
            (!pVictim->IsInCombat() && (pVictim->GetMaxHealth() > me->GetMaxHealth()) && (me->GetDistance(pVictim) > 30.0f))) &&
            CanTryToCastSpell(pVictim, m_spells.mage.pPyroblast))
        {
            if (DoCastSpell(pVictim, m_spells.mage.pPyroblast) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.mage.pIceBlock &&
			me->GetHealthPercent() < 10.0f &&
            CanTryToCastSpell(me, m_spells.mage.pIceBlock))
        {
            if (DoCastSpell(me, m_spells.mage.pIceBlock) == SPELL_CAST_OK)
                return;
        }

		if (!me->GetAttackers().empty())
        {
			if (m_spells.mage.pIceBarrier &&
				CanTryToCastSpell(me, m_spells.mage.pIceBarrier))
			{
				if (DoCastSpell(me, m_spells.mage.pIceBarrier) == SPELL_CAST_OK)
					return;
			}
        }

		if (GetAttackersInRangeCount(10.0f) > 1)
        {
            if (m_spells.mage.pManaShield &&
               (me->GetPowerPercent(POWER_MANA) > 20.0f) &&
                CanTryToCastSpell(me, m_spells.mage.pManaShield))
            {
                if (DoCastSpell(me, m_spells.mage.pManaShield) == SPELL_CAST_OK)
                    return;
            }

            if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != DISTANCING_MOTION_TYPE)
            {
                if (m_spells.mage.pBlink &&
                    (me->HasUnitState(UNIT_STAT_CAN_NOT_MOVE) ||
                        me->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED)) &&
                    CanTryToCastSpell(me, m_spells.mage.pBlink))
                {
                    if (me->GetMotionMaster()->GetCurrentMovementGeneratorType())
                        me->GetMotionMaster()->Clear();

                    if (DoCastSpell(me, m_spells.mage.pBlink) == SPELL_CAST_OK)
                        return;
                }

                if (!me->HasUnitState(UNIT_STAT_CAN_NOT_MOVE)) //當法師是「非」「不可移動以外的狀態」(其實就等於不可移動的狀態)時
                {
                    //施放冰霜新星條件=1.被攻擊目標狀態非定身 2.被攻擊目標狀態「非」「不可反應或失去控制」
					if (m_spells.mage.pFrostNova &&
                       !pVictim->HasUnitState(UNIT_STAT_ROOT) &&
                       !pVictim->HasUnitState(UNIT_STAT_CAN_NOT_REACT_OR_LOST_CONTROL) &&
                        CanTryToCastSpell(me, m_spells.mage.pFrostNova))
                    {
                        DoCastSpell(me, m_spells.mage.pFrostNova);
                        RunAwayFromTarget(pVictim);
                    }
					//定腳目標後逃開的行為模式
                    //if (MageRunAwayFromTarget(pVictim))
                }
            }
        }

		if (me->GetEnemyCountInRadiusAround(me, 10.0f) > 2 &&
			m_aoeSpellTimer <= 0)
		{
			if (m_spells.mage.pImprovedArcaneExplosion &&
                m_spells.mage.pArcaneExplosion &&
                CanTryToCastSpell(me, m_spells.mage.pArcaneExplosion))
            {
                if (DoCastSpell(me, m_spells.mage.pArcaneExplosion) == SPELL_CAST_OK)
                    return;
            }

			if (m_spells.mage.pBlastWave &&
				CanTryToCastSpell(me, m_spells.mage.pBlastWave))
			{
				if (DoCastSpell(me, m_spells.mage.pBlastWave) == SPELL_CAST_OK)
					return;
			}

            if (m_spells.mage.pConeofCold && !me->IsMoving() &&
                CanTryToCastSpell(me, m_spells.mage.pConeofCold))
            {
                if (DoCastSpell(pVictim, m_spells.mage.pConeofCold) == SPELL_CAST_OK)
                    return;
            }

			if (m_spells.mage.pArcaneExplosion &&
				CanTryToCastSpell(me, m_spells.mage.pArcaneExplosion))
			{
				if (DoCastSpell(me, m_spells.mage.pArcaneExplosion) == SPELL_CAST_OK)
                    return;
            }

        }

        if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == DISTANCING_MOTION_TYPE)
            return;

        if (m_spells.mage.pCounterspell &&
            pVictim->IsNonMeleeSpellCasted(false, false, true) &&
            CanTryToCastSpell(pVictim, m_spells.mage.pCounterspell)) //法術反制
        {
            if (DoCastSpell(pVictim, m_spells.mage.pCounterspell) == SPELL_CAST_OK)
                return;
        }

		if (me->GetEnemyCountInRadiusAround(pVictim, 10.0f) > 3 &&
			m_aoeSpellTimer <= 0 &&
			pVictim->GetHealthPercent() < 75.0f)
        {
			if (m_spells.mage.pImprovedArcaneExplosion &&
                m_spells.mage.pArcaneExplosion &&
                CanTryToCastSpell(pVictim, m_spells.mage.pArcaneExplosion))
            {
                // Chase victim at close range to use Arcane Explosion.
                // Spell is cast on a previous check when in range.
                me->GetMotionMaster()->MoveChase(pVictim, 5.0f);
            }
			if (m_spells.mage.pImprovedFlamestrike &&
                m_spells.mage.pFlamestrike &&
                CanTryToCastSpell(pVictim, m_spells.mage.pFlamestrike)) //如果是天賦火法則用烈焰風暴
            {
                if (DoCastSpell(pVictim, m_spells.mage.pFlamestrike) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.mage.pBlizzard &&
                CanTryToCastSpell(pVictim, m_spells.mage.pBlizzard)) //暴風雪
            {
                if (DoCastSpell(pVictim, m_spells.mage.pBlizzard) == SPELL_CAST_OK)
                    return;
             }
         }

        if (m_spells.mage.pPolymorph)
        {
            if (Unit* pTarget = SelectAttackerDifferentFrom(pVictim))
            {
                if (pTarget->GetHealthPercent() > 20.0f &&
                    CanTryToCastSpell(pTarget, m_spells.mage.pPolymorph) &&
                    CanUseCrowdControl(m_spells.mage.pPolymorph, pTarget))
                {
                    if (DoCastSpell(pTarget, m_spells.mage.pPolymorph) == SPELL_CAST_OK)
                        return;
                }
            }
        }

		if (m_spells.mage.pCombustion &&
			CanTryToCastSpell(pVictim, m_spells.mage.pCombustion))
		{
			if (DoCastSpell(pVictim, m_spells.mage.pCombustion) == SPELL_CAST_OK)
				return;
		}

        if (m_spells.mage.pArcanePower &&
            (me->GetPowerPercent(POWER_MANA) > 20.0f) &&
            CanTryToCastSpell(me, m_spells.mage.pArcanePower))
        {
            if (DoCastSpell(me, m_spells.mage.pArcanePower) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.mage.pPresenceOfMind &&
            CanTryToCastSpell(me, m_spells.mage.pPresenceOfMind)) //氣定神閒
        {
            if (DoCastSpell(me, m_spells.mage.pPresenceOfMind) == SPELL_CAST_OK)
                return;
		}

		// If has improved fireball, try fire spells
		if (m_spells.mage.pImprovedFireball)
        {
            if (m_spells.mage.pFireBlast &&
                CanTryToCastSpell(pVictim, m_spells.mage.pFireBlast)) //火焰衝擊
            {
                if (DoCastSpell(pVictim, m_spells.mage.pFireBlast) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.mage.pScorch &&
                CanTryToCastSpell(pVictim, m_spells.mage.pScorch)) //灼燒
            {
				if (pVictim->GetHealth() < 10.0f)
				{
					if (DoCastSpell(pVictim, m_spells.mage.pScorch) == SPELL_CAST_OK)
						return;
				}
				else if (m_spells.mage.pImprovedScorch)
				{
					// Fire vulnerability aura 22959
					SpellAuraHolder* pSpellAuraHolder = pVictim->GetSpellAuraHolder(22959);
					if (!pSpellAuraHolder || pSpellAuraHolder->GetStackAmount() < 5)
					{
						if (DoCastSpell(pVictim, m_spells.mage.pScorch) == SPELL_CAST_OK)
							return;
					}
				}
            }

            if (m_spells.mage.pFireball &&
				CanTryToCastStackSpell(pVictim, m_spells.mage.pFireball, 2))
            {
                if (DoCastSpell(pVictim, m_spells.mage.pFireball) == SPELL_CAST_OK)
                    return;
            }
        }

		// If has improved Arcane Missiles, try to use it
		if (m_spells.mage.pImprovedArcaneMissiles &&
			m_spells.mage.pArcaneMissiles &&
			CanTryToCastStackSpell(pVictim, m_spells.mage.pArcaneMissiles, 2))
		{
			if (DoCastSpell(pVictim, m_spells.mage.pArcaneMissiles) == SPELL_CAST_OK)
				return;
		}

		// Nothing cast, try Frostbolt...
		if (m_spells.mage.pFrostbolt &&
			CanTryToCastStackSpell(pVictim, m_spells.mage.pFrostbolt, 2))
        {
            if (DoCastSpell(pVictim, m_spells.mage.pFrostbolt) == SPELL_CAST_OK)
                return;
        }

		// If immune, try normal fireball
		if (m_spells.mage.pFireball &&
			CanTryToCastStackSpell(pVictim, m_spells.mage.pFireball, 2))
		{
			if (DoCastSpell(pVictim, m_spells.mage.pFireball) == SPELL_CAST_OK)
				return;
		}

        if (m_spells.mage.pEvocation &&
           (me->GetPowerPercent(POWER_MANA) < 30.0f) &&
           (GetAttackersInRangeCount(10.0f) == 0) &&
            CanTryToCastSpell(me, m_spells.mage.pEvocation))
        {
            if (DoCastSpell(me, m_spells.mage.pEvocation) == SPELL_CAST_OK)
                return;
        }

        if (me->HasSpell(PB_SPELL_SHOOT_WAND) &&
           !me->IsMoving() &&
           !me->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL))
            me->CastSpell(pVictim, PB_SPELL_SHOOT_WAND, false);
    }
}

void PartyBotAI::UpdateOutOfCombatAI_Priest()
{
    if (m_spells.priest.pPrayerofFortitude)//堅韌禱言
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.priest.pPrayerofFortitude))
        {
            if (CanTryToCastSpell(pTarget, m_spells.priest.pPrayerofFortitude))
            {
                if (DoCastSpell(pTarget, m_spells.priest.pPrayerofFortitude) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }
    else if (m_spells.priest.pPowerWordFortitude)//真言術：韌
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.priest.pPowerWordFortitude))
        {
            if (CanTryToCastSpell(pTarget, m_spells.priest.pPowerWordFortitude))
            {
                if (DoCastSpell(pTarget, m_spells.priest.pPowerWordFortitude) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }

    if (m_spells.priest.pPrayerofSpirit) //精神禱言
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.priest.pPrayerofSpirit))
        {
            if (CanTryToCastSpell(pTarget, m_spells.priest.pPrayerofSpirit))
            {
                if (DoCastSpell(pTarget, m_spells.priest.pPrayerofSpirit) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }
    else if (m_spells.priest.pDivineSpirit) //神聖之靈
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.priest.pDivineSpirit))
        {
            if (CanTryToCastSpell(me, m_spells.priest.pDivineSpirit))
            {
                if (DoCastSpell(me, m_spells.priest.pDivineSpirit) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }

    if (m_spells.priest.pShadowProtection) //防護暗影
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.priest.pShadowProtection))
        {
            if (CanTryToCastSpell(pTarget, m_spells.priest.pShadowProtection))
            {
                if (DoCastSpell(pTarget, m_spells.priest.pShadowProtection) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }

    if (m_spells.priest.pInnerFire &&
        CanTryToCastSpell(me, m_spells.priest.pInnerFire)) //心靈之火
    {
        if (DoCastSpell(me, m_spells.priest.pInnerFire) == SPELL_CAST_OK)
        {
            m_isBuffing = true;
            return;
        }
    }

    if (m_spells.priest.pTouchOfWeakness &&
        CanTryToCastSpell(me, m_spells.priest.pTouchOfWeakness)) //虛弱之觸
    {
        if (DoCastSpell(me, m_spells.priest.pTouchOfWeakness) == SPELL_CAST_OK)
        {
            m_isBuffing = true;
            return;
        }
    }

    if (m_isBuffing &&
       (!m_spells.priest.pPowerWordFortitude ||
        !me->HasGCD(m_spells.priest.pPowerWordFortitude)))
    {
        m_isBuffing = false;
    }

	// Dispels
    if (m_spells.priest.pDispelMagic) //驅散魔法
    {
        if (Unit* pFriend = SelectDispelTarget(m_spells.priest.pDispelMagic))
        {
            if (CanTryToCastSpell(pFriend, m_spells.priest.pDispelMagic))
            {
                if (DoCastSpell(pFriend, m_spells.priest.pDispelMagic) == SPELL_CAST_OK)
                    return;
            }
        }
    }

    if (m_spells.priest.pAbolishDisease) //驅除疾病
    {
        if (Unit* pFriend = SelectDispelTarget(m_spells.priest.pAbolishDisease))
        {
            if (CanTryToCastSpell(pFriend, m_spells.priest.pAbolishDisease))
            {
                if (DoCastSpell(pFriend, m_spells.priest.pAbolishDisease) == SPELL_CAST_OK)
                    return;
            }
        }
    }

	if (m_role == ROLE_HEALER && FindAndHealInjuredAlly(90.0f))
        return;
    /*
    if (me->GetVictim())
        UpdateInCombatAI_Priest();
    */
}

void PartyBotAI::UpdateInCombatAI_Priest() //牧師戰鬥中AI
{

    if (!me->GetAttackers().empty())
    {
        if (m_spells.priest.pFade &&
            CanTryToCastSpell(me, m_spells.priest.pFade))
        {
            if (DoCastSpell(me, m_spells.priest.pFade) == SPELL_CAST_OK)
                return;
        }

        if (me->GetHealthPercent() < 50.0f)
        {
           if (m_spells.priest.pPsychicScream &&
                GetAttackersInRangeCount(10.0f) > 1 &&
                CanTryToCastSpell(me, m_spells.priest.pPsychicScream)) //當BOT血量<50%時，10碼內敵人>1則使用心靈尖嘯
           {
                if (DoCastSpell(me, m_spells.priest.pPsychicScream) == SPELL_CAST_OK)
                    return;
           }
        }

        if (m_spells.priest.pPowerWordShield &&
			CanTryToCastSpell(me, m_spells.priest.pPowerWordShield)) //真言術·盾
        {
			if (DoCastSpell(me, m_spells.priest.pPowerWordShield) == SPELL_CAST_OK)
				return;
        }

        if (m_spells.priest.pShackleUndead) //束縛不死生物
        {
            Unit* pAttacker = *me->GetAttackers().begin();
            if ((pAttacker->GetHealth() > me->GetHealth()) &&
                CanTryToCastSpell(pAttacker, m_spells.priest.pShackleUndead) &&
                CanUseCrowdControl(m_spells.priest.pShackleUndead, pAttacker))
            {
                if (DoCastSpell(pAttacker, m_spells.priest.pShackleUndead) == SPELL_CAST_OK)
                    RunAwayFromTarget(pAttacker);
                    return;
            }
        }
    }

    if (m_spells.priest.pInnerFocus &&
       (me->GetPowerPercent(POWER_MANA) < 50.0f) &&
        CanTryToCastSpell(me, m_spells.priest.pInnerFocus)) //心靈專注
    {
        DoCastSpell(me, m_spells.priest.pInnerFocus);
    }

	// Critical Healing
	if (FindAndHealInjuredAlly(35.0f, 35.0f))
		return;

	// Dispels
	if (m_spells.priest.pDispelMagic)
	{
		if (Unit* pFriend = SelectDispelTarget(m_spells.priest.pDispelMagic))
		{
			if (CanTryToCastSpell(pFriend, m_spells.priest.pDispelMagic))
			{
				if (DoCastSpell(pFriend, m_spells.priest.pDispelMagic) == SPELL_CAST_OK)
					return;
			}
		}
	}

	if (m_spells.priest.pAbolishDisease)
	{
		if (Unit* pFriend = SelectDispelTarget(m_spells.priest.pAbolishDisease))
		{
			if (CanTryToCastSpell(pFriend, m_spells.priest.pAbolishDisease))
			{
				if (DoCastSpell(pFriend, m_spells.priest.pAbolishDisease) == SPELL_CAST_OK)
					return;
			}
		}
	}

    if (m_role == ROLE_HEALER)
    {
        // Check group healing
        if (GetAlliesNeedingHealCount(20.0f, 70.0f) >= 3 &&
            m_spells.priest.pPrayerofHealing &&
            CanTryToCastSpell(me, m_spells.priest.pPrayerofHealing)) //檢查周圍20~70碼盟友>3，則用治療導言
        {
            if (DoCastSpell(me, m_spells.priest.pPrayerofHealing) == SPELL_CAST_OK)
                return;
        }

        // Shield allies being attacked.
        if (m_spells.priest.pPowerWordShield)
        {
            if (Player* pTarget = SelectShieldTarget())
            {
                if (CanTryToCastSpell(pTarget, m_spells.priest.pPowerWordShield))
                {
                    if (DoCastSpell(pTarget, m_spells.priest.pPowerWordShield) == SPELL_CAST_OK)
                        return;
                }
            }
        }

		if (FindAndHealInjuredAlly(85.0f, 45.0f))
			return;
    }
	else
	{
		if (Unit* pVictim = me->GetVictim())
		{
			if (m_spells.priest.pShadowform &&
				me->GetShapeshiftForm() != FORM_SHADOW &&
				CanTryToCastSpell(me, m_spells.priest.pShadowform))
			{
				if (DoCastSpell(me, m_spells.priest.pShadowform) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.priest.pSilence &&
				pVictim->IsNonMeleeSpellCasted() &&
				CanTryToCastSpell(pVictim, m_spells.priest.pSilence))
			{
				if (DoCastSpell(pVictim, m_spells.priest.pSilence) == SPELL_CAST_OK)
					return;
			}


			if (m_spells.priest.pHolyNova &&
				me->GetShapeshiftForm() == FORM_NONE &&
				me->GetEnemyCountInRadiusAround(me, 10.0f) > 2 &&
				CanTryToCastSpell(me, m_spells.priest.pHolyNova))
			{
				if (DoCastSpell(me, m_spells.priest.pHolyNova) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.priest.pManaBurn &&
				me->GetPowerPercent(POWER_MANA) < 50.0f &&
				pVictim->GetPowerType() == POWER_MANA &&
				pVictim->GetPowerPercent(POWER_MANA) > 10.0f &&
				CanTryToCastSpell(pVictim, m_spells.priest.pManaBurn))
			{
				if (DoCastSpell(pVictim, m_spells.priest.pManaBurn) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.priest.pVampiricEmbrace &&
				CanTryToCastSpell(pVictim, m_spells.priest.pVampiricEmbrace)) //吸血鬼的擁抱
			{
				if (DoCastSpell(pVictim, m_spells.priest.pVampiricEmbrace) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.priest.pShadowWordPain &&
				CanTryToCastSpell(pVictim, m_spells.priest.pShadowWordPain)) //暗言術：痛
			{
				if (DoCastSpell(pVictim, m_spells.priest.pShadowWordPain) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.priest.pDevouringPlague &&
				CanTryToCastSpell(pVictim, m_spells.priest.pDevouringPlague)) //嗜靈瘟疫
			{
				if (DoCastSpell(pVictim, m_spells.priest.pDevouringPlague) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.priest.pMindBlast &&
				CanTryToCastSpell(pVictim, m_spells.priest.pMindBlast))
			{
				if (DoCastSpell(pVictim, m_spells.priest.pMindBlast) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.priest.pMindFlay &&
				CanTryToCastSpell(pVictim, m_spells.priest.pMindFlay))
			{
				if (DoCastSpell(pVictim, m_spells.priest.pMindFlay) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.priest.pSmite &&
				CanTryToCastSpell(pVictim, m_spells.priest.pSmite))
			{
				if (DoCastSpell(pVictim, m_spells.priest.pSmite) == SPELL_CAST_OK)
					return;
			}

			if (me->HasSpell(PB_SPELL_SHOOT_WAND) &&
				!me->IsMoving() &&
				!me->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL))
				me->CastSpell(pVictim, PB_SPELL_SHOOT_WAND, false);
		}
    }
}

void PartyBotAI::UpdateOutOfCombatAI_Warlock()
{
	if (m_spells.warlock.pUnendingBreath && !me->GetGroup()->isRaidGroup()) //水息術
	{
		if (Player* pTarget = SelectBuffTarget(m_spells.warlock.pUnendingBreath))
		{
			if (pTarget->IsInWater() || pTarget->IsSwimming())
			{
				if (CanTryToCastSpell(pTarget, m_spells.warlock.pUnendingBreath))
				{
					if (DoCastSpell(pTarget, m_spells.warlock.pUnendingBreath) == SPELL_CAST_OK)
					{
						m_isBuffing = true;
						return;
					}
				}
			}
		}
	}

	if (m_spells.warlock.pDetectInvisibility && !me->GetGroup()->isRaidGroup()) //偵測次級隱形
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.warlock.pDetectInvisibility))
        {
            if (CanTryToCastSpell(pTarget, m_spells.warlock.pDetectInvisibility))
            {
                if (DoCastSpell(pTarget, m_spells.warlock.pDetectInvisibility) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }

	if (m_spells.warlock.pDemonArmor)
	{
		if (CanTryToCastSpell(me, m_spells.warlock.pDemonArmor))
		{
			if (DoCastSpell(me, m_spells.warlock.pDemonArmor) == SPELL_CAST_OK)
			{
				m_isBuffing = true;
				return;
			}
		}

	}
	else if (m_spells.warlock.pDemonSkin)
	{
		if (CanTryToCastSpell(me, m_spells.warlock.pDemonSkin))
		{
			if (DoCastSpell(me, m_spells.warlock.pDemonSkin) == SPELL_CAST_OK)
			{
				m_isBuffing = true;
				return;
			}
        }
    }

	//如果buffing且沒有水息術或偵測次級隱形不再GCD或水息術不在GCD時，則將m_ifBuffing設為false
    if (m_isBuffing &&
       ((!m_spells.warlock.pUnendingBreath) ||
        ((!me->HasGCD(m_spells.warlock.pDetectInvisibility)) ||
		!me->HasGCD(m_spells.warlock.pUnendingBreath))))
    {
        m_isBuffing = false;
    }

	if (!me->HasAura(PB_SPELL_TOUCH_OF_SHADOW))
	{
		if (m_spells.warlock.pDemonicSacrifice)
		{
			if (Pet* pPet = me->GetPet())
			{
				if (pPet->IsAlive() &&
					CanTryToCastSpell(pPet, m_spells.warlock.pDemonicSacrifice))
				{
					if (DoCastSpell(pPet, m_spells.warlock.pDemonicSacrifice) == SPELL_CAST_OK)
						return;
				}
			}
		}

		SummonPetIfNeeded();
		return;
    }
	/*
    if (Unit* pVictim = me->GetVictim())
        UpdateInCombatAI_Warlock();
	*/
    /*
    if (Unit* pVictim = me->GetVictim())
    {
        if (Pet* pPet = me->GetPet())
        {
			if (!pPet->GetVictim())
            {
                pPet->GetCharmInfo()->SetIsCommandAttack(true);
                //pPet->AI()->AttackStart(pVictim); //VM原版，命令寵物開始攻擊，僅普通攻擊
				if (me->GetLevel() >= 1 && me->GetLevel() < 8)
				{
					pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK1, false); //測試功能，術士小鬼放火焰箭
				}
				else if (me->GetLevel() >= 8 && me->GetLevel() < 18)
				{
					pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK2, false); //測試功能，術士小鬼放火焰箭
				}
				else if (me->GetLevel() >= 18 && me->GetLevel() < 28)
				{
					pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK3, false); //測試功能，術士小鬼放火焰箭
				}
				else if (me->GetLevel() >= 28 && me->GetLevel() < 38)
				{
					pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK4, false); //測試功能，術士小鬼放火焰箭
				}
				else if (me->GetLevel() >= 38 && me->GetLevel() < 48)
				{
					pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK5, false); //測試功能，術士小鬼放火焰箭
				}
				else if (me->GetLevel() >= 48 && me->GetLevel() < 58)
				{
					pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK6, false); //測試功能，術士小鬼放火焰箭
				}
				else if (me->GetLevel() >= 58 && me->GetLevel() <= 60)
				{
					pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK7, false); //測試功能，術士小鬼放火焰箭
				}
            }
        }

        UpdateInCombatAI_Warlock();
    }
	else //反之，非戰鬥中，進行判斷寵物召喚或復活
	{
		SummonPetIfNeeded(); //沒有敵人則召喚寵物
		if (Pet* pPet = me->GetPet())
		{
			Player* pLeader = GetPartyLeader();
			//if(!pLeader->HasAura(PB_SPELL_BLOODPACT_RANK1))
			if (me->GetLevel() >=4 && me->GetLevel() < 14 && !pLeader->HasAura(PB_SPELL_BLOODPACT_RANK1))
			{
				pPet->CastSpell(me, PB_SPELL_BLOODPACT_RANK1, true);
				m_isBuffing = true;
				return;
			}
			else if (me->GetLevel() >= 14 && me->GetLevel() < 26 && !pLeader->HasAura(PB_SPELL_BLOODPACT_RANK2))
			{
				pPet->CastSpell(me, PB_SPELL_BLOODPACT_RANK2, true);
				m_isBuffing = true;
				return;
			}
			else if (me->GetLevel() >= 26 && me->GetLevel() < 38 && !pLeader->HasAura(PB_SPELL_BLOODPACT_RANK3))
			{
				pPet->CastSpell(me, PB_SPELL_BLOODPACT_RANK3, true);
				m_isBuffing = true;
				return;
			}
			else if (me->GetLevel() >= 38 && me->GetLevel() < 50 && !pLeader->HasAura(PB_SPELL_BLOODPACT_RANK4))
			{
				pPet->CastSpell(me, PB_SPELL_BLOODPACT_RANK4, true);
				m_isBuffing = true;
				return;
			}
			else if (me->GetLevel() >= 50 && me->GetLevel() <= 60 && !pLeader->HasAura(PB_SPELL_BLOODPACT_RANK5))
			{
				pPet->CastSpell(me, PB_SPELL_BLOODPACT_RANK5, true);
				m_isBuffing = true;
				return;
			}
		}
		return;
	}
	*/
}

void PartyBotAI::UpdateInCombatAI_Warlock()
{
    if (Unit* pVictim = me->GetVictim())
    {
		/*
        if (Pet* pPet = me->GetPet())
		{
				//pPet->GetCharmInfo()->SetIsCommandAttack(true);
				//pPet->AI()->AttackStart(pVictim); //VM原版，命令寵物開始攻擊，僅普通攻擊
			if (me->GetLevel() >= 1 && me->GetLevel() < 8)
			{
				pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK1, false); //測試功能，術士小鬼放火焰箭
			}
			else if (me->GetLevel() >= 8 && me->GetLevel() < 18)
			{
				pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK2, false); //測試功能，術士小鬼放火焰箭
			}
			else if (me->GetLevel() >= 18 && me->GetLevel() < 28)
			{
				pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK3, false); //測試功能，術士小鬼放火焰箭
			}
			else if (me->GetLevel() >= 28 && me->GetLevel() < 38)
			{
				pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK4, false); //測試功能，術士小鬼放火焰箭
			}
			else if (me->GetLevel() >= 38 && me->GetLevel() < 48)
			{
				pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK5, false); //測試功能，術士小鬼放火焰箭
			}
			else if (me->GetLevel() >= 48 && me->GetLevel() < 58)
			{
				pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK6, false); //測試功能，術士小鬼放火焰箭
			}
			else if (me->GetLevel() >= 58 && me->GetLevel() <= 60)
			{
				pPet->CastSpell(pVictim, PB_SPELL_FIREBOLT_RANK7, false); //測試功能，術士小鬼放火焰箭
			}
		}
		*/

		if (m_spells.warlock.pDeathCoil &&
            me->GetHealthPercent() < 65.0f &&
            pVictim->GetVictim() == me &&
            pVictim->CanReachWithMeleeAutoAttack(me) &&
            CanTryToCastSpell(pVictim, m_spells.warlock.pDeathCoil)) //死亡纏繞
        {
            if (DoCastSpell(pVictim, m_spells.warlock.pDeathCoil) == SPELL_CAST_OK)
                return;
        }

		if (Pet* pPet = me->GetPet())
		{
			if (!pPet->GetVictim() && !me->GetMap()->IsDungeon())
			{
				pPet->GetCharmInfo()->SetIsCommandAttack(true);
				pPet->AI()->AttackStart(pVictim);
			}
		}

		if (m_spells.warlock.pHowlofTerror &&
			me->GetHealthPercent() < 30.0f &&
			GetAttackersInRangeCount(10.0f) > 1 &&
			CanTryToCastSpell(me, m_spells.warlock.pHowlofTerror)) //恐懼嚎叫
		{
			if (DoCastSpell(me, m_spells.warlock.pHowlofTerror) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warlock.pShadowburn &&
			(pVictim->GetHealthPercent() < 10.0f) &&
			CanTryToCastSpell(pVictim, m_spells.warlock.pShadowburn)) //暗影灼燒
		{
			if (DoCastSpell(pVictim, m_spells.warlock.pShadowburn) == SPELL_CAST_OK)
                return;
        }

		if (m_spells.warlock.pBanish && m_spellTimer1 <= 0)
		{
			if (Unit* pTarget = SelectSpellTargetDifferentFrom(m_spells.warlock.pBanish, pVictim, 15.0f))
			{
				if (DoCastSpell(pTarget, m_spells.warlock.pBanish) == SPELL_CAST_OK)
				{
					m_spellTimer1 = 15 * IN_MILLISECONDS;
					return;
				}
            }
        }

        if (m_spells.warlock.pRainOfFire &&
			m_aoeSpellTimer <= 0 &&
            (me->GetEnemyCountInRadiusAround(pVictim, 10.0f) > 3) &&
            pVictim->GetHealthPercent() < 75.0f &&
            CanTryToCastSpell(pVictim, m_spells.warlock.pRainOfFire)) //火焰之雨
        {
            if (DoCastSpell(pVictim, m_spells.warlock.pRainOfFire) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.warlock.pDemonicSacrifice) //惡魔犧牲
        {
            if (Pet* pPet = me->GetPet()) //如果術士惡魔活著則對其使用惡魔犧牲
            {
                if (pPet->IsAlive() &&
                    CanTryToCastSpell(pPet, m_spells.warlock.pDemonicSacrifice))
                {
                    if (DoCastSpell(pPet, m_spells.warlock.pDemonicSacrifice) == SPELL_CAST_OK)
                        return;
                }
            }
        }

		// Raid Curse
		if (me->GetGroup()->isRaidGroup())
		{
			if (m_spells.warlock.pRaidCurse &&
				!pVictim->HasAura(m_spells.warlock.pRaidCurse->Id) &&
				CanTryToCastSpell(pVictim, m_spells.warlock.pRaidCurse))
			{
				if (DoCastSpell(pVictim, m_spells.warlock.pRaidCurse) == SPELL_CAST_OK)
					return;
			}
		}

		if (m_spells.warlock.pImmolate &&
			CanTryToCastSpell(pVictim, m_spells.warlock.pImmolate))
		{
			if (DoCastSpell(pVictim, m_spells.warlock.pImmolate) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warlock.pCorruption &&
			CanTryToCastSpell(pVictim, m_spells.warlock.pCorruption))
		{
			if (DoCastSpell(pVictim, m_spells.warlock.pCorruption) == SPELL_CAST_OK)
				return;
		}

        if (m_spells.warlock.pSiphonLife &&
           (me->GetHealthPercent() < 80.0f) &&
            CanTryToCastSpell(pVictim, m_spells.warlock.pSiphonLife)) //靈魂虹吸
        {
            if (DoCastSpell(pVictim, m_spells.warlock.pSiphonLife) == SPELL_CAST_OK)
                return;
        }

		if (!me->GetGroup()->isRaidGroup())
		{
			if (m_spells.warlock.pCurseofTongues &&
				pVictim->IsCaster() &&
				CanTryToCastSpell(pVictim, m_spells.warlock.pCurseofTongues))
			{
				if (DoCastSpell(pVictim, m_spells.warlock.pCurseofTongues) == SPELL_CAST_OK)
					return;
			}
			else if (m_spells.warlock.pCurseofAgony &&
				CanTryToCastSpell(pVictim, m_spells.warlock.pCurseofAgony))
			{
				if (DoCastSpell(pVictim, m_spells.warlock.pCurseofAgony) == SPELL_CAST_OK)
					return;
			}
		}

        if (m_spells.warlock.pDrainLife &&
           (me->GetHealthPercent() < 50.0f) &&
            CanTryToCastSpell(pVictim, m_spells.warlock.pDrainLife)) //吸取生命，VM原版當術士生命<30使用，，我比照Ace方式改為<50
        {
            if (DoCastSpell(pVictim, m_spells.warlock.pDrainLife) == SPELL_CAST_OK)
                return;
        }

		if (m_spells.warlock.pConflagrate &&
			CanTryToCastSpell(pVictim, m_spells.warlock.pConflagrate))
		{
			if (DoCastSpell(pVictim, m_spells.warlock.pConflagrate) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warlock.pFear &&
			pVictim->GetVictim() == me &&
			pVictim->CanReachWithMeleeAutoAttack(me) &&
			(!pVictim->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE) || !pVictim->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT)) &&
			CanTryToCastSpell(pVictim, m_spells.warlock.pFear)) //恐懼術
		{
			if (DoCastSpell(pVictim, m_spells.warlock.pFear) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warlock.pSearingPain &&
			(pVictim->GetHealthPercent() < 20.0f) &&
			CanTryToCastSpell(pVictim, m_spells.warlock.pSearingPain))
		{
			if (DoCastSpell(pVictim, m_spells.warlock.pSearingPain) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.warlock.pShadowBolt &&
            CanTryToCastSpell(pVictim, m_spells.warlock.pShadowBolt)) //暗影箭
        {
            if (DoCastSpell(pVictim, m_spells.warlock.pShadowBolt) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.warlock.pLifeTap &&
           (me->GetPowerPercent(POWER_MANA) < 10.0f) &&
           //(me->GetHealthPercent() > 70.0f) &&
            CanTryToCastSpell(me, m_spells.warlock.pLifeTap)) //生命分流
        {
            if (DoCastSpell(me, m_spells.warlock.pLifeTap) == SPELL_CAST_OK)
                return;
        }

		if (m_spells.warlock.pDarkPact &&
			(me->GetPowerPercent(POWER_MANA) < 10.0f) &&
			CanTryToCastSpell(me, m_spells.warlock.pDarkPact))
		{
			if (DoCastSpell(me, m_spells.warlock.pDarkPact) == SPELL_CAST_OK)
				return;
		}

        if (me->HasSpell(PB_SPELL_SHOOT_WAND) &&
           !me->IsMoving() &&
           !me->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL))
            me->CastSpell(pVictim, PB_SPELL_SHOOT_WAND, false);
    }
}

void PartyBotAI::UpdateOutOfCombatAI_Warrior()
{
	if (m_spells.warrior.pBattleStance &&
		CanTryToCastSpell(me, m_spells.warrior.pBattleStance))
	{
		if (DoCastSpell(me, m_spells.warrior.pBattleStance) == SPELL_CAST_OK)
			return;
	}

	if (m_spells.warrior.pBattleShout &&
		!me->HasAura(m_spells.warrior.pBattleShout->Id))
	{
		if (CanTryToCastSpell(me, m_spells.warrior.pBattleShout))
			DoCastSpell(me, m_spells.warrior.pBattleShout);
		else if (m_spells.warrior.pBloodrage &&
			(me->GetPower(POWER_RAGE) < 10) &&
			CanTryToCastSpell(me, m_spells.warrior.pBloodrage))
		{
			DoCastSpell(me, m_spells.warrior.pBloodrage);
		}
	}

	/*
	if (Unit* pVictim = me->GetVictim())
	{
		if (m_spells.warrior.pCharge &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pCharge))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pCharge) == SPELL_CAST_OK)
				return;
		}
	}
	*/
}

void PartyBotAI::UpdateInCombatAI_Warrior()
{
	if (Unit* pVictim = me->GetVictim())
	{
        // CHARGE
        if (m_spells.warrior.pCharge &&
            CanTryToCastSpell(pVictim, m_spells.warrior.pCharge))
        {
            if (DoCastSpell(pVictim, m_spells.warrior.pCharge) == SPELL_CAST_OK)
                return;
        }

        // STANCE SELECTION
		if (pVictim->CanReachWithMeleeAutoAttack(me))
		{
			if (m_role == ROLE_TANK || me->GetHealthPercent() < 25.0f)
			{
				if (m_spells.warrior.pDefensiveStance &&
					CanTryToCastSpell(me, m_spells.warrior.pDefensiveStance))
				{
					DoCastSpell(me, m_spells.warrior.pDefensiveStance);
				}
			}
			else if (me->GetHealthPercent() > 60.0f)
			{
				if (m_spells.warrior.pBloodthirst &&
					m_spells.warrior.pBerserkerStance &&
					me->GetShapeshiftForm() != FORM_BERSERKERSTANCE &&
					CanTryToCastSpell(me, m_spells.warrior.pBerserkerStance))
				{
					DoCastSpell(me, m_spells.warrior.pBerserkerStance);
				}
				else if (m_spells.warrior.pMortalStrike &&
					m_spells.warrior.pBattleStance &&
					me->GetShapeshiftForm() != FORM_BATTLESTANCE &&
					CanTryToCastSpell(me, m_spells.warrior.pBattleStance))
				{
					DoCastSpell(me, m_spells.warrior.pBattleStance);
				}
			}
		}

		// USE DEFENSIVE SPELLS
		if (me->GetShapeshiftForm() == FORM_DEFENSIVESTANCE && IsWearingShield())
		{
			if (!me->GetAttackers().empty())
			{
				if (m_spells.warrior.pShieldBlock &&
					(me->GetHealthPercent() < 70.0f) &&
					CanTryToCastSpell(me, m_spells.warrior.pShieldBlock))
				{
					if (DoCastSpell(me, m_spells.warrior.pShieldBlock) == SPELL_CAST_OK)
						return;
				}

				if (m_spells.warrior.pShieldWall &&
					(me->GetHealthPercent() < 30.0f) &&
					CanTryToCastSpell(me, m_spells.warrior.pShieldWall))
				{
					if (DoCastSpell(me, m_spells.warrior.pShieldWall) == SPELL_CAST_OK)
						return;
				}
			}
		}

		if (m_spells.warrior.pLastStand &&
			me->GetHealthPercent() < 20.0f &&
			CanTryToCastSpell(me, m_spells.warrior.pLastStand))
		{
			if (DoCastSpell(me, m_spells.warrior.pLastStand) == SPELL_CAST_OK)
				return;
		}

		if (m_role != ROLE_TANK &&
			m_spells.warrior.pIntimidatingShout &&
			(me->GetHealthPercent() < 20.0f) &&
			(GetAttackersInRangeCount(10.0f) > 2) &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pIntimidatingShout))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pIntimidatingShout) == SPELL_CAST_OK)
				return;
		}

		// BATTLE SHOUT IF NEEDED
		if (m_spells.warrior.pBattleShout &&
			CanTryToCastSpell(me, m_spells.warrior.pBattleShout))
		{
			if (DoCastSpell(me, m_spells.warrior.pBattleShout) == SPELL_CAST_OK)
				return;
		}

		// USE PROC OR CONDITIONAL SPELLS
		if (m_spells.warrior.pRevenge &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pRevenge))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pRevenge) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warrior.pOverpower &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pOverpower)) //壓制
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pOverpower) == SPELL_CAST_OK)
				return;
		}

        if (m_spells.warrior.pBerserkerRage &&
            CanTryToCastSpell(me, m_spells.warrior.pBerserkerRage)) //狂暴之怒
        {
            if (DoCastSpell(me, m_spells.warrior.pBerserkerRage) == SPELL_CAST_OK)
                return;
        }

		if (m_spells.warrior.pExecute &&
			(pVictim->GetHealthPercent() < 20.0f) &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pExecute))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pExecute) == SPELL_CAST_OK)
				return;
		}

		// DEBUFF ENEMY
		if (m_role == ROLE_TANK &&
			m_spells.warrior.pDemoralizingShout &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pDemoralizingShout)) //挫志怒吼
        {
			if (DoCastSpell(pVictim, m_spells.warrior.pDemoralizingShout) == SPELL_CAST_OK)
				return;
        }

		// Go on only if 15 rage is available so the most relevant skills can be used 怒氣低於15就不再往下執行
		if (me->GetPowerPercent(POWER_RAGE) < 15.0f)
			return;

        // For tanks, prioritize first Sunder Armor application
        if (m_role == ROLE_TANK &&
            m_spells.warrior.pSunderArmor &&
            CanTryToCastStackSpell(pVictim, m_spells.warrior.pSunderArmor, 1))
        {
            if (DoCastSpell(pVictim, m_spells.warrior.pSunderArmor) == SPELL_CAST_OK)
                return;
        }

		// Use AOE spells
		if (me->GetEnemyCountInRadiusAround(me, 10.0f) > 2)
		{
			if (m_role == ROLE_TANK)
			{
				if (m_spells.warrior.pBattleShout &&
					CanTryToCastStackSpell(me, m_spells.warrior.pBattleShout, 2))
				{
					if (DoCastSpell(me, m_spells.warrior.pBattleShout) == SPELL_CAST_OK)
						return;
				}
			}
			else
			{
				if (m_spells.warrior.pWhirlwind &&
					CanTryToCastSpell(pVictim, m_spells.warrior.pWhirlwind))
				{
					if (DoCastSpell(pVictim, m_spells.warrior.pWhirlwind) == SPELL_CAST_OK)
						return;
				}

				if (m_spells.warrior.pThunderClap &&
					CanTryToCastSpell(pVictim, m_spells.warrior.pThunderClap))
				{
					if (DoCastSpell(pVictim, m_spells.warrior.pThunderClap) == SPELL_CAST_OK)
						return;
				}
			}
		}

		// Use single target spells
		if (m_spells.warrior.pRend &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pRend))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pRend) == SPELL_CAST_OK)
				return;
		}

		// Try to stop if target running away
		if (m_spells.warrior.pConcussionBlow &&
			(pVictim->IsNonMeleeSpellCasted() || pVictim->IsMoving() || (me->GetHealthPercent() < 50.0f)) &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pConcussionBlow))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pConcussionBlow) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warrior.pHamstring &&
			pVictim->IsMoving() &&
			!pVictim->HasUnitState(UNIT_STAT_ROOT) &&
			!pVictim->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED) &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pHamstring))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pHamstring) == SPELL_CAST_OK)
				return;
		}


		// Now wait for more rage for main skills
		if (me->GetPowerPercent(POWER_RAGE) < 30.0f)
			return;

		if (m_spells.warrior.pShieldSlam &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pShieldSlam)) //盾牌猛擊
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pShieldSlam) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warrior.pSweepingStrikes &&
			CanTryToCastSpell(me, m_spells.warrior.pSweepingStrikes) &&
			(me->GetEnemyCountInRadiusAround(pVictim, 10.0f) > 1))
		{
			if (DoCastSpell(me, m_spells.warrior.pSweepingStrikes) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warrior.pMortalStrike &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pMortalStrike)) //致死打擊
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pMortalStrike) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warrior.pBloodthirst &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pBloodthirst)) //血性狂暴
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pBloodthirst) == SPELL_CAST_OK)
				return;
		}

        // Second Sunder Armor Application
		if (m_role == ROLE_TANK &&
			m_spells.warrior.pSunderArmor &&
			CanTryToCastStackSpell(pVictim, m_spells.warrior.pSunderArmor, 2)) //破甲，堆疊上限為2
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pSunderArmor) == SPELL_CAST_OK)
				return;
		}

        if (m_spells.warrior.pDisarm &&
			IsMeleeWeaponClass(pVictim->GetClass()) &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pDisarm)) //繳械
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pDisarm) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warrior.pRetaliation &&
			(GetAttackersInRangeCount(10.0f) > 2) &&
			CanTryToCastSpell(me, m_spells.warrior.pRetaliation))
		{
			if (DoCastSpell(me, m_spells.warrior.pRetaliation) == SPELL_CAST_OK)
				return;
		}

        if (m_role != ROLE_TANK &&
			(me->GetHealthPercent() > 60.0f) && (pVictim->GetHealthPercent() > 40.0f) &&
			!me->HasUnitState(UNIT_STAT_ROOT) &&
			!me->IsImmuneToMechanic(MECHANIC_FEAR))
		{
			if (m_spells.warrior.pDeathWish &&
				CanTryToCastSpell(me, m_spells.warrior.pDeathWish))
			{
				if (DoCastSpell(me, m_spells.warrior.pDeathWish) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.warrior.pRecklessness &&
				CanTryToCastSpell(me, m_spells.warrior.pRecklessness))
			{
				if (DoCastSpell(me, m_spells.warrior.pRecklessness) == SPELL_CAST_OK)
					return;
			}
		}

		if (m_spells.warrior.pIntercept &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pIntercept)) //攔截
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pIntercept) == SPELL_CAST_OK)
				return;
		}
/*
		if (me->GetShapeshiftForm() == FORM_BERSERKERSTANCE &&
			m_spells.warrior.pSlam &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pSlam)) //猛擊
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pSlam) == SPELL_CAST_OK)
				return;
		}
*/
        // LASTLY USE FILLER SPELLS
		if (me->GetEnemyCountInRadiusAround(pVictim, 8.0f) > 1 &&
			m_spells.warrior.pCleave &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pCleave))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pCleave) == SPELL_CAST_OK)
				return;
		}

		// For tanks, apply Sunder Armor up to 5 stacks 如為坦克身分，破甲堆5
		if (m_role == ROLE_TANK &&
			m_spells.warrior.pSunderArmor &&
			CanTryToCastStackSpell(pVictim, m_spells.warrior.pSunderArmor, 5))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pSunderArmor) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.warrior.pHeroicStrike &&
			CanTryToCastSpell(pVictim, m_spells.warrior.pHeroicStrike))
		{
			if (DoCastSpell(pVictim, m_spells.warrior.pHeroicStrike) == SPELL_CAST_OK)
				return;
		}

		/*if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE
			&& !me->CanReachWithMeleeAutoAttack(pVictim))
		{
			me->GetMotionMaster()->MoveChase(pVictim);
		}*/

	}
	else // no victim
	{
		if (m_spells.warrior.pBattleShout &&
			CanTryToCastSpell(me, m_spells.warrior.pBattleShout))
		{
			if (DoCastSpell(me, m_spells.warrior.pBattleShout) == SPELL_CAST_OK)
				return;
		}
	}
}

bool PartyBotAI::ShouldEnterStealth() const
{
    if (me->IsMounted())
        return false;

    if (me->GetVictim() || me->InBattleGround() || me->IsFFAPvP())
        return true;

    if (me->GetHealthPercent() < 10.0f)
        return true;

    if (Player* pLeader = GetPartyLeader())
    {
        if (pLeader->IsDead() || pLeader->IsFeigningDeathSuccessfully() ||
            pLeader->HasAuraType(SPELL_AURA_MOD_STEALTH) ||
            pLeader->HasAuraType(SPELL_AURA_MOD_INVISIBILITY))
            return true;
    }

    return false;
}

bool PartyBotAI::EnterStealthIfNeeded(SpellEntry const* pStealthSpell)
{
    if (pStealthSpell)
    {
        bool const shouldStealth = ShouldEnterStealth();

        if (me->HasAura(pStealthSpell->Id))
        {
            if (!shouldStealth)
                me->RemoveAurasDueToSpellByCancel(pStealthSpell->Id);
        }
        else
        {
            if (shouldStealth &&
                CanTryToCastSpell(me, pStealthSpell) &&
                DoCastSpell(me, pStealthSpell) == SPELL_CAST_OK)
                return true;
        }
    }

    return false;
}

void PartyBotAI::UpdateOutOfCombatAI_Rogue()
{
    if (m_spells.rogue.pMainHandPoison &&
        CanTryToCastSpell(me, m_spells.rogue.pMainHandPoison))
    {
        if (CastWeaponBuff(m_spells.rogue.pMainHandPoison, EQUIPMENT_SLOT_MAINHAND) == SPELL_CAST_OK)
            return;
    }

    if (m_spells.rogue.pOffHandPoison &&
        CanTryToCastSpell(me, m_spells.rogue.pOffHandPoison))
    {
        if (CastWeaponBuff(m_spells.rogue.pOffHandPoison, EQUIPMENT_SLOT_OFFHAND) == SPELL_CAST_OK)
            return;
    }

	if (m_spells.rogue.pStealth &&
		CanTryToCastSpell(me, m_spells.rogue.pStealth))
	{
		if (Player* pLeader = GetPartyLeader())
		{
			if (me->IsWithinDistInMap(pLeader, 10.0) &&
				DoCastSpell(me, m_spells.rogue.pStealth) == SPELL_CAST_OK)
				return;
		}
	}

    /*
    if (me->GetVictim())
        UpdateInCombatAI_Rogue();
     */
}

void PartyBotAI::UpdateInCombatAI_Rogue()
{
    if (Unit* pVictim = me->GetVictim())
    {
        if (me->HasAuraType(SPELL_AURA_MOD_STEALTH)) //如果處於隱身狀態
        {
            if (m_spells.rogue.pPremeditation &&
                CanTryToCastSpell(pVictim, m_spells.rogue.pPremeditation)) //嘗試使用預謀技能
            {
                DoCastSpell(pVictim, m_spells.rogue.pPremeditation);
            }

            if (pVictim->IsCaster()) //若對方是施法者
            {
                if (m_spells.rogue.pGarrote &&
                    CanTryToCastSpell(pVictim, m_spells.rogue.pGarrote)) //使用绞喉
                {
                    if (DoCastSpell(pVictim, m_spells.rogue.pGarrote) == SPELL_CAST_OK)
                        return;
                }
            }
            else
            {
                if (m_spells.rogue.pAmbush &&
                    CanTryToCastSpell(pVictim, m_spells.rogue.pAmbush)) //使用伏擊
                {
                    if (DoCastSpell(pVictim, m_spells.rogue.pAmbush) == SPELL_CAST_OK)
                        return;
                }

                if (m_spells.rogue.pCheapShot &&
                    CanTryToCastSpell(pVictim, m_spells.rogue.pCheapShot)) //使用偷襲
                {
                    if (DoCastSpell(pVictim, m_spells.rogue.pCheapShot) == SPELL_CAST_OK)
                        return;
                }
            }
        }
        else
        {
            if (m_spells.rogue.pVanish &&
                (me->GetHealthPercent() < 10.0f)) //如果有消失技能自己生命值<10%
            {
                if (m_spells.rogue.pPreparation &&
                    !me->IsSpellReady(m_spells.rogue.pVanish->Id) &&
                    CanTryToCastSpell(me, m_spells.rogue.pPreparation))
                {
                    if (DoCastSpell(me, m_spells.rogue.pPreparation) == SPELL_CAST_OK)
                        return;
                }

                if (CanTryToCastSpell(me, m_spells.rogue.pVanish))
                {
                    if (DoCastSpell(me, m_spells.rogue.pVanish) == SPELL_CAST_OK)
                    {
                        RunAwayFromTarget(pVictim);
                        return;
                    }
                }
            }
        }

        if (me->GetComboPoints() > 4)
        {
            std::vector<SpellEntry const*> vSpells;

            // Give priority to Slice and Dice over other finishing moves.
            if (m_spells.rogue.pSliceAndDice &&
               !me->HasAura(m_spells.rogue.pSliceAndDice->Id) &&
                pVictim->GetHealthPercent() > 10.0f)
                vSpells.push_back(m_spells.rogue.pSliceAndDice);
            else
            {
                if (m_spells.rogue.pEviscerate)
                    vSpells.push_back(m_spells.rogue.pEviscerate);
                if (m_spells.rogue.pKidneyShot && !pVictim->IsImmuneToMechanic(MECHANIC_STUN))
                    vSpells.push_back(m_spells.rogue.pKidneyShot);
                if (m_spells.rogue.pExposeArmor)
                    vSpells.push_back(m_spells.rogue.pExposeArmor);
                if (m_spells.rogue.pRupture)
                    vSpells.push_back(m_spells.rogue.pRupture);
            }
            
            if (!vSpells.empty())
            {
                SpellEntry const* pComboSpell = SelectRandomContainerElement(vSpells);
                if (CanTryToCastSpell(pVictim, pComboSpell))
                {
                    if (DoCastSpell(pVictim, pComboSpell) == SPELL_CAST_OK)
                        return;
                }
            }
        }

        if (m_spells.rogue.pBlind) //致盲
        {
            if (Unit* pTarget = SelectAttackerDifferentFrom(pVictim))
            {
                if (CanTryToCastSpell(pTarget, m_spells.rogue.pBlind) &&
                    CanUseCrowdControl(m_spells.rogue.pBlind, pTarget))
                {
                    if (DoCastSpell(pTarget, m_spells.rogue.pBlind) == SPELL_CAST_OK)
                    {
                        me->AttackStop();
                        AttackStart(pVictim);
                        return;
                    }
                }
            }
        }

        if (m_spells.rogue.pAdrenalineRush &&
           !me->GetPower(POWER_ENERGY) &&
            CanTryToCastSpell(me, m_spells.rogue.pAdrenalineRush)) //衝動
        {
            if (DoCastSpell(me, m_spells.rogue.pAdrenalineRush) == SPELL_CAST_OK)
                return;
        }

        if (pVictim->IsNonMeleeSpellCasted())
        {
			if (m_spells.rogue.pKick &&
				CanTryToCastSpell(pVictim, m_spells.rogue.pKick)) //腳踢
			{
				if (DoCastSpell(pVictim, m_spells.rogue.pKick) == SPELL_CAST_OK)
					return;
			}
			
			if (m_spells.rogue.pGouge &&
                CanTryToCastSpell(pVictim, m_spells.rogue.pGouge)) //鑿擊
            {
                if (DoCastSpell(pVictim, m_spells.rogue.pGouge) == SPELL_CAST_OK)
                    return;
            }
        }

        if (!me->HasAuraType(SPELL_AURA_MOD_STEALTH))
        {
            if (m_spells.rogue.pEvasion &&
               (me->GetHealthPercent() < 80.0f) &&
               ((GetAttackersInRangeCount(10.0f) > 2) || !IsRangedDamageClass(pVictim->GetClass())) &&
                CanTryToCastSpell(me, m_spells.rogue.pEvasion))
            {
                if (DoCastSpell(me, m_spells.rogue.pEvasion) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.rogue.pColdBlood &&
                CanTryToCastSpell(me, m_spells.rogue.pColdBlood))
            {
                DoCastSpell(me, m_spells.rogue.pColdBlood);
            }

            if (m_spells.rogue.pBladeFlurry &&
                CanTryToCastSpell(me, m_spells.rogue.pBladeFlurry))
            {
                if (DoCastSpell(me, m_spells.rogue.pBladeFlurry) == SPELL_CAST_OK)
                    return;
            }
        }

        if (m_spells.rogue.pRiposte &&
            CanTryToCastSpell(pVictim, m_spells.rogue.pRiposte)) //還擊
        {
            if (DoCastSpell(pVictim, m_spells.rogue.pRiposte) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.rogue.pBackstab &&
            CanTryToCastSpell(pVictim, m_spells.rogue.pBackstab)) //背刺
        {
            if (DoCastSpell(pVictim, m_spells.rogue.pBackstab) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.rogue.pGhostlyStrike &&
            CanTryToCastSpell(pVictim, m_spells.rogue.pGhostlyStrike))
        {
            if (DoCastSpell(pVictim, m_spells.rogue.pGhostlyStrike) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.rogue.pHemorrhage &&
            CanTryToCastSpell(pVictim, m_spells.rogue.pHemorrhage))
        {
            if (DoCastSpell(pVictim, m_spells.rogue.pHemorrhage) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.rogue.pSinisterStrike &&
            CanTryToCastSpell(pVictim, m_spells.rogue.pSinisterStrike))
        {
            if (DoCastSpell(pVictim, m_spells.rogue.pSinisterStrike) == SPELL_CAST_OK)
                return;
        }

        if (m_spells.rogue.pSprint &&
           !me->HasUnitState(UNIT_STAT_ROOT) &&
           !me->CanReachWithMeleeAutoAttack(pVictim) &&
            CanTryToCastSpell(me, m_spells.rogue.pSprint))
        {
            if (DoCastSpell(me, m_spells.rogue.pSprint) == SPELL_CAST_OK)
                return;
        }
    }
}

bool PartyBotAI::EnterCombatDruidForm()
{
    if (m_spells.druid.pCatForm &&
        m_role == ROLE_MELEE_DPS &&
        CanTryToCastSpell(me, m_spells.druid.pCatForm))
    {
        if (DoCastSpell(me, m_spells.druid.pCatForm) == SPELL_CAST_OK)
            return true;
    }

    if (m_spells.druid.pBearForm &&
       (m_role == ROLE_TANK || m_role == ROLE_MELEE_DPS) &&
        CanTryToCastSpell(me, m_spells.druid.pBearForm))
    {
        if (DoCastSpell(me, m_spells.druid.pBearForm) == SPELL_CAST_OK)
            return true;
    }

    if (m_spells.druid.pMoonkinForm &&
        m_role == ROLE_RANGE_DPS &&
        CanTryToCastSpell(me, m_spells.druid.pMoonkinForm))
    {
        if (DoCastSpell(me, m_spells.druid.pMoonkinForm) == SPELL_CAST_OK)
            return true;
    }

    return false;
}

//BOT使用消耗品的判斷式
void PartyBotAI::PopulateConsumableSpellData()
{
	// Healing Potion
	if (me->GetLevel() >= 60)
		m_potionSpell = sSpellMgr.GetSpellEntry(PB_SPELL_POT_REJUV);
	else if (me->GetLevel() >= 45)
		m_potionSpell = sSpellMgr.GetSpellEntry(PB_SPELL_POT_HEAL_45);
	else if (me->GetLevel() >= 35)
		m_potionSpell = sSpellMgr.GetSpellEntry(PB_SPELL_POT_HEAL_35);
	else if (me->GetLevel() >= 21)
		m_potionSpell = sSpellMgr.GetSpellEntry(PB_SPELL_POT_HEAL_21);
	else if (me->GetLevel() >= 12)
		m_potionSpell = sSpellMgr.GetSpellEntry(PB_SPELL_POT_HEAL_12);
	else if (me->GetLevel() >= 3)
		m_potionSpell = sSpellMgr.GetSpellEntry(PB_SPELL_POT_HEAL_3);

	// Other Potions only apply to lvl 60+
	if (m_level < sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL))
		return;

	m_restPotion = sSpellMgr.GetSpellEntry(PB_SPELL_POT_RESTO);

	switch (m_role)
	{
	case ROLE_TANK:
		m_elixirSpell = sSpellMgr.GetSpellEntry(PB_SPELL_ELX_FORCE);
		m_flaskSpell = sSpellMgr.GetSpellEntry(PB_SPELL_FLASK_TITAN);
		break;
	case ROLE_HEALER:
		m_elixirSpell = sSpellMgr.GetSpellEntry(PB_SPELL_ELX_MAGEBL);
		m_flaskSpell = sSpellMgr.GetSpellEntry(PB_SPELL_FLASK_WISDOM);
		break;
	case ROLE_MELEE_DPS:
		m_elixirSpell = sSpellMgr.GetSpellEntry(PB_SPELL_ELX_MOONG);
		m_flaskSpell = sSpellMgr.GetSpellEntry(PB_SPELL_FLASK_TITAN);
		break;
	case ROLE_RANGE_DPS:
		if (m_class == CLASS_HUNTER)
		{
			m_elixirSpell = sSpellMgr.GetSpellEntry(PB_SPELL_ELX_MOONG);
			m_flaskSpell = sSpellMgr.GetSpellEntry(PB_SPELL_FLASK_TITAN);
		}
		else
		{
			m_elixirSpell = sSpellMgr.GetSpellEntry(PB_SPELL_ELX_MAGEBL);
			m_flaskSpell = sSpellMgr.GetSpellEntry(PB_SPELL_FLASK_SPOWER);
		}
		break;
	}
}

void PartyBotAI::UpdateOutOfCombatAI_Druid()
{
    // Make sure bot leaves combat form if his role is changed to healer. //若為治療身分且有變形狀態，則移除變形
    if (m_role == ROLE_HEALER && me->GetShapeshiftForm() != FORM_NONE &&
        me->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
    {
        me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT);
        return;
    }

    if (m_spells.druid.pGiftoftheWild) //野性賜福
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.druid.pGiftoftheWild))
        {
            if (CanTryToCastSpell(pTarget, m_spells.druid.pGiftoftheWild))
            {
                if (me->GetShapeshiftForm() != FORM_NONE)
                    me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT); //若為變身狀態則變回人形使用野性賜福
                if (DoCastSpell(pTarget, m_spells.druid.pGiftoftheWild) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }
    else if (m_spells.druid.pMarkoftheWild) //野性印記
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.druid.pMarkoftheWild))
        {
            if (CanTryToCastSpell(pTarget, m_spells.druid.pMarkoftheWild))
            {
                if (me->GetShapeshiftForm() != FORM_NONE)
                    me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT); //若為變身狀態則變回人形使用野性印記
                if (DoCastSpell(pTarget, m_spells.druid.pMarkoftheWild) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }

	if (m_spells.druid.pOmenOfClarity) //清晰預兆
	{
		if (CanTryToCastSpell(me, m_spells.druid.pOmenOfClarity))
		{
			if (me->GetShapeshiftForm() != FORM_NONE) //有變身情形下擊變回人形使用清晰預兆
				me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT);
			if (DoCastSpell(me, m_spells.druid.pOmenOfClarity) == SPELL_CAST_OK)
			{
				m_isBuffing = true;
				return;
			}
		}
	}

	if (m_spells.druid.pThorns && !me->GetGroup()->isRaidGroup()) //荊棘術
    {
        if (Player* pTarget = SelectBuffTarget(m_spells.druid.pThorns))
        {
            if (CanTryToCastSpell(pTarget, m_spells.druid.pThorns))
            {
                if (me->GetShapeshiftForm() != FORM_NONE)
                    me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT); //若為變身狀態則變回人形使用荊棘術
                if (DoCastSpell(pTarget, m_spells.druid.pThorns) == SPELL_CAST_OK)
                {
                    m_isBuffing = true;
                    return;
                }
            }
        }
    }

    if (m_isBuffing &&
       (!m_spells.druid.pMarkoftheWild ||
        !me->HasGCD(m_spells.druid.pMarkoftheWild)))
    {
        m_isBuffing = false;
    }

	// Dispels 使用驅毒術/消毒術
	SpellEntry const* pDispelSpell = m_spells.druid.pAbolishPoison ?
		m_spells.druid.pAbolishPoison :
		m_spells.druid.pCurePoison;
	if (pDispelSpell)
	{
		if (Unit* pFriend = SelectDispelTarget(pDispelSpell))
		{
			if (CanTryToCastSpell(pFriend, pDispelSpell))
			{
				if (DoCastSpell(pFriend, pDispelSpell) == SPELL_CAST_OK)
					return;
			}
		}
	}

	if (m_spells.druid.pRemoveCurse)
	{
		if (Unit* pFriend = SelectDispelTarget(m_spells.druid.pRemoveCurse))
		{
			if (CanTryToCastSpell(pFriend, m_spells.druid.pRemoveCurse))
			{
				if (DoCastSpell(pFriend, m_spells.druid.pRemoveCurse) == SPELL_CAST_OK)
					return;
			}
		}
	}

	if (m_role == ROLE_HEALER && FindAndHealInjuredAlly(90.0f))
		return;
	else
	{
		if (me->GetShapeshiftForm() == FORM_NONE)
		{
			if (EnterCombatDruidForm())
				return;
		}
		else if (me->GetShapeshiftForm() == FORM_CAT)
		{
			if (m_spells.druid.pProwl &&
				CanTryToCastSpell(me, m_spells.druid.pProwl))
			{
				if (DoCastSpell(me, m_spells.druid.pProwl) == SPELL_CAST_OK)
					return;
			}
		}
	}
}

void PartyBotAI::UpdateInCombatAI_Druid()
{
    ShapeshiftForm const form = me->GetShapeshiftForm();

    if (GetAttackersInRangeCount(10.0f) &&
        m_spells.druid.pBarkskin &&
        (form == FORM_NONE || form == FORM_MOONKIN) &&
        (me->GetHealthPercent() < 50.0f) &&
        CanTryToCastSpell(me, m_spells.druid.pBarkskin)) //取得10碼內的攻擊者，且如果沒有變形或為梟獸型態，且血量<50%，則用橡皮術
    {
        if (DoCastSpell(me, m_spells.druid.pBarkskin) == SPELL_CAST_OK)
            return;
    }

	// Critical Healing
	if (m_role == ROLE_TANK && me->GetHealthPercent() < 35.0f)
	{
		HealInjuredTargetDirect(me);
		return;
	}
	else
	{
		if (FindAndHealInjuredAlly(35.0f, 35.0f))
			return;
	}

	// Dispels
	SpellEntry const* pDispelSpell = m_spells.druid.pAbolishPoison ?
		m_spells.druid.pAbolishPoison :
		m_spells.druid.pCurePoison;
	if (pDispelSpell)
	{
		if (Unit* pFriend = SelectDispelTarget(pDispelSpell))
		{
			if (CanTryToCastSpell(pFriend, pDispelSpell))
			{
				if (DoCastSpell(pFriend, pDispelSpell) == SPELL_CAST_OK)
					return;
			}
		}
	}

	if (m_spells.druid.pRemoveCurse)
	{
		if (Unit* pFriend = SelectDispelTarget(m_spells.druid.pRemoveCurse))
		{
			if (CanTryToCastSpell(pFriend, m_spells.druid.pRemoveCurse))
			{
				if (DoCastSpell(pFriend, m_spells.druid.pRemoveCurse) == SPELL_CAST_OK)
					return;
			}
		}
	}

    if (m_role == ROLE_HEALER)
    {
        // Check group healing
        if (GetAlliesNeedingHealCount(20.0f, 70.0f) >= 3 &&
            m_spells.druid.pTranquility &&
            CanTryToCastSpell(me, m_spells.druid.pTranquility)) //寧靜
        {
            if (DoCastSpell(me, m_spells.druid.pTranquility) == SPELL_CAST_OK)
                return;
        }

		// Swiftmend
		if (Unit* pTarget = SelectHealTarget(50.0f, false))
		{
			if (m_spells.druid.pSwiftmend &&
				pTarget->HasAuraType(SPELL_AURA_PERIODIC_HEAL) &&
				CanTryToCastSpell(pTarget, m_spells.druid.pSwiftmend))
			{
				if (DoCastSpell(pTarget, m_spells.druid.pSwiftmend) == SPELL_CAST_OK)
					return;
			}
		}

		if (FindAndHealInjuredAlly(85.0f, 45.0f))
			return;
	}

    if (form == FORM_NONE)
    {
        if (m_spells.druid.pHibernate &&
            m_role != ROLE_TANK &&
            !me->GetAttackers().empty())
        {
            Unit* pAttacker = *me->GetAttackers().begin();
            if (CanTryToCastSpell(pAttacker, m_spells.druid.pHibernate) &&
                CanUseCrowdControl(m_spells.druid.pHibernate, pAttacker))
            {
                if (DoCastSpell(pAttacker, m_spells.druid.pHibernate) == SPELL_CAST_OK)
                    return;
            }
        }

        if (m_spells.druid.pInnervate &&
            (me->GetHealthPercent() > 40.0f) &&
            (me->GetPowerPercent(POWER_MANA) < 10.0f) &&
            CanTryToCastSpell(me, m_spells.druid.pInnervate)) //啟動
        {
            if (DoCastSpell(me, m_spells.druid.pInnervate) == SPELL_CAST_OK)
                return;
        }

        if (EnterCombatDruidForm())
            return;
    }

    Unit* pVictim = me->GetVictim();
    if (!pVictim)
        return;
    
    if (form != FORM_NONE &&
        me->HasUnitState(UNIT_STAT_ROOT) &&
        me->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT) &&
        (m_role != ROLE_TANK || !me->CanReachWithMeleeAutoAttack(pVictim)))
        me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT);

    if (m_role == ROLE_HEALER)
        return;
    
    switch (form)
    {
        case FORM_CAT:
        {
            if (me->HasDistanceCasterMovement())
                me->SetCasterChaseDistance(0.0f);

			if (m_spells.druid.pFuror && me->GetPower(POWER_ENERGY) <= 12)
			{
				me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT);
			}

            /*if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE
                && !me->CanReachWithMeleeAutoAttack(pVictim))
            {
                me->GetMotionMaster()->MoveChase(pVictim);
            }*/

            if (me->HasAuraType(SPELL_AURA_MOD_STEALTH))
            {
                if (m_spells.druid.pRavage &&
                    CanTryToCastSpell(pVictim, m_spells.druid.pRavage))
                {
                    if (DoCastSpell(pVictim, m_spells.druid.pRavage) == SPELL_CAST_OK)
                        return;
                }
				if (m_spells.druid.pPounce &&
					CanTryToCastSpell(pVictim, m_spells.druid.pPounce))
				{
					if (DoCastSpell(pVictim, m_spells.druid.pPounce) == SPELL_CAST_OK)
						return;
				}

				/*if (m_spells.druid.pTigersFury &&
					CanTryToCastSpell(me, m_spells.druid.pTigersFury))
				{
					if (DoCastSpell(me, m_spells.druid.pTigersFury) == SPELL_CAST_OK)
						return;
				}*/
                return;
            }

            if (m_spells.druid.pCower &&
                GetAttackersInRangeCount(8.0f))
            {
                Unit* pAttacker = *me->GetAttackers().begin();
                if (CanTryToCastSpell(me, m_spells.druid.pCower))
                {
                    if (DoCastSpell(me, m_spells.druid.pCower) == SPELL_CAST_OK)
                        return;
                }
            }

			if (me->GetComboPoints() > 4 ||
				(me->GetComboPoints() > 2 && pVictim->GetHealthPercent() < 10.0f))
            {
                if (m_spells.druid.pFerociousBite &&
                    CanTryToCastSpell(pVictim, m_spells.druid.pFerociousBite))
                {
                    if (DoCastSpell(pVictim, m_spells.druid.pFerociousBite) == SPELL_CAST_OK)
                        return;
                }

                if (m_spells.druid.pRip &&
                    CanTryToCastSpell(pVictim, m_spells.druid.pRip))
                {
                    if (DoCastSpell(pVictim, m_spells.druid.pRip) == SPELL_CAST_OK)
                        return;
                }
            }

            if (!me->CanReachWithMeleeAutoAttack(pVictim))
            {
                if (m_spells.druid.pFaerieFireFeral &&
                    CanTryToCastSpell(pVictim, m_spells.druid.pFaerieFireFeral))
                {
                    if (DoCastSpell(pVictim, m_spells.druid.pFaerieFireFeral) == SPELL_CAST_OK)
                        return;
                }

                if (m_spells.druid.pDash &&
                    pVictim->IsMoving() &&
                    CanTryToCastSpell(me, m_spells.druid.pDash))
                {
                    if (DoCastSpell(me, m_spells.druid.pDash) == SPELL_CAST_OK)
                        return;
                }
            }

            if (m_spells.druid.pRake &&
                CanTryToCastSpell(pVictim, m_spells.druid.pRake))
            {
                if (DoCastSpell(pVictim, m_spells.druid.pRake) == SPELL_CAST_OK)
                    return;
            }

			if (m_spells.druid.pShred)
			{
				if (CanTryToCastSpell(pVictim, m_spells.druid.pShred))
				{
					if (DoCastSpell(pVictim, m_spells.druid.pShred) == SPELL_CAST_OK)
						return;
				}
			}
			else if (m_spells.druid.pClaw &&
				CanTryToCastSpell(pVictim, m_spells.druid.pClaw))
            {
                if (DoCastSpell(pVictim, m_spells.druid.pClaw) == SPELL_CAST_OK)
                    return;
            }
                
            break;
        }
        case FORM_BEAR:
        case FORM_DIREBEAR:
        {
            if (me->HasDistanceCasterMovement())
                me->SetCasterChaseDistance(0.0f);

            /*if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE
                && !me->CanReachWithMeleeAutoAttack(pVictim))
            {
                me->GetMotionMaster()->MoveChase(pVictim);
            }*/

            if (m_spells.druid.pFeralCharge &&
                CanTryToCastSpell(pVictim, m_spells.druid.pFeralCharge)) //野性衝鋒
            {
                if (DoCastSpell(pVictim, m_spells.druid.pFeralCharge) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.druid.pBash &&
                CanTryToCastSpell(pVictim, m_spells.druid.pBash))
            {
                if (DoCastSpell(pVictim, m_spells.druid.pBash) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.druid.pFrenziedRegeneration &&
                (me->GetHealthPercent() < 30.0f) &&
                CanTryToCastSpell(me, m_spells.druid.pFrenziedRegeneration))
            {
                if (DoCastSpell(me, m_spells.druid.pFrenziedRegeneration) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.druid.pFaerieFireFeral &&
                CanTryToCastSpell(pVictim, m_spells.druid.pFaerieFireFeral))
            {
                if (DoCastSpell(pVictim, m_spells.druid.pFaerieFireFeral) == SPELL_CAST_OK)
                    return;
            }

            if ((me->GetPower(POWER_RAGE) > 80) ||
                (GetAttackersInRangeCount(10.0f) > 1))
            {
                if (m_spells.druid.pDemoralizingRoar &&
                    CanTryToCastSpell(pVictim, m_spells.druid.pDemoralizingRoar))
                {
                    if (DoCastSpell(pVictim, m_spells.druid.pDemoralizingRoar) == SPELL_CAST_OK)
                        return;
                }

                if (m_spells.druid.pSwipe &&
                    CanTryToCastSpell(pVictim, m_spells.druid.pSwipe))
                {
                    if (DoCastSpell(pVictim, m_spells.druid.pSwipe) == SPELL_CAST_OK)
                        return;
                }
            }

            if (m_spells.druid.pMaul &&
                CanTryToCastSpell(pVictim, m_spells.druid.pMaul))
            {
                if (DoCastSpell(pVictim, m_spells.druid.pMaul) == SPELL_CAST_OK)
                    return;
            }
            break;
        }
        case FORM_NONE:
        case FORM_MOONKIN:
        {
			if (pVictim->CanReachWithMeleeAutoAttack(me) &&
                    (pVictim->GetVictim() == me) &&
                    !me->HasUnitState(UNIT_STAT_ROOT) &&
                    (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != DISTANCING_MOTION_TYPE))
            {
                if (m_spells.druid.pEntanglingRoots &&
                    CanTryToCastSpell(pVictim, m_spells.druid.pEntanglingRoots))
                {
                    {
                        RunAwayFromTarget(pVictim);
                        return;
                    }
                }
            }

            if (m_spells.druid.pHurricane &&
				m_aoeSpellTimer <= 0 &&
                (me->GetEnemyCountInRadiusAround(pVictim, 8.0f) > 3) &&
                pVictim->GetHealthPercent() < 75.0f &&
                CanTryToCastSpell(pVictim, m_spells.druid.pHurricane)) //颶風術
            {
                if (DoCastSpell(pVictim, m_spells.druid.pHurricane) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.druid.pNaturesGrasp &&
                CanTryToCastSpell(me, m_spells.druid.pNaturesGrasp)) //自然之握
            {
                if (DoCastSpell(me, m_spells.druid.pNaturesGrasp) == SPELL_CAST_OK)
					return;
            }

            if (m_spells.druid.pFaerieFire &&
               (pVictim->GetClass() == CLASS_ROGUE) &&
                CanTryToCastSpell(pVictim, m_spells.druid.pFaerieFire))
            {
                if (DoCastSpell(pVictim, m_spells.druid.pFaerieFire) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.druid.pInsectSwarm &&
                CanTryToCastSpell(pVictim, m_spells.druid.pInsectSwarm))
            {
                if (DoCastSpell(pVictim, m_spells.druid.pInsectSwarm) == SPELL_CAST_OK)
                    return;
            }

            if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == DISTANCING_MOTION_TYPE)
                return;

            if (m_spells.druid.pHurricane &&
               (me->GetEnemyCountInRadiusAround(pVictim, 10.0f) > 2) &&
                CanTryToCastSpell(pVictim, m_spells.druid.pHurricane))
            {
                if (DoCastSpell(pVictim, m_spells.druid.pHurricane) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.druid.pMoonfire &&
                CanTryToCastSpell(pVictim, m_spells.druid.pMoonfire)) //月火術
            {
                if (DoCastSpell(pVictim, m_spells.druid.pMoonfire) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.druid.pStarfire &&
               (pVictim->GetHealthPercent() > 50.0f) &&
                CanTryToCastSpell(pVictim, m_spells.druid.pStarfire)) //星火術
            {
                if (DoCastSpell(pVictim, m_spells.druid.pStarfire) == SPELL_CAST_OK)
                    return;
            }

            if (m_spells.druid.pWrath &&
                CanTryToCastSpell(pVictim, m_spells.druid.pWrath))
            {
                if (DoCastSpell(pVictim, m_spells.druid.pWrath) == SPELL_CAST_OK)
                    return;
            }

            break;
        }
    }
}

bool PartyBotAI::CheckBossMechanics()
{
	// Return FALSE while not ok with desired mechanics

	// If not in Raid Group or Inside Dungeon return
	if (!(me->GetMap()->IsDungeon() || me->GetGroup()->isRaidGroup()))
		return true;

	switch (me->GetMap()->GetId())
	{
		// MOLTEN CORE
	case 409:

		// MAGMADAR - Fire Bomb
		if (GameObject* pBomb = me->FindNearestGameObject(177704, 6.0f))
		{
			RunAwayFromObject(pBomb, 8.0f, me->GetVictim());
			return false;
		}

		// GEHENNAS - Rain of Fire
		if (me->HasAura(19717))
		{
			RunAwayFromAOE(12.0f);
			return false;
		}

		// GARR
		if (Unit* pVictim = me->GetVictim())
		{
			if (pVictim->GetEntry() == 12057)
				m_aoeSpellTimer = 30 * IN_MILLISECONDS;
		}

	default:
		break;
	}

	return true;
}
