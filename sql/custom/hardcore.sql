-- Remove Spirit Healers (6491), Alliance Spirit Guides (13116), and Horde Spirit Guides (13117)
DELETE FROM `creature` WHERE `guid` IN (6491, 13116, 13117);

-- Remove binding from items
UPDATE `item_template` SET `bonding` = 0;
