#include "erquestlog_messages.hpp"

#include <map>
#include <string>

const std::map<std::string, std::map<int, const std::wstring>>
    erquestlog::event_text_for_talk_by_lang = {
        {"english",
         {
             {erquestlog::event_text_for_talk::questlog, L"Ongoing Quests"},
             
             {erquestlog::event_text_for_talk::irina_head, L"Irina's Quest"},
             {erquestlog::event_text_for_talk::irina_01_h, L"Delivery to Castle Morne"},
             {erquestlog::event_text_for_talk::irina_01_t, L"You accepted to deliver a \"letter\" from Irina to her father in Castle Morne."},
         }},
};
