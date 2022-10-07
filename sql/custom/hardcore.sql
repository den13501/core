-- Remove Spirit Healers (6491), Alliance Spirit Guides (13116), and Horde Spirit Guides (13117)
DELETE FROM `creature` WHERE `guid` IN (6491, 13116, 13117);

-- BattleGroundEvent: missing db-data for map:489, event1:2, event2:0 ("Spirit Guides")
DELETE FROM `battleground_events` WHERE `map` = 489 && `event1` = 2 && `event2` = 0;
-- BattleGroundEvent: creature with nonexistent guid 150380 for event: map:0, event1:0, event2:1 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150002 for event: map:0, event1:0, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150387 for event: map:0, event1:0, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150003 for event: map:0, event1:0, event2:4 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150381 for event: map:0, event1:1, event2:1 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150004 for event: map:0, event1:1, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150388 for event: map:0, event1:1, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150005 for event: map:0, event1:1, event2:4 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150000 for event: map:0, event1:2, event2:0 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150001 for event: map:0, event1:2, event2:0 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150382 for event: map:0, event1:2, event2:1 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150006 for event: map:0, event1:2, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150389 for event: map:0, event1:2, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150007 for event: map:0, event1:2, event2:4 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150008 for event: map:0, event1:3, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150009 for event: map:0, event1:3, event2:4 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150384 for event: map:0, event1:4, event2:1 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150010 for event: map:0, event1:4, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150391 for event: map:0, event1:4, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150011 for event: map:0, event1:4, event2:4 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150385 for event: map:0, event1:5, event2:1 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150392 for event: map:0, event1:5, event2:3 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150386 for event: map:0, event1:6, event2:1 ("(null)")
-- BattleGroundEvent: creature with nonexistent guid 150393 for event: map:0, event1:6, event2:3 ("(null)")
DELETE FROM `creature_battleground` WHERE `guid` IN (
    150380, 150002, 150387, 150003, 150381, 150004, 150388, 150005, 150000,
    150001, 150382, 150006, 150389, 150007, 150008, 150009, 150384, 150010,
    150391, 150011, 150385, 150392, 150386, 150393
);

-- Remove binding from items
UPDATE `item_template` SET `bonding` = 0;
