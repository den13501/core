DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20210128215744');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20210128215744');
-- Add your query below.


-- Corrections to page texts.
DELETE FROM `page_text` WHERE `entry` IN (712, 713, 714);
INSERT INTO `page_text` (`entry`, `text`, `next_page`) VALUES (791, 'I will describe the surrounding lands as the scouts of Kargath have surveyed:\r\n\r\n-Red, rocky hills and dry flats that offer little support for life.\r\n-A blazing sun and severe winds.  \r\n-No lakes or streams.  Not even scattered pools.  To find water denizens must dig deep, muddy wells, or suck scant moisture from the rare cactus or spiny weed.\r\n\r\nIn short: hot, hard living.', 792);
INSERT INTO `page_text` (`entry`, `text`, `next_page`) VALUES (792, 'The Badlands are filled with enemies.  Ogres roam the blistering sands, ambushing the unwary.  Dark Iron dwarves inhabit a barracks east of Kargath and battle their lighter-skinned cousins in Loch Modan to the north.  Brutal, primitive beasts called Troggs haunt any scrap of shade they find and defend it savagely.\r\n\r\nAnd in eastern Badlands, in the Lethlor Ravine, there are dragons.  We don\'t know how many and we don\'t know how big, since scouts who get too close never return.', 793);
INSERT INTO `page_text` (`entry`, `text`, `next_page`) VALUES (793, 'It need not be said that we--those garrisoned at Kargath--are quite happy with our assignment.  We stay tough here, because if we get soft then we die.\r\n\r\nAnd I wouldn\'t have it any other way.\r\n\r\nNeeka Bloodscar\r\nHead Scout, Kargath', 0);
UPDATE `page_text` SET `text`='A Report on the State of the Frostmane Trolls in the General Area of Coldridge Valley\r\n\r\nPrepared by Grelin Whitebeard, Senate Special Envoy\r\n\r\nFrom the time that I have spent observing the movement of the Frostmane trolls in the Coldridge Valley area, I have determined that they pose no large threat to dwarven settlements in the area. Moreover, they are a threat that can be eliminated with little additional support from the army. Through the assistance of Mountaineers already stationed in' WHERE `entry`=90;
UPDATE `page_text` SET `text`='DAY ONE\r\n\r\nThe apprentice and I have arrived in Coldridge Valley today. The trip through the cave was mostly uneventful. We made camp a good distance away from the cave we\'re told the trolls have gathered in.\r\n\r\nDAY TWO\r\n\r\nBloody wolf howling almost kept me up all night.\r\n\r\nI will have new wolfhide clothing in a few days.\r\n\r\nThe lad got tangled up with a trogg today, put up a fight, and' WHERE `entry`=74;
UPDATE `page_text` SET `text`='Grelin,\r\n\r\nMy time is short and many matters press on my time, and I hope that your investigation of the trolls will not be one of them. Therefore I will allow you to use my authority in dealing with the trolls in whatever fashion you deem necessary, more so if you are able to find an expedient solution.\r\n\r\n\r\nMagni Bronzebeard' WHERE `entry`=80;
UPDATE `page_text` SET `text`='managed to get the better of the ugly brute, but he\'s now nursing a nasty cut on his arm. Looks like I\'ll have to do the chores for a while.\r\n\r\nDAY THREE\r\n\r\nCold. Snowed a bit around noon.\r\n\r\nDAY FOUR\r\n\r\nThe lad was back and in good spirits today, so we took our first look at the trolls. Frostmane, I\'d say, judging by the markings on their skin and the various trinkets they wore on their bodies.' WHERE `entry`=81;
UPDATE `page_text` SET `text`='DAY FIVE\r\n\r\nHad the lad watch over the camp and I snuck over to the cave and took a look around. The trolls\' numbers are somewhat troublesome. The Mountaineers might have to be summoned in force if the cave is to be cleared of the troll infestation.\r\n\r\nI realize I have not mentioned the troggs of late. They appear in the area in greater numbers, but they are so primitive that they do not pose much of a threat. Time may say if this is true or not.' WHERE `entry`=82;
UPDATE `page_text` SET `text`=' Led by Grom Hellscream, all the clan chiefs except Durotan drank and thereby sealed their fates as slaves to the Burning Legion. Empowered by Mannoroth\'s rage, the chieftains unwittingly extended this subjugation to their unsuspecting brethren. ' WHERE `entry`=1954;
UPDATE `page_text` SET `text`='And not a drop of ale for almost a week now.\r\n\r\nDAY SIX\r\n\r\nCold again. Snows. Trolls. No ale.\r\n\r\nDAY SEVEN\r\n\r\nSnow below so white,\r\nSky above so blue,\r\nWolves will howl the night,\r\nNot a drop of brew.\r\n\r\nDAY EIGHT\r\n\r\nThe trolls are perhaps not as large a problem as we initially thought. They have some' WHERE `entry`=83;
UPDATE `page_text` SET `text`='While his confusion and misery deepened, Sargeras was forced to contend with another group intent on disrupting the Titans\' order: the Nathrezim. This dark race of vampiric demons (also known as dreadlords) conquered a number of populated worlds by possessing their inhabitants and turning them to the shadow. ' WHERE `entry`=1776;
UPDATE `page_text` SET `text`='Coldridge Valley and mercenaries (paid with funds set aside by the Senate prior to my dispatchment), I am confident that the problem will be solved in short order. \r\n\r\nThis action has been authorized with the sanction given to me by King Bronzebeard.' WHERE `entry`=87;
UPDATE `page_text` SET `text`='A Report on the State of the Frostmane Trolls in the General Area of Dun Morogh\r\n\r\nThe trolls situated in Dun Morogh are largely centralized in Frostmane Hold, a mountain cave on the western border. They have sufficient numbers to cause some concern, however, they seem more than content to stay in their cave. This is, no doubt, because they do not wish to incur the wrath of the dwarves again, and risk total extermination. Their actions can be considered territorial, if anything, and it is' WHERE `entry`=88;
UPDATE `page_text` SET `text`='my belief that they pose no real threat to us, so long as we do not encroach upon their territory. This may be a situation unappealing to the dwarven populace, but given the dispersal of military resources, it may be prudent to relegate the extermination of the trolls to a lower level of importance, and continue to focus on the threat posed by the troggs and the Dark Irons.\r\n\r\nEnclosed, you will also find a copy of my brother Grelin\'s report on Anvilmar.\r\n\r\nSigned,\r\nSenir Whitebeard' WHERE `entry`=89;
UPDATE `page_text` SET `text`='Coldridge Valley and mercenaries (paid with funds set aside by the Senate prior to my dispatchment), I am confident that the problem will be solved in short order. \r\n\r\nThis action has been authorized with the sanction given to me by King Bronzebeard.' WHERE `entry`=91;
UPDATE `page_text` SET `text`='<HTML>\r\n<BODY>\r\n<IMG src=\"Interface\\Pictures\\14679_Tirion_256\"/>\r\n</BODY>\r\n</HTML>\r\n' WHERE `entry`=2351;
UPDATE `page_text` SET `text`='Lord Bethor Iceshard,\r\n\r\nAs per your instructions, I send to you the agent you requested.  It is the bearer of this note.\r\n\r\nThis person has shown to be dependable and able to follow orders, is proven against the forces of the Scourge, and is my choice for your mission.\r\n\r\nMay She reign supreme,\r\n-Magistrate Sevren\r\n\r\n' WHERE `entry`=244;
UPDATE `page_text` SET `text`='General Turalyon\r\n\r\nFormer Lieutenant to Lord Anduin Lothar. Knight of the Silver Hand. High General of the Alliance Expedition that marched into the orc homeworld of Draenor. Presumed deceased.\r\n\r\nEsarus thar no\'Darador\' - By Blood and Honor We Serve. \r\nYou were the right hand of justice and virtue, old friend. Your name will be honored in our halls always.\r\n\r\n- Lord Uther the Lightbringer - Knight of the Silver Hand' WHERE `entry`=290;
UPDATE `page_text` SET `text`='I started this journal so I could keep notes on my quest to help Ashenvale. There is a mystery to some of the events that occurred not too long ago, and hopefully I will be able to unravel some of it in order to help my people.\r\n\r\nLet me start by putting down facts so they don\'t slip my mind at a later date.\r\n\r\nI\'ve recently found truth to the rumors of the wizard Dartol\'s efforts.' WHERE `entry`=403;
UPDATE `page_text` SET `text`='Where once I thought it preposterous that a human would come to our lands and learn our ways, this wizard, this evil man, came here and not only survived, but also gained some of our knowledge. I\'m still uncertain how...\r\n\r\nI never discovered his goals during my investigation, but his plan seemed simple: using druidic magic, he wanted to befriend and then control the furbolg. If it was in an attempt to harm my kin, or for some other malicious purpose, I hope to find out before my path ends.' WHERE `entry`=404;
UPDATE `page_text` SET `text`='Regardless, he was apparently more successful than naught in actualizing his plans. Did he want to attempt his machinations on the furbolg before trying on my people? Did the furbolg have something he coveted? Who knows?\r\n\r\nUsing an item he created (a rod or staff of some kind), he attempted to infiltrate the furbolg tribes of Ashenvale. At some point, and this is where many of the details are still unclear, he was discovered by the furbolg while trying to manipulate them into acting against' WHERE `entry`=405;
UPDATE `page_text` SET `text`='Peeling the Onion\r\nThe How-to Guide On Dismantling the Stormpike \r\n-By Drek\'Thar\r\n\r\nWithin these pages you will find a wealth of knowledge on battle tactics and politics. The learned soldier is the soldier that leans on the shoulder of experience. Let this book serve as a guide in your battle for Alterac Valley.\r\n' WHERE `entry`=2771;
UPDATE `page_text` SET `text`='one another. As I\'m sure the elves would be, the furbolg were angered, but they reacted much more strongly and killed Dartol.\r\n\r\nThe furbolg, at least at this time, weren\'t the same corrupted creatures they\'ve become. They were still rational and intelligent--their relationship with our people amicable.\r\n\r\nI\'m hoping that if I can recreate the rod with the help of a dryad named Shael\'dryn, I can use its power to help our people... and the furbolg.' WHERE `entry`=406;
UPDATE `page_text` SET `text`='Not all the furbolg have been corrupted. Some still live and try to protect the forest. During their corruption, some of the furbolg fled, many were killed, and others were forced out of their tribes.\r\n\r\nI found a venerable furbolg of the Foulweald tribe living above Lake Mystral--his name is Krolg.\r\n\r\nI\'ve watched him for days, and I think if I were to approach him in the guise of a furbolg, I could help him and discover a way to re-establish a bond between our people.' WHERE `entry`=407;
UPDATE `page_text` SET `text`='Along with killing Dartol, the furbolg split up the rod into three parts so it couldn\'t be used against them again. It has been difficult, but I\'ve a good idea where all three parts were placed.\r\n\r\nThe Gem\r\nThe first part of the rod, a glowing gem, was hidden in a shrine in Northwestern Ashenvale. I believe now this shrine is the ruins at the center of Lake Falathim. The Sentinels tell me that it\'s been inhabited by murlocs now.' WHERE `entry`=408;
UPDATE `page_text` SET `text`='If I can\'t find the gem hidden in the shrine, it might be in the possession of one of the murlocs.\r\n\r\nThe shaft portion\r\nThis part of the rod was given to the treants near what is now called Felwood. Neither the furbolg nor my kind could have suspected that such magnificent creatures could ever fall to the corruption that\'s overtaken the land.\r\n\r\nMy research tells me that the guardians kept the piece in a small glade locked within a chest. To find out any more, I\'ll have to speak to Shael\'dryn.' WHERE `entry`=409;
UPDATE `page_text` SET `text`='Shael\'dryn is a dryad who protects the moonwell northeast of Lake Iris. She refuses to leave the forest or forsake it to the corruption. I know she has the power and knowledge to repair the rod, or to at least tell me how I can do it on my own.\r\n\r\nThe pommel\r\nThe pommel of the rod was given to the druids of Dor\'danil. There is one major problem with this though: the druids are dead.\r\n\r\nTheir spirits now inhabit the area and are no longer hospitable.' WHERE `entry`=411;
UPDATE `page_text` SET `text`='This may require more investigation. I\'m not sure I\'m powerful enough to fight the spirits of my dead kin...let alone delve into the depths of Dor\'danil and find the pommel.\r\n\r\n(Note: During my preparations in Astranaar, I\'ve recently met a dwarf hunter who has spent a good portion of his time in Ashenvale trying to help my people. He came from a place called Stormwind.\r\n\r\nWe spoke over a few ales one night, and his tales have given me new hope of finding the pommel...' WHERE `entry`=412;
UPDATE `page_text` SET `text`='He tells me he\'s been throughout all of Dor\'danil, and he\'s never seen a chest or any container that may hold the pommel. \r\n\r\nHe also tells me that rotting slimes have inhabited the area, and they devour almost anything smaller than them. He\'s seen them \"eat\" tables, sculptures, bears, and even gnomes!\r\n\r\nThe slimes seem to gain a great deal of sustenance from things magical. If the chest holding the pommel was enchanted at all, the slimes might have eaten it.' WHERE `entry`=413;
UPDATE `page_text` SET `text`='It\'s a gamble, but I have no other clues at this time...\r\n\r\nAs I find out more I\'ll put the details here; but until then, I shall work on finding the parts of the rod and helping Ashenvale.' WHERE `entry`=414;
UPDATE `page_text` SET `text`='The goblin Nazz Steamboil is really the son of a goblin merchant prince (Which prince?  The price of that information is high).\r\n\r\nIt seems he much rather enjoys spending the money his family makes than he does earning it himself.  So he stole a small fortune from his family\'s hoard and is now hiding in the Shimmering Flats.\r\n\r\nIf his father knew where he was, he\'d be sure to seek him out and drag him back home... minus a toe for his insolence.' WHERE `entry`=438;
UPDATE `page_text` SET `text`='For many years, the night elves worked tirelessly to rebuild what they could of their ancient homeland. Leaving their broken temples and roads to be overgrown, they constructed their new homes amidst the verdant trees and shadowed hills at Hyjal\'s base. In time, the dragons that had survived the great Sundering came forth from their secret abodes. ' WHERE `entry`=1836;
UPDATE `page_text` SET `next_page`=791 WHERE `entry`=711;
UPDATE `page_text` SET `text`='Helgrum,\r\n\r\nMy compliments to whomever issued the order to establish our base of Kargath in the Badlands.  It is an ideal locale to train our troops.  Its harsh weather, vicious wildlife, warlike natives and complete lack of outside support make this place a crucible from which only the finest warriors and scouts will emerge.\r\n\r\nGood planning.  Well done.' WHERE `entry`=711;
UPDATE `page_text` SET `text`='Consumed with the curse of this new bloodlust, the orcs sought to unleash their fury on any who stood before them. Sensing that the time had come, Gul\'dan united the warring clans into a single unstoppable Horde. ' WHERE `entry`=1955;
UPDATE `page_text` SET `text`='Calling themselves dwarves, the last of the earthen left the halls of Uldaman and ventured out into the waking world. Still lulled by the safety and wonders of the deep places, they founded a vast kingdom under the highest mountain in the land. ' WHERE `entry`=1895;
UPDATE `page_text` SET `text`='Commander,\r\n\r\nReturn to Orgrimmar. Your forces inadequate. Must reanalyze our position based upon new information.\r\n\r\nLarge number of Shadowsworn and Ogres present. Demons guard the Dark Portal.\r\n\r\n-Thrall, Warchief of the Horde\r\n' WHERE `entry`=1071;
UPDATE `page_text` SET `text`='Ysera, the Dreamer, also placed an enchantment upon the World Tree by linking it to her own realm, the ethereal dimension known as the Emerald Dream. The Emerald Dream, a vast, ever-changing spirit world, existed outside the boundaries of the physical world. From the Dream, Ysera regulated the ebb and flow of nature and the evolutionary path of the world itself. ' WHERE `entry`=1842;
UPDATE `page_text` SET `text`='Greetings and Salutations, Adventurers!\r\n\r\nI, Krinkle Goodsteel, have need of those willing to put themselves at risk in order to complete some of my most arduous tasks. Because of my many duties and the workload I\'ve managed to take upon myself, I ensure that anyone brave enough to complete this list of items and return them to me intact will be paid handsomely. \r\n\r\nThe list is contained on the following pages...' WHERE `entry`=1551;
UPDATE `page_text` SET `text`='Solid Crystal Leg Shafts - \r\n\r\nThe Glassweb spiders of Searing Gorge are made of an incredible crystal-like material. Their legs, if not damaged when they\'re killed, make for a wonderful conductor in some of my companions\' engineering experiments.\r\n\r\nI will need a number of them to test  upon. The spiders having eight possible legs themselves should be no problem for a stalwart warrior or practiced mage.' WHERE `entry`=1552;
UPDATE `page_text` SET `text`='An Overdue Package -\r\n\r\nI hired someone who I thought was a reliable pilot to bring me a package from Theramore. I was apparently wrong. And even though the pilot lived to tell the tale, he left his entire zepplin and all of its cargo behind to save his own neck.\r\n\r\nWell, I need that package back. From what Beezil tells me, he crashed just west of the bay in Dustwallow Marsh. It went down just after he crossed the hills along the water\'s edge.\r\n\r\nHmmm... never did tell me what caused him to crash... ' WHERE `entry`=1553;
UPDATE `page_text` SET `text`='Goodsteel\'s Balanced Flameberge - \r\n\r\nFinally, I want one of my finest works of blacksmithing to date. This flameberge was an incredible sword that I bestowed upon what I thought was a very honorable and great warrior. Well, he was trounced by a murloc named Jarquai? Something like that. \r\n\r\nIt was while he was traveling along the coast of the Swamp of Sorrows when he thought to attack the creature. He failed and apparently fled, but not before leaving the weapon behind for this murloc to take.' WHERE `entry`=1554;
UPDATE `page_text` SET `text`='Find me these items and return to Gadgetzan with them all, along with this ledger, and I will reward you. ' WHERE `entry`=1556;
UPDATE `page_text` SET `text`='As doubt and despair overwhelmed Sargeras\' senses, he lost all faith not only in his mission, but also in the Titans\' vision of an ordered universe. Eventually he came to believe that the concept of order itself was folly, and that chaos and depravity were the only absolutes within the dark, lonely universe. ' WHERE `entry`=1778;
UPDATE `page_text` SET `text`='In his fury, Sargeras shattered the prisons of the eredar and the Nathrezim and set the loathsome demons free. These cunning creatures bowed before the dark Titan\'s vast rage and offered to serve him in whatever malicious ways they could. From the ranks of the powerful Eredar, Sargeras picked two champions to command his demonic army of destruction. ' WHERE `entry`=1782;
UPDATE `page_text` SET `text`='Kil\'jaeden the Deceiver was chosen to seek out the darkest races in the universe and recruit them into Sargeras\' ranks. The second champion, Archimonde the Defiler, was chosen to lead Sargeras\' vast armies into battle against any who might resist the Titan\'s will. ' WHERE `entry`=1783;
UPDATE `page_text` SET `text`='Alexstrasza the red, Ysera the green, and Nozdormu the bronze descended upon the druids\' tranquil glades and surveyed the fruits of the night elves\' labors. Malfurion, who had become an arch-druid of immense power, greeted the mighty dragons and told them about the creation of the new Well of Eternity. ' WHERE `entry`=1837;
UPDATE `page_text` SET `text`='Alexstrasza, the Lifebinder, placed a single, enchanted acorn within the heart of the Well of Eternity. The acorn, activated by the potent, magical waters, sprung to life as a colossal tree. The mighty tree\'s roots grew from the Well\'s waters, and its verdant canopy seemed to scrape the roof of the sky. ' WHERE `entry`=1839;
UPDATE `page_text` SET `text`='The immense tree would be an everlasting symbol of the night elves\' bond with nature, and its life-giving energies would extend out to heal the rest of the world over time. The night elves\' gave their World Tree the new name Nordrassil, which meant \"crown of the heavens\" in their native tongue. ' WHERE `entry`=1840;
UPDATE `page_text` SET `text`='Nozdormu, the Timeless, placed an enchantment upon the World Tree to ensure that as long as the colossal tree stood, the night elves would never age or fall prey to sickness or disease. ' WHERE `entry`=1841;
UPDATE `page_text` SET `text`='In the ancient times, after the Titans departed Azeroth, their children, known as the earthen, continued to shape and guard the deep recesses of the world. The earthen were largely unconcerned with the affairs of the surface-dwelling races and longed only to plumb the dark depths of the earth. ' WHERE `entry`=1892;
UPDATE `page_text` SET `text`='When the world was sundered by the Well of Eternity\'s implosion, the earthen were deeply affected. Reeling with the pain of the earth itself, the earthen lost much of their identity and sealed themselves within the stone chambers where they were first created. Uldaman, Uldum, Ulduar... these were the names of the ancient Titan cities where the earthen first took shape and form. Buried deep beneath the world, the earthen rested in peace for nearly eight thousand years. ' WHERE `entry`=1893;
UPDATE `page_text` SET `text`='Epilogue\r\n\r\nAfter having done all of this, you are left with the center of the onion: The sweet core. Vanndar Stormpike will be left defenseless and alone. Rules of military conduct require that we ask for his surrender before carrying out any executions. Be sure to mention the surrender thing when you see him... then kill him.' WHERE `entry`=2778;
UPDATE `page_text` SET `text`='The orcs became increasingly aggressive under the secret control of Gul\'dan and his Shadow Council. They constructed massive arenas where the orcs honed their warrior skills in trials of combat and death. During this period, a few clan chieftains spoke out against the growing depravity in their race. ' WHERE `entry`=1951;
UPDATE `page_text` SET `text`='Kil\'jaeden knew that the orc clans were almost ready, but he needed to be certain of their ultimate loyalty. In secret, he had the Shadow Council summon Mannoroth the Destructor, the living vessel of destruction and rage. Gul\'dan called the clan chieftains together and convinced them that drinking Mannoroth\'s raging blood would make them utterly invincible.\r\n' WHERE `entry`=1953;
UPDATE `page_text` SET `text`='Kil\'jaeden knew that the Horde was finally prepared. The orcs had become the Burning Legion\'s greatest weapon. The cunning demon shared his knowledge with his waiting master, and Sargeras agreed that the time of his revenge had finally come. ' WHERE `entry`=1958;
UPDATE `page_text` SET `text`='The Grand Admiral forced Jaina to make a terrible decision: support him in battle against the orcs and betray her newfound allies, or fight her own father to maintain the fragile peace that the Alliance and the Horde had finally attained. After much soul-searching, Jaina chose the latter and helped Thrall defeat her crazed father. ' WHERE `entry`=2110;
UPDATE `page_text` SET `text`='Archbishop Alonsus Faol\r\n\r\nBenevolent patron of the Church of Light.\r\n\r\nThough he began his good work in Stratholme, Lordaeron, Archbishop Faol was a great friend to the people of Stormwind. In the dark days after the Second War, he helped to reform the Brotherhood of Northshire and raised vast funds to rebuild Stormwind city itself.\r\n\r\nThis Cathedral stands not only as a bastion of the Holy Light, but as a lasting testament to one man\'s noble spirit and generosity. ' WHERE `entry`=2291;
UPDATE `page_text` SET `text`='This intact pteradon skeleton was recovered from the remote Un\'Goro Crater. Based on the skeletal structure, it is clear that this specific genus has not yet been encountered. This skeleton could have been preserved for any number of centuries beneath the region\'s rich soil. \r\n' WHERE `entry`=2311;
UPDATE `page_text` SET `text`='Beware, soldier, as both of these towers are heavily fortified and ruled over by one of Vanndar\'s elite Commanders. Should your forces breach the fortifications, make certain that the Commander within has been ... silenced. This too will be part of the dismantling of the Stormpike.\r\n' WHERE `entry`=2774;
UPDATE `page_text` SET `text`='Chapter 1 - The Front Line\r\n\r\nDismantling the Stormpike army is very much like peeling an onion. To get to the core, you must start by removing the outermost layers.\r\n\r\nThe front lines, comprised mostly of Stormpike Mountaineers and Alliance Sentinels, are tied to the Captain\'s bunker. It is Captain Balinda Stonehearth who empowers these units and provides for reinforcements when the lines are under siege. Strike at the Captain and the front line forces will crumble.\r\n\r\n' WHERE `entry`=2772;
UPDATE `page_text` SET `text`='Chapter 2 - The Twin Towers\r\n\r\nMake no mistake; Vanndar Stormpike is a cunning foe and certainly no fool. Once the front line has been breached, the secondary defensive targets must still be destroyed. It is the twin towers of Stonehearth and Icewing which control the Stormpike Guardsmen outside of Dun Baldar and the Stormpike patrols.' WHERE `entry`=2773;
UPDATE `page_text` SET `text`='Chapter 3 - The Four Commanders\r\n\r\nThe third layer of the Stormpike onion is comprised of the four Commanders. In this respect, Vanndar has mimicked our own glorious Frostwolf defenses. Of course he will tell you otherwise... But I digress. \r\n\r\nThe four Commanders control the ebb and flow of the Stormpike Guardsmen that fiercely guard Dun Baldar. Silence them all and the Stormpike Guardsmen will fall. \r\n\r\nThen there is but one layer left to peel.\r\n' WHERE `entry`=2775;
UPDATE `page_text` SET `text`='Chapter 4 - The Dun Baldar Bunkers\r\n\r\nAs you have undoubtedly noticed, the Stormpike defensive layers are in place to prevent one mighty power move from dismantling the entire army. Before you ask, yes, this is exactly how our own forces are setup and no, I will not change our defensive structure. They copied us, why should we have to change?\r\n' WHERE `entry`=2776;
UPDATE `page_text` SET `text`='More rapid than eagles his coursers they came,$B$BAnd he whistled, and shouted, and called them by name;$B$B\"Now, Mercer! now, Chilton! now, Jordan and Kaplan!$B$BOn, Nagle! on Pardo! on, Goodman and Metzen!$B$BTo the top of the porch! to the top of the wall!$B$BNow dash away! dash away! dash away all!\"\r\n' WHERE `entry`=2844;

-- Corrections to npc texts.
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6236, 8817, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6242, 8826, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6714, 9106, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6799, 9238, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6805, 9244, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6807, 9246, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6810, 9249, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6813, 9263, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6816, 9266, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6819, 9269, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6822, 9272, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6826, 9276, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6829, 9279, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6835, 9285, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6865, 9328, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (6873, 9340, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (8346, 11933, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`, `BroadcastTextID1`, `Probability1`, `BroadcastTextID2`, `Probability2`, `BroadcastTextID3`, `Probability3`, `BroadcastTextID4`, `Probability4`, `BroadcastTextID5`, `Probability5`, `BroadcastTextID6`, `Probability6`, `BroadcastTextID7`, `Probability7`) VALUES (8653, 12738, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (2115, 1, 0, 0, 0, 0, 0, 0, 0, 4538, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (6061, 1, 0, 0, 0, 0, 0, 0, 0, 8589, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (6798, 1, 0, 0, 0, 0, 0, 0, 0, 9234, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (6832, 1, 0, 0, 0, 0, 0, 0, 0, 9282, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (6838, 1, 0, 0, 0, 0, 0, 0, 0, 9288, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (6848, 1, 0, 0, 0, 0, 0, 0, 0, 9305, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (6871, 1, 0, 0, 0, 0, 0, 0, 0, 9338, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (7361, 1, 0, 0, 0, 0, 0, 0, 0, 10078, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (8507, 1, 0, 0, 0, 0, 0, 0, 0, 12247, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (8516, 1, 0, 0, 0, 0, 0, 0, 0, 12280, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `npc_text` (`ID`, `Probability0`, `Probability1`, `Probability2`, `Probability3`, `Probability4`, `Probability5`, `Probability6`, `Probability7`, `BroadcastTextID0`, `BroadcastTextID1`, `BroadcastTextID2`, `BroadcastTextID3`, `BroadcastTextID4`, `BroadcastTextID5`, `BroadcastTextID6`, `BroadcastTextID7`) VALUES (8554, 1, 0, 0, 0, 0, 0, 0, 0, 12402, 0, 0, 0, 0, 0, 0, 0);

-- Corrections to gameobjects.
UPDATE `gameobject_template` SET `size`=5 WHERE `entry`=1607;
UPDATE `gameobject_template` SET `size`=3 WHERE `entry`=18603;
UPDATE `gameobject_template` SET `size`=1.2 WHERE `entry`=164954;
UPDATE `gameobject_template` SET `size`=0.75 WHERE `entry`=177681;
UPDATE `gameobject_template` SET `size`=0.75 WHERE `entry`=177683;
UPDATE `gameobject_template` SET `size`=1.5 WHERE `entry`=179664;
UPDATE `gameobject_template` SET `size`=2 WHERE `entry`=181374;
UPDATE `gameobject_template` SET `displayId`=1407 WHERE `entry`=177277;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`) VALUES (181444, 1, 6696, 'Kel\'Thuzad Trigger', 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;