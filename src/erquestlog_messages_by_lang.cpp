#include "erquestlog_messages.hpp"

#include <map>
#include <string>

const std::map<std::string, std::map<int, const std::wstring>>
    erquestlog::event_text_for_talk_by_lang = {
        {"english",
         {
             {erquestlog::event_text_for_talk::weapons, L"Weapons"},
             {erquestlog::event_text_for_talk::armor, L"Armor"},
             {erquestlog::event_text_for_talk::spells, L"Sorceries/Incantations"},
             {erquestlog::event_text_for_talk::talismans, L"Talismans"},
             {erquestlog::event_text_for_talk::ammunition, L"Arrows/Bolts"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"Ashes of War"},
             {erquestlog::event_text_for_talk::consumables, L"Consumables"},
             {erquestlog::event_text_for_talk::spirit_summons, L"Spirit Ashes"},
             {erquestlog::event_text_for_talk::materials, L"Materials"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"Gestures"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Browse Inventory"},
             {erquestlog::event_text_for_talk::items, L"Items"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"Browse Cut Content"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},

             {erquestlog::event_text_for_talk::quest_log, L"Ongoing Quests"},
             
             {erquestlog::event_text_for_talk::irina_head, L"Irina's Quest"},
             {erquestlog::event_text_for_talk::irina_01_h, L"Delivery to Castle Morne"},
             {erquestlog::event_text_for_talk::irina_01_t, L"You accepted to deliver a \"letter\" from Irina to her father in Castle Morne."},
         }},
        {"german",
         {
             {erquestlog::event_text_for_talk::weapons, L"Waffen"},
             {erquestlog::event_text_for_talk::armor, L"Rüstung"},
             {erquestlog::event_text_for_talk::spells, L"Zaubereien/Anrufungen"},
             {erquestlog::event_text_for_talk::talismans, L"Talismane"},
             {erquestlog::event_text_for_talk::ammunition, L"Pfeile/Bolzen"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"Kriegsasche"},
             {erquestlog::event_text_for_talk::consumables, L"Verbrauchsgüter"},
             {erquestlog::event_text_for_talk::spirit_summons, L"Geisterasche"},
             {erquestlog::event_text_for_talk::materials, L"Materialien"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"Gesten"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Inventar durchsuchen"},
             {erquestlog::event_text_for_talk::items, L"Objekte"},
             {erquestlog::event_text_for_talk::browse_cut_content,
              L"Entfernte Inhalte durchsuchen"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
        {"french",
         {
             {erquestlog::event_text_for_talk::weapons, L"Armes"},
             {erquestlog::event_text_for_talk::armor, L"Armure"},
             {erquestlog::event_text_for_talk::spells, L"Tous les sorts"},
             {erquestlog::event_text_for_talk::talismans, L"Talismans"},
             {erquestlog::event_text_for_talk::ammunition, L"Flèches/Carreaux"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"Cendres de guerre"},
             {erquestlog::event_text_for_talk::consumables, L"Consommables"},
             {erquestlog::event_text_for_talk::spirit_summons, L"Cendres spirituelles"},
             {erquestlog::event_text_for_talk::materials, L"Matériaux"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"Émotes"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Parcourir l'inventaire"},
             {erquestlog::event_text_for_talk::items, L"Objets"},
             {erquestlog::event_text_for_talk::browse_cut_content,
              L"Parcourir le contenu supprimé"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
        {"italian",
         {
             {erquestlog::event_text_for_talk::weapons, L"Armi"},
             {erquestlog::event_text_for_talk::armor, L"Armature"},
             {erquestlog::event_text_for_talk::spells, L"Stregonerie/Incantesimi"},
             {erquestlog::event_text_for_talk::talismans, L"Talismani"},
             {erquestlog::event_text_for_talk::ammunition, L"Frecce/Dardi"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"Ceneri di guerra"},
             {erquestlog::event_text_for_talk::consumables, L"Consumabili"},
             {erquestlog::event_text_for_talk::spirit_summons, L"Ceneri di spirito"},
             {erquestlog::event_text_for_talk::materials, L"Materiali"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"Gesti"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Sfoglia l'inventario"},
             {erquestlog::event_text_for_talk::items, L"Oggetti"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"Sfoglia i contenuti rimossi"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
        // Japanese localization by Furisuke
        {"japanese",
         {
             {erquestlog::event_text_for_talk::weapons, L"武器"},
             {erquestlog::event_text_for_talk::armor, L"防具"},
             {erquestlog::event_text_for_talk::spells, L"魔術/祈祷"},
             {erquestlog::event_text_for_talk::talismans, L"タリスマン"},
             {erquestlog::event_text_for_talk::ammunition, L"矢/ボルト"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"戦灰"},
             {erquestlog::event_text_for_talk::consumables, L"消費アイテム"},
             {erquestlog::event_text_for_talk::spirit_summons, L"遺灰"},
             {erquestlog::event_text_for_talk::materials, L"製作素材"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"その他アイテム"},
             {erquestlog::event_text_for_talk::gestures, L"ジェスチャー"},
             {erquestlog::event_text_for_talk::browse_inventory, L"インベントリを見る"},
             {erquestlog::event_text_for_talk::items, L"アイテム"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"カットコンテンツを見る"},
             {erquestlog::event_text_for_talk::goods, L"アイテム"},
             {erquestlog::event_text_for_talk::unlock, L"解放"},
             {erquestlog::event_text_for_talk::dlc, L"DLCアイテム"},
         }},
        {"koreana",
         {
             {erquestlog::event_text_for_talk::weapons, L"무기"},
             {erquestlog::event_text_for_talk::armor, L"방어구"},
             {erquestlog::event_text_for_talk::spells, L"모든 마술/기도"},
             {erquestlog::event_text_for_talk::talismans, L"탈리스만"},
             {erquestlog::event_text_for_talk::ammunition, L"화살/볼트"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"전회"},
             {erquestlog::event_text_for_talk::consumables, L"소비 아이템"},
             {erquestlog::event_text_for_talk::spirit_summons, L"뼛가루 유무"},
             {erquestlog::event_text_for_talk::materials, L"소재 아이템"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"제스처"},
             {erquestlog::event_text_for_talk::browse_inventory, L"인벤토리 찾아보기"},
             {erquestlog::event_text_for_talk::items, L"아이템"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"컷 콘텐츠 찾아보기"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
        {"polish",
         {
             {erquestlog::event_text_for_talk::weapons, L"Broń"},
             {erquestlog::event_text_for_talk::armor, L"Zbroja"},
             {erquestlog::event_text_for_talk::spells, L"Czary/Inkantacje"},
             {erquestlog::event_text_for_talk::talismans, L"Talizmany"},
             {erquestlog::event_text_for_talk::ammunition, L"Strzały/bełty"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"Popioły wojny"},
             {erquestlog::event_text_for_talk::consumables, L"Przedmioty jednorazowe"},
             {erquestlog::event_text_for_talk::spirit_summons, L"Prochy duchów"},
             {erquestlog::event_text_for_talk::materials, L"Materiały"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"Gesty"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Przeglądaj Ekwipunek"},
             {erquestlog::event_text_for_talk::items, L"Przedmioty"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"Przeglądaj wyciętą zawartość"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
        // Brazilian Portuguese localization by LucasGabranth
        {"brazilian",
         {
             {erquestlog::event_text_for_talk::weapons, L"Armas"},
             {erquestlog::event_text_for_talk::armor, L"Armadura"},
             {erquestlog::event_text_for_talk::spells, L"Feitiços/Encantamentos"},
             {erquestlog::event_text_for_talk::talismans, L"Talismãs"},
             {erquestlog::event_text_for_talk::ammunition, L"Flechas/Setas"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"Cinzas de Guerra"},
             {erquestlog::event_text_for_talk::consumables, L"Consumíveis"},
             {erquestlog::event_text_for_talk::spirit_summons, L"Cinzas de espíritos"},
             {erquestlog::event_text_for_talk::materials, L"Materiais"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Itens variados"},
             {erquestlog::event_text_for_talk::gestures, L"Gestos"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Navegar no inventário"},
             {erquestlog::event_text_for_talk::items, L"Itens"},
             {erquestlog::event_text_for_talk::browse_cut_content,
              L"Navegar pelo conteúdo removido"},
             {erquestlog::event_text_for_talk::goods, L"Mercadorias"},
             {erquestlog::event_text_for_talk::unlock, L"Desbloqueios"},
             {erquestlog::event_text_for_talk::dlc, L"Itens da DLC"},
         }},
        {"russian",
         {
             {erquestlog::event_text_for_talk::weapons, L"Оружие"},
             {erquestlog::event_text_for_talk::armor, L"Доспехи"},
             {erquestlog::event_text_for_talk::spells, L"Чары/молитвы"},
             {erquestlog::event_text_for_talk::talismans, L"Талисманы"},
             {erquestlog::event_text_for_talk::ammunition, L"Стрелы/болты"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"Пепел Войны"},
             {erquestlog::event_text_for_talk::consumables, L"Расход. материалы"},
             {erquestlog::event_text_for_talk::spirit_summons, L"Прах для призыва"},
             {erquestlog::event_text_for_talk::materials, L"Материалы"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"Жесты"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Просмотреть инвентарь"},
             {erquestlog::event_text_for_talk::items, L"Предметы"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"Browse cut content"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
        {"latam",
         {
             {erquestlog::event_text_for_talk::weapons, L"Armas"},
             {erquestlog::event_text_for_talk::armor, L"Armadura"},
             {erquestlog::event_text_for_talk::spells, L"Hechicerías/Encantamientos"},
             {erquestlog::event_text_for_talk::talismans, L"Talismanes"},
             {erquestlog::event_text_for_talk::ammunition, L"Flechas/Virotes"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"Cenizas de guerra"},
             {erquestlog::event_text_for_talk::consumables, L"Consumibles"},
             {erquestlog::event_text_for_talk::spirit_summons, L"Cenizas de espíritus"},
             {erquestlog::event_text_for_talk::materials, L"Materiales"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"Gestos"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Explorar inventario"},
             {erquestlog::event_text_for_talk::items, L"Objetos"},
             {erquestlog::event_text_for_talk::browse_cut_content,
              L"Explorar contenidos eliminados"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
        {"spanish",
         {
             {erquestlog::event_text_for_talk::weapons, L"Armas"},
             {erquestlog::event_text_for_talk::armor, L"Armadura"},
             {erquestlog::event_text_for_talk::spells, L"Hechizos/encantamientos"},
             {erquestlog::event_text_for_talk::talismans, L"Talismanes"},
             {erquestlog::event_text_for_talk::ammunition, L"Flechas/saetas"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"Cenizas de guerra"},
             {erquestlog::event_text_for_talk::consumables, L"Consumibles"},
             {erquestlog::event_text_for_talk::spirit_summons, L"Cenizas de espíritu"},
             {erquestlog::event_text_for_talk::materials, L"Materiales"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"Gestos"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Explorar inventario"},
             {erquestlog::event_text_for_talk::items, L"Objetos"},
             {erquestlog::event_text_for_talk::browse_cut_content,
              L"Explorar contenidos eliminados"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
        {"thai",
         {
             {erquestlog::event_text_for_talk::weapons, L"อาวุธ"},
             {erquestlog::event_text_for_talk::armor,
              L"เครือง​ปองกัน"},
             {erquestlog::event_text_for_talk::spells,
              L"คาถา/​มน​ตรา​ทังหมด"},
             {erquestlog::event_text_for_talk::talismans, L"เครืองราง"},
             {erquestlog::event_text_for_talk::ammunition,
              L"ลูก​ธนู/​ลูกดอก"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"เถ้า​สงคราม"},
             {erquestlog::event_text_for_talk::consumables,
              L"ไอ​เทม​ประเภท​ใช้​แล้ว"
              L"​หมด​ไป"},
             {erquestlog::event_text_for_talk::spirit_summons,
              L"ใช้​ธุลี​หรือ​ไม่"},
             {erquestlog::event_text_for_talk::materials,
              L"ไอ​เท​ม​วัตถุดิบ"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"ท่าทาง"},
             {erquestlog::event_text_for_talk::browse_inventory,
              L"เรียกดู คลัง​ไอ​เทม"},
             {erquestlog::event_text_for_talk::items, L"รายการ"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"Browse Cut Content"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
        // Simplified Chinese localization by quantumfallout
        {"schinese",
         {
             {erquestlog::event_text_for_talk::weapons, L"武器"},
             {erquestlog::event_text_for_talk::armor, L"防具"},
             {erquestlog::event_text_for_talk::spells, L"全部的魔法、祷告"},
             {erquestlog::event_text_for_talk::talismans, L"护符"},
             {erquestlog::event_text_for_talk::ammunition, L"箭／弩箭"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"战灰"},
             {erquestlog::event_text_for_talk::consumables, L"消耗道具"},
             {erquestlog::event_text_for_talk::spirit_summons, L"骨灰"},
             {erquestlog::event_text_for_talk::materials, L"材料道具"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"杂项道具"},
             {erquestlog::event_text_for_talk::gestures, L"肢体动作"},
             {erquestlog::event_text_for_talk::browse_inventory, L"浏览置物包"},
             {erquestlog::event_text_for_talk::items, L"全部道具"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"浏览删减内容"},
             {erquestlog::event_text_for_talk::goods, L"其他物品"},
             {erquestlog::event_text_for_talk::unlock, L"解锁"},
             {erquestlog::event_text_for_talk::dlc, L"DLC道具"},
         }},
        // Traditional Chinese localization by quantumfallout
        {"tchinese",
         {
             {erquestlog::event_text_for_talk::weapons, L"武器"},
             {erquestlog::event_text_for_talk::armor, L"防具"},
             {erquestlog::event_text_for_talk::spells, L"全部的魔法、禱告"},
             {erquestlog::event_text_for_talk::talismans, L"護符"},
             {erquestlog::event_text_for_talk::ammunition, L"箭／弩箭"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"戰灰"},
             {erquestlog::event_text_for_talk::consumables, L"消耗道具"},
             {erquestlog::event_text_for_talk::spirit_summons, L"骨灰"},
             {erquestlog::event_text_for_talk::materials, L"材料道具"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"雜項道具"},
             {erquestlog::event_text_for_talk::gestures, L"肢體動作"},
             {erquestlog::event_text_for_talk::browse_inventory, L"浏览置物包"},
             {erquestlog::event_text_for_talk::items, L"全部道具"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"浏览刪減內容"},
             {erquestlog::event_text_for_talk::goods, L"其他物品"},
             {erquestlog::event_text_for_talk::unlock, L"解鎖"},
             {erquestlog::event_text_for_talk::dlc, L"DLC道具"},
         }},
        {"arabic",
         {
             {erquestlog::event_text_for_talk::weapons, L"اﻷﺳﻠﺣﺔ"},
             {erquestlog::event_text_for_talk::armor, L"اﻟﻭاﻗﻲ"},
             {erquestlog::event_text_for_talk::spells, L"اﻷﺳﺣﺎر/اﻟﺗﻌﺎوﻳﺫ"},
             {erquestlog::event_text_for_talk::talismans, L"اﻟﻁﻼﺳﻡ"},
             {erquestlog::event_text_for_talk::ammunition, L"اﻷﺳﻬﻡ/اﻷﺳﻬﻡ اﻟﺻﻐﻳﺭة"},
             {erquestlog::event_text_for_talk::ashes_of_war, L"رﻣﺎد اﻟﺣﺭب"},
             {erquestlog::event_text_for_talk::consumables, L"اﻟﻣﻭاد اﻟﻘﺎﺑﻠﺔ ﻟﻼﺳﺗﻬﻼك"},
             {erquestlog::event_text_for_talk::spirit_summons, L"رﻣﺎد اﻷرواح"},
             {erquestlog::event_text_for_talk::materials, L"اﻟﻣﻭاد"},
             {erquestlog::event_text_for_talk::miscellaneous_items, L"Miscellaneous Items"},
             {erquestlog::event_text_for_talk::gestures, L"اﻹﻳﻣﺎءات"},
             {erquestlog::event_text_for_talk::browse_inventory, L"Browse Inventory"},
             {erquestlog::event_text_for_talk::items, L"أغراض"},
             {erquestlog::event_text_for_talk::browse_cut_content, L"Browse Cut Content"},
             {erquestlog::event_text_for_talk::goods, L"Goods"},
             {erquestlog::event_text_for_talk::unlock, L"Unlock"},
             {erquestlog::event_text_for_talk::dlc, L"DLC Items"},
         }},
};
