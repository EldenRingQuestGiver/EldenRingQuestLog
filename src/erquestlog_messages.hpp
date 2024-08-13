#pragma once

#include <map>
#include <string>

#include "from/messages.hpp"

namespace erquestlog
{

namespace event_text_for_talk
{
//questlog messages
static constexpr int questlog = 82000000;

static constexpr int irina_head = 82010000;
static constexpr int irina_01_h = 82011000;
static constexpr int irina_01_t = 82011001;

// Existing messages, for searching for particular talkscript states
static constexpr int leave = 20000009;
static constexpr int sortchest = 15000395;
}

void setup_messages();
const std::wstring_view get_message(from::msgbnd, int);

extern const std::map<std::string, std::map<int, const std::wstring>> event_text_for_talk_by_lang;

}
