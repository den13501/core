SET
@Entry = 190010,
@Name = "Magister Stellaria";
DELETE FROM `creature_template` WHERE `entry` = 190010;

INSERT INTO `creature_template` (`entry`, `patch`, `display_id1`, `display_id2`, `display_id3`, `display_id4`, `display_scale1`, `display_scale2`, `display_scale3`, `display_scale4`, `display_probability1`, `display_probability2`, `display_probability3`, `display_probability4`, `display_total_probability`, `mount_display_id`, `name`, `subname`, `gossip_menu_id`, `level_min`, `level_max`, `faction`, `npc_flags`, `speed_walk`, `speed_run`, `detection_range`, `call_for_help_range`, `leash_range`, `rank`, `xp_multiplier`, `health_multiplier`, `mana_multiplier`, `armor_multiplier`, `damage_multiplier`, `damage_variance`, `damage_school`, `base_attack_time`, `ranged_attack_time`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `unit_class`, `unit_flags`, `pet_family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `loot_id`, `pickpocket_loot_id`, `skinning_loot_id`, `gold_min`, `gold_max`, `spell_id1`, `spell_id2`, `spell_id3`, `spell_id4`, `spell_list_id`, `pet_spell_list_id`, `spawn_spell_id`, `auras`, `ai_name`, `movement_type`, `inhabit_type`, `civilian`, `racial_leader`, `regeneration`, `equipment_id`, `trainer_id`, `vendor_id`, `mechanic_immune_mask`, `school_immune_mask`, `flags_extra`, `script_name`) VALUES 
(@Entry, 0, 2240, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, @Name, "Transmogrifier", 0, 60, 60, 35, 1, 1, 1.14286, 18, 5, 0, 0, 1, 1, 1, 1, 1.3, 0.14, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 138936390, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 'npc_transmogrifier');


SET @TEXT_ID := 601083;
DELETE FROM `npc_text` WHERE `ID` BETWEEN @TEXT_ID AND @TEXT_ID+5;
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`) VALUES
(@TEXT_ID, @TEXT_ID),
(@TEXT_ID+1, @TEXT_ID+1),
(@TEXT_ID+2, @TEXT_ID+2),
(@TEXT_ID+3, @TEXT_ID+3),
(@TEXT_ID+4, @TEXT_ID+4),
(@TEXT_ID+5, @TEXT_ID+5);

DELETE FROM `broadcast_text` WHERE `entry` BETWEEN @TEXT_ID AND @TEXT_ID+5;
INSERT INTO `broadcast_text` (`entry`, `male_text`, `female_text`) VALUES
(@TEXT_ID, 'Transmogrification allows you to change how your items look like without changing the stats of the items.\r\nItems used in transmogrification are no longer refundable, tradeable and are bound to you.\r\n\r\nNot everything can be transmogrified with eachother.\r\nRestrictions include but are not limited to:\r\nOnly armor and weapons can be transmogrified\r\nGuns, bows and crossbows can be transmogrified with eachother\r\nFishing poles can not be transmogrified\r\nYou must be able to equip both items used in the process.\r\n\r\nTransmogrifications stay on your items as long as you own them.\r\nIf you try to put the item in guild bank or mail it to someone else, the transmogrification is stripped.\r\n\r\nYou can also remove transmogrifications for free at the transmogrifier.', 'Transmogrification allows you to change how your items look like without changing the stats of the items.\r\nItems used in transmogrification are no longer refundable, tradeable and are bound to you.\r\n\r\nNot everything can be transmogrified with eachother.\r\nRestrictions include but are not limited to:\r\nOnly armor and weapons can be transmogrified\r\nGuns, bows and crossbows can be transmogrified with eachother\r\nFishing poles can not be transmogrified\r\nYou must be able to equip both items used in the process.\r\n\r\nTransmogrifications stay on your items as long as you own them.\r\nIf you try to put the item in guild bank or mail it to someone else, the transmogrification is stripped.\r\n\r\nYou can also remove transmogrifications for free at the transmogrifier.'),
(@TEXT_ID+1, 'You can save your own transmogrification sets.\r\n\r\nTo save, first you must transmogrify your equipped items.\r\nThen when you go to the set management menu and go to save set menu,\r\nall items you have transmogrified are displayed so you see what you are saving.\r\nIf you think the set is fine, you can click to save the set and name it as you wish.\r\n\r\nTo use a set you can click the saved set in the set management menu and then select use set.\r\nIf the set has a transmogrification for an item that is already transmogrified, the old transmogrification is lost.\r\nNote that same transmogrification restrictions apply when trying to use a set as in normal transmogrification.\r\n\r\nTo delete a set you can go to the set\'s menu and select delete set.', 'You can save your own transmogrification sets.\r\n\r\nTo save, first you must transmogrify your equipped items.\r\nThen when you go to the set management menu and go to save set menu,\r\nall items you have transmogrified are displayed so you see what you are saving.\r\nIf you think the set is fine, you can click to save the set and name it as you wish.\r\n\r\nTo use a set you can click the saved set in the set management menu and then select use set.\r\nIf the set has a transmogrification for an item that is already transmogrified, the old transmogrification is lost.\r\nNote that same transmogrification restrictions apply when trying to use a set as in normal transmogrification.\r\n\r\nTo delete a set you can go to the set\'s menu and select delete set.'),
(@TEXT_ID+2, 'Select desired look for this slot.', 'Select desired look for this slot.'),
(@TEXT_ID+3, 'Check price and click Confirm to change item look!', 'Check price and click Confirm to change item look!'),
(@TEXT_ID+4, 'This item is already transmogrified.\r\nClick Remove to restore original look!', 'This item is already transmogrified.\r\nClick Remove to restore original look!'),
(@TEXT_ID+5, 'This item is already transmogrified.\r\nClick Remove to restore original look,\r\n\or select a different one!', 'This item is already transmogrified.\r\nClick Remove to restore original look,\r\n\or select a different one!');

SET @STRING_ENTRY := 11100;
DELETE FROM `mangos_string` WHERE `entry` BETWEEN  @STRING_ENTRY+0 AND @STRING_ENTRY+29;
INSERT INTO `mangos_string` (`entry`, `content_default`) VALUES
(@STRING_ENTRY+0, 'Item successfully transmogrified.'),
(@STRING_ENTRY+1, 'Equipment slot is empty.'),
(@STRING_ENTRY+2, 'Invalid source item selected.'),
(@STRING_ENTRY+3, 'Source item does not exist.'),
(@STRING_ENTRY+4, 'Destination item does not exist.'),
(@STRING_ENTRY+5, 'Selected items are invalid.'),
(@STRING_ENTRY+6, 'You don''t have  enough money.'),
(@STRING_ENTRY+7, 'You don''t have enough tokens.'),
(@STRING_ENTRY+8, 'Destination item already has this transmogrification.'),
(@STRING_ENTRY+9, 'All your transmogrifications were removed.'),
(@STRING_ENTRY+10, 'Item transmogrifications were removed.'),
(@STRING_ENTRY+11, 'No transmogrification found.'),
(@STRING_ENTRY+12, 'No transmogrification found on this item.'),
(@STRING_ENTRY+13, 'Invalid name inserted.'),
(@STRING_ENTRY+14, 'Showing transmogrifieded items, relog to update the current area.'),
(@STRING_ENTRY+15, 'Hiding transmogrifieded items, relog to update the current area.'),
(@STRING_ENTRY+16, 'The selected Item is not suitable for transmogrification.'),
(@STRING_ENTRY+17, 'The selected Item cannot be used for transmogrification of the target player.'),
(@STRING_ENTRY+18, 'You have no suitable items in your inventory.'),
(@STRING_ENTRY+19, 'Remove: '),
(@STRING_ENTRY+20, '< [Back]'),
(@STRING_ENTRY+21, '< [Main Menu]'),
(@STRING_ENTRY+22, 'Before: '), 
(@STRING_ENTRY+23, 'After:'),
(@STRING_ENTRY+24, 'Cost is '),
(@STRING_ENTRY+25, 'Confirm'),
(@STRING_ENTRY+26, 'Your item: '),
(@STRING_ENTRY+27, 'Transmog: '),
(@STRING_ENTRY+28, 'Possible transmogrifications:'),
(@STRING_ENTRY+29, 'Options:');

DELETE FROM `command` WHERE `name` IN ('transmog', 'transmog add', 'transmog add set');
INSERT INTO `command` (`name`, `security`, `help`) VALUES
('transmog', 0, 'Syntax: .transmog <on/off>\nAllows seeing transmogrified items and the transmogrifier NPC.'),
('transmog add', 1, 'Syntax: .transmog add $player $item\nAdds an item to a player\'s appearance collection.'),
('transmog add set', 1, 'Syntax: .transmog add set $player $itemSet\nAdds items of an ItemSet to a player\'s appearance collection.');

/* Localize */
DELETE FROM `locales_creature` WHERE `entry`=190010;
INSERT INTO `locales_creature` (`entry`, `name_loc1`, `name_loc2`, `name_loc3`, `name_loc4`, `name_loc5`, `name_loc6`, `name_loc7`, `name_loc8`, `subname_loc1`, `subname_loc2`, `subname_loc3`, `subname_loc4`, `subname_loc5`, `subname_loc6`, `subname_loc7`, `subname_loc8`) VALUES (190010, '', '', '', '史黛菈', '史黛菈', '', '', '', NULL, NULL, NULL, '幻化師', '塑形師', NULL, NULL, NULL);


DELETE FROM `locales_broadcast_text` WHERE `entry`=601083;
INSERT INTO `locales_broadcast_text` (`entry`, `male_text_loc1`, `male_text_loc2`, `male_text_loc3`, `male_text_loc4`, `male_text_loc5`, `male_text_loc6`, `male_text_loc7`, `male_text_loc8`, `female_text_loc1`, `female_text_loc2`, `female_text_loc3`, `female_text_loc4`, `female_text_loc5`, `female_text_loc6`, `female_text_loc7`, `female_text_loc8`) VALUES (601083, NULL, NULL, NULL, '塑型允許你在不改變物品屬性的情況下改變你的物品外觀。$r$n塑型中使用的物品不再可退款、可交易並且與你綁定。$r$n$r$n並非所有東西都可以用$r$n限制包括但不限於：$r$n只有盔甲和武器可以塑型$r$n槍、弓和弩可以互相塑型$r$n釣魚竿不能塑型$r$n你必須能夠裝備在此過程中使用的兩個物品。$r$n$r$n只要你擁有它們，塑型就會留在你的物品上。$r$n如果你嘗試將物品郵寄給其他人，塑型將被解除。$r$n$r$n你也可以在塑型器上免費移除塑型。\', \'塑型允許你在不改變物品屬性的情況下改變你的物品的外觀。$r$n使用的物品塑型不再可退款、可交易且與你綁定。$r$n$r$n不是前夕rything 可以互相變形。$r$n限制包括但不限於：$r$n只有盔甲和武器可以變形$r$n槍、弓和弩可以互相變形$r$n魚竿不能變形$r$n你必須能夠裝備在這個過程中使用的兩個物品。$r$n$r$n只要你擁有它們，塑型就會留在你的物品上。$r$n如果你嘗試將物品放入公會銀行或郵件中給別人，其塑型會被移除。$r$n$r$n你也可以在塑型器免費移除塑型。', '塑型允許你在不改變物品屬性的情況下改變你的物品外觀。$r$n塑型中使用的物品不再可退款、可交易並且與你綁定。$r$n$r$n並非所有東西都可以用$r$n限制包括但不限於：$r$n只有盔甲和武器可以塑型$r$n槍、弓和弩可以互相塑型$r$n釣魚竿不能塑型$r$n你必須能夠裝備在此過程中使用的兩個物品。$r$n$r$n只要你擁有它們，塑型就會留在你的物品上。$r$n如果你嘗試將物品郵寄給其他人，塑型將被解除。$r$n$r$n你也可以在塑型器上免費移除塑型。\', \'塑型允許你在不改變物品屬性的情況下改變你的物品的外觀。$r$n使用的物品塑型不再可退款、可交易且與你綁定。$r$n$r$n不是前夕rything 可以互相變形。$r$n限制包括但不限於：$r$n只有盔甲和武器可以變形$r$n槍、弓和弩可以互相變形$r$n魚竿不能變形$r$n你必須能夠裝備在這個過程中使用的兩個物品。$r$n$r$n只要你擁有它們，塑型就會留在你的物品上。$r$n如果你嘗試將物品放入公會銀行或郵件中給別人，其塑型會被移除。$r$n$r$n你也可以在塑型器免費移除塑型。', NULL, NULL, NULL, NULL, NULL, NULL, '塑型允許你在不改變物品屬性的情況下改變你的物品外觀。$r$n塑型中使用的物品不再可退款、可交易並且與你綁定。$r$n$r$n並非所有東西都可以用$r$n限制包括但不限於：$r$n只有盔甲和武器可以塑型$r$n槍、弓和弩可以互相塑型$r$n釣魚竿不能塑型$r$n你必須能夠裝備在此過程中使用的兩個物品。$r$n$r$n只要你擁有它們，塑型就會留在你的物品上。$r$n如果你嘗試將物品郵寄給其他人，塑型將被解除。$r$n$r$n你也可以在塑型器上免費移除塑型。\', \'塑型允許你在不改變物品屬性的情況下改變你的物品的外觀。$r$n使用的物品塑型不再可退款、可交易且與你綁定。$r$n$r$n不是前夕rything 可以互相變形。$r$n限制包括但不限於：$r$n只有盔甲和武器可以變形$r$n槍、弓和弩可以互相變形$r$n魚竿不能變形$r$n你必須能夠裝備在這個過程中使用的兩個物品。$r$n$r$n只要你擁有它們，塑型就會留在你的物品上。$r$n如果你嘗試將物品放入公會銀行或郵件中給別人，其塑型會被移除。$r$n$r$n你也可以在塑型器免費移除塑型。', '塑型允許你在不改變物品屬性的情況下改變你的物品外觀。$r$n塑型中使用的物品不再可退款、可交易並且與你綁定。$r$n$r$n並非所有東西都可以用$r$n限制包括但不限於：$r$n只有盔甲和武器可以塑型$r$n槍、弓和弩可以互相塑型$r$n釣魚竿不能塑型$r$n你必須能夠裝備在此過程中使用的兩個物品。$r$n$r$n只要你擁有它們，塑型就會留在你的物品上。$r$n如果你嘗試將物品郵寄給其他人，塑型將被解除。$r$n$r$n你也可以在塑型器上免費移除塑型。\', \'塑型允許你在不改變物品屬性的情況下改變你的物品的外觀。$r$n使用的物品塑型不再可退款、可交易且與你綁定。$r$n$r$n不是前夕rything 可以互相變形。$r$n限制包括但不限於：$r$n只有盔甲和武器可以變形$r$n槍、弓和弩可以互相變形$r$n魚竿不能變形$r$n你必須能夠裝備在這個過程中使用的兩個物品。$r$n$r$n只要你擁有它們，塑型就會留在你的物品上。$r$n如果你嘗試將物品放入公會銀行或郵件中給別人，其塑型會被移除。$r$n$r$n你也可以在塑型器免費移除塑型。', NULL, NULL, NULL);
DELETE FROM `locales_broadcast_text` WHERE `entry`=601084;
INSERT INTO `locales_broadcast_text` (`entry`, `male_text_loc1`, `male_text_loc2`, `male_text_loc3`, `male_text_loc4`, `male_text_loc5`, `male_text_loc6`, `male_text_loc7`, `male_text_loc8`, `female_text_loc1`, `female_text_loc2`, `female_text_loc3`, `female_text_loc4`, `female_text_loc5`, `female_text_loc6`, `female_text_loc7`, `female_text_loc8`) VALUES (601084, NULL, NULL, NULL, '你可以保存你自己的塑型組合。$r$n$r$n要保存，首先你必須塑型你裝備的物品。$r$n然後當你進入套裝管理選單和保存套裝選單時，$r$n顯示您塑型的所有項目，以便您查看正在保存的內容。$r$n如果你認為該套裝沒問題，你可以單擊保存該套裝並隨意命名。$r$n$r$n要使用你的套裝可以在套裝管理菜單中點擊已保存的套裝，然後選擇使用套裝。$r$n如果該套裝有一個已經塑型過的物品的塑型，舊的塑型將遺失。$r$n請注意，嘗試時同樣的塑型限制像在普通塑型中一樣使用一個集合。$r$n$r$n要刪除一個集合，你可以進入集合菜單並選擇刪除組合。', '你可以保存你自己的塑型組合。$r$n$r$n要保存，首先你必須塑型你裝備的物品。$r$n然後當你進入套裝管理選單和保存套裝選單時，$r$n顯示您塑型的所有項目，以便您查看正在保存的內容。$r$n如果你認為該套裝沒問題，你可以單擊保存該套裝並隨意命名。$r$n$r$n要使用你的套裝可以在套裝管理菜單中點擊已保存的套裝，然後選擇使用套裝。$r$n如果該套裝有一個已經塑型過的物品的塑型，舊的塑型將遺失。$r$n請注意，嘗試時同樣的塑型限制像在普通塑型中一樣使用一個集合。$r$n$r$n要刪除一個集合，你可以進入集合菜單並選擇刪除組合。', NULL, NULL, NULL, NULL, NULL, NULL, '你可以保存你自己的塑型組合。$r$n$r$n要保存，首先你必須塑型你裝備的物品。$r$n然後當你進入套裝管理選單和保存套裝選單時，$r$n顯示您塑型的所有項目，以便您查看正在保存的內容。$r$n如果你認為該套裝沒問題，你可以單擊保存該套裝並隨意命名。$r$n$r$n要使用你的套裝可以在套裝管理菜單中點擊已保存的套裝，然後選擇使用套裝。$r$n如果該套裝有一個已經塑型過的物品的塑型，舊的塑型將遺失。$r$n請注意，嘗試時同樣的塑型限制像在普通塑型中一樣使用一個集合。$r$n$r$n要刪除一個集合，你可以進入集合菜單並選擇刪除組合。', '你可以保存你自己的塑型組合。$r$n$r$n要保存，首先你必須塑型你裝備的物品。$r$n然後當你進入套裝管理選單和保存套裝選單時，$r$n顯示您塑型的所有項目，以便您查看正在保存的內容。$r$n如果你認為該套裝沒問題，你可以單擊保存該套裝並隨意命名。$r$n$r$n要使用你的套裝可以在套裝管理菜單中點擊已保存的套裝，然後選擇使用套裝。$r$n如果該套裝有一個已經塑型過的物品的塑型，舊的塑型將遺失。$r$n請注意，嘗試時同樣的塑型限制像在普通塑型中一樣使用一個集合。$r$n$r$n要刪除一個集合，你可以進入集合菜單並選擇刪除組合。', NULL, NULL, NULL);
DELETE FROM `locales_broadcast_text` WHERE `entry`=601085;
INSERT INTO `locales_broadcast_text` (`entry`, `male_text_loc1`, `male_text_loc2`, `male_text_loc3`, `male_text_loc4`, `male_text_loc5`, `male_text_loc6`, `male_text_loc7`, `male_text_loc8`, `female_text_loc1`, `female_text_loc2`, `female_text_loc3`, `female_text_loc4`, `female_text_loc5`, `female_text_loc6`, `female_text_loc7`, `female_text_loc8`) VALUES (601085, NULL, NULL, NULL, '選擇此部位想要塑造的外型。', '選擇此部位想要塑造的外型。', NULL, NULL, NULL, NULL, NULL, NULL, '選擇此部位想要塑造的外型。', '選擇此部位想要塑造的外型。', NULL, NULL, NULL);
DELETE FROM `locales_broadcast_text` WHERE `entry`=601086;
INSERT INTO `locales_broadcast_text` (`entry`, `male_text_loc1`, `male_text_loc2`, `male_text_loc3`, `male_text_loc4`, `male_text_loc5`, `male_text_loc6`, `male_text_loc7`, `male_text_loc8`, `female_text_loc1`, `female_text_loc2`, `female_text_loc3`, `female_text_loc4`, `female_text_loc5`, `female_text_loc6`, `female_text_loc7`, `female_text_loc8`) VALUES (601086, NULL, NULL, NULL, '查看價格並點擊確認變更物品外型！', '查看價格並點擊確認變更物品外型！', NULL, NULL, NULL, NULL, NULL, NULL, '查看價格並點擊確認變更物品外型！', '查看價格並點擊確認變更物品外型！', NULL, NULL, NULL);
DELETE FROM `locales_broadcast_text` WHERE `entry`=601087;
INSERT INTO `locales_broadcast_text` (`entry`, `male_text_loc1`, `male_text_loc2`, `male_text_loc3`, `male_text_loc4`, `male_text_loc5`, `male_text_loc6`, `male_text_loc7`, `male_text_loc8`, `female_text_loc1`, `female_text_loc2`, `female_text_loc3`, `female_text_loc4`, `female_text_loc5`, `female_text_loc6`, `female_text_loc7`, `female_text_loc8`) VALUES (601087, NULL, NULL, NULL, '此物品已塑型。$r$n點擊移除恢復原貌！', '此物品已塑型。$r$n點擊移除恢復原貌！', NULL, NULL, NULL, NULL, NULL, NULL, '此物品已塑型。$r$n點擊移除恢復原貌！', '此物品已塑型。$r$n點擊移除恢復原貌！', NULL, NULL, NULL);
DELETE FROM `locales_broadcast_text` WHERE `entry`=601088;
INSERT INTO `locales_broadcast_text` (`entry`, `male_text_loc1`, `male_text_loc2`, `male_text_loc3`, `male_text_loc4`, `male_text_loc5`, `male_text_loc6`, `male_text_loc7`, `male_text_loc8`, `female_text_loc1`, `female_text_loc2`, `female_text_loc3`, `female_text_loc4`, `female_text_loc5`, `female_text_loc6`, `female_text_loc7`, `female_text_loc8`) VALUES (601088, NULL, NULL, NULL, '此物品已塑型。$r$n點選刪除可恢復原本外型，$r$n或選擇別的！', '此物品已塑型。$r$n點選刪除可恢復原本外型，$r$n或選擇別的！', NULL, NULL, NULL, NULL, NULL, NULL, '此物品已塑型。$r$n點選刪除可恢復原本外型，$r$n或選擇別的！', '此物品已塑型。$r$n點選刪除可恢復原本外型，$r$n或選擇別的！', NULL, NULL, NULL);


DELETE FROM `mangos_string` WHERE `entry`=11100;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11100, 'Item successfully transmogrified.', NULL, NULL, NULL, '物品塑形完成。', '物品塑形完成。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11101;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11101, 'Equipment slot is empty.', NULL, NULL, NULL, '該部位是空的。', '該部位是空的。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11102;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11102, 'Invalid source item selected.', NULL, NULL, NULL, '你選了不符的來源物品。', '你選了不符的來源物品。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11103;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11103, 'Source item does not exist.', NULL, NULL, NULL, '來源物品不存在。', '來源物品不存在。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11104;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11104, 'Destination item does not exist.', NULL, NULL, NULL, '目的物品不存在。', '目的物品不存在。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11105;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11105, 'Selected items are invalid.', NULL, NULL, NULL, '選擇的物品不符。', '選擇的物品不符。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11106;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11106, 'You don\'t have  enough money.', NULL, NULL, NULL, '你身上的錢不夠付。', '你身上的錢不夠付。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11107;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11107, 'You don\'t have enough tokens.', NULL, NULL, NULL, '你沒有足夠的代幣。', '你沒有足夠的代幣。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11108;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11108, 'Destination item already has this transmogrification.', NULL, NULL, NULL, '目的物品已有此幻化', '目的物品已有此塑型', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11109;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11109, 'All your transmogrifications were removed.', NULL, NULL, NULL, '你所有的塑形已被移除，', '你所有的塑形已被移除，', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11110;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11110, 'Item transmogrifications were removed.', NULL, NULL, NULL, '物品塑型已被移除。', '物品塑型已被移除。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11111;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11111, 'No transmogrification found.', NULL, NULL, NULL, '找不到幻化。', '找不到塑型。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11112;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11112, 'No transmogrification found on this item.', NULL, NULL, NULL, '此物品無幻化。', '此物品未發現塑型。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11113;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11113, 'Invalid name inserted.', NULL, NULL, NULL, '不正確的名稱。', '不正確的名稱。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11114;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11114, 'Showing transmogrifieded items, relog to update the current area.', NULL, NULL, NULL, '顯示被幻化的物品，重新登入以更新顯示部位。', '顯示被塑型的物品，重新登入以更新顯示部位。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11115;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11115, 'Hiding transmogrifieded items, relog to update the current area.', NULL, NULL, NULL, '隱藏幻化物品，重新登入以更新顯示部位。', '隱藏塑型物品，重新登入以更新顯示部位。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11116;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11116, 'The selected Item is not suitable for transmogrification.', NULL, NULL, NULL, '選中的物品不適合做為幻化。', '選中的物品不適合做為塑型。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11117;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11117, 'The selected Item cannot be used for transmogrification of the target player.', NULL, NULL, NULL, '選中的物品無法作為目標玩家幻化使用，', '選中的物品無法作為目標玩家塑型使用，', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11118;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11118, 'You have no suitable items in your inventory.', NULL, NULL, NULL, '你的背包、銀行沒有適合的物品。', '你的背包、銀行沒有適合的物品。', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11119;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11119, 'Remove: ', NULL, NULL, NULL, '移除：', '移除：', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11120;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11120, '< [Back]', NULL, NULL, NULL, '< [上一頁]', '< [上一頁]', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11121;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11121, '< [Main Menu]', NULL, NULL, NULL, '< [首頁]', '< [首頁]', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11122;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11122, 'Before: ', NULL, NULL, NULL, '變更前：', '變更前：', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11123;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11123, 'After:', NULL, NULL, NULL, '變更後：', '變更後：', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11124;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11124, 'Cost is ', NULL, NULL, NULL, '收費', '收費', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11125;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11125, 'Confirm', NULL, NULL, NULL, '確認', '確認', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11126;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11126, 'Your item: ', NULL, NULL, NULL, '你的物品：', '你的物品：', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11127;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11127, 'Transmog: ', NULL, NULL, NULL, '塑形：', '塑形：', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11128;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11128, 'Possible transmogrifications:', NULL, NULL, NULL, '可用來塑型的物品：', '可用來塑型的物品：', NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=11129;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11129, 'Options:', NULL, NULL, NULL, '選項：', '選項：', NULL, NULL, NULL);
