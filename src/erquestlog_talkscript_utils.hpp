/**
 * erquestlog_talkscript_utils.hpp
 *
 * Repetitive/tedious data structure setup for modded talkscript states used by
 * erquestlog_talkscript.cpp.
 */
#include <array>
#include <cstdint>

#include "from/ezstate.hpp"
#include "from/talk_commands.hpp"

#include "erquestlog_messages.hpp"

namespace
{

typedef std::array<unsigned char, 6> int_value_data;

/**
 * Create an ESD expression representing a 4 byte integer
 */
constexpr int_value_data make_int_value(int value)
{
    return {
        0x82,
        static_cast<unsigned char>((value & 0x000000ff)),
        static_cast<unsigned char>((value & 0x0000ff00) >> 8),
        static_cast<unsigned char>((value & 0x00ff0000) >> 16),
        static_cast<unsigned char>((value & 0xff000000) >> 24),
        0xa1,
    };
}

/**
 * Parse an ESD expression containing only a 1 or 4 byte integer
 */
int get_int_value(from::EzState::arg &arg)
{
    // Single byte (plus final 0xa1) - used to store integers from -64 to 63
    if (arg.size() == 2)
    {
        return arg[0] - 64;
    }

    // Five bytes (plus final 0xa1) - used to store larger integers
    if (arg.size() == 6 && arg[0] == 0x82)
    {
        return *reinterpret_cast<int *>(&arg[1]);
    }

    return -1;
}

/**
 * Generates a ListEntryResult string
 */
template<int Value>
struct TalkListEntryEvaluator {
    static constexpr std::array<unsigned char, 9> value = {
        0x57, 0x84, 0x82,
        static_cast<unsigned char>(Value & 0xFF),
        static_cast<unsigned char>((Value >> 8) & 0xFF),
        static_cast<unsigned char>((Value >> 16) & 0xFF),
        static_cast<unsigned char>((Value >> 24) & 0xFF),
        0x95, 0xA1
    };
};

template<int Value>
constexpr auto generate_talk_list_entry_evaluator_v = TalkListEntryEvaluator<Value>::value;

extern from::EzState::state open_quests_state;
extern from::EzState::state open_quests_successor_state;

#define ADD_TALK_LIST_DATA_ARGS(name, index, message_id)                                           \
    int_value_data name##_index_value = make_int_value(index);                                     \
    int_value_data name##_message_id_value = make_int_value(message_id);                           \
    int_value_data name##_unk_value = make_int_value(-1);                                          \
    std::array<from::EzState::arg, 3> name##_args = {name##_index_value, name##_message_id_value,  \
                                                     name##_unk_value}

/*#define OPEN_GENERIC_DIALOG(name)                                                                \
    from::EzState::event(from::talk_command::open_generic_dialog, name##_unlock_args);*/


//events definition
ADD_TALK_LIST_DATA_ARGS(open_quests, 91, erquestlog::event_text_for_talk::questlog);

ADD_TALK_LIST_DATA_ARGS(irina, 3, erquestlog::event_text_for_talk::irina_head);
ADD_TALK_LIST_DATA_ARGS(leave, 99, erquestlog::event_text_for_talk::leave);


//evaluators definition
static constexpr auto evaluator_91 = generate_talk_list_entry_evaluator_v<91>;
static constexpr auto evaluator_92 = generate_talk_list_entry_evaluator_v<92>;


static constexpr char open_quests_evaluator[] =
    "\x57\x84\x82\x5b\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 91

static constexpr char irina_head_evaluator[] =
    "\x57\x84\x82\x03\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 03

static constexpr char else_evaluator[] = "\x41\xa1";

constexpr char talk_menu_closed_evaluator[] =
    // CheckSpecificPersonMenuIsOpen(1, 0) == 1
    "\x7b"
    "\x82\x01\x00\x00\x00"
    "\x82\x00\x00\x00\x00"
    "\x86"
    "\x82\x01\x00\x00\x00"
    "\x95"
    // CheckSpecificPersonGenericDialogIsOpen(0) == 0
    "\x7a"
    "\x82\x00\x00\x00\x00"
    "\x85"
    "\x82\x00\x00\x00\x00"
    "\x95"
    // &&
    "\x98"
    // == 0
    "\x82\x00\x00\x00\x00"
    "\x95"
    "\xa1";

constexpr char menu_closed_evaluator[] =
    // CheckSpecificPersonMenuIsOpen(5, 0) == 1
    "\x7b"
    "\x82\x05\x00\x00\x00"
    "\x82\x00\x00\x00\x00"
    "\x86"
    "\x82\x01\x00\x00\x00"
    "\x95"
    // CheckSpecificPersonGenericDialogIsOpen(0) == 0
    "\x7a"
    "\x82\x00\x00\x00\x00"
    "\x85"
    "\x82\x00\x00\x00\x00"
    "\x95"
    // &&
    "\x98"
    // == 0
    "\x82\x00\x00\x00\x00"
    "\x95"
    "\xa1";


from::EzState::transition irina_h_transition(nullptr, open_quests_evaluator);
from::EzState::transition main_menu_return_transition(nullptr, else_evaluator);

//OPEN_GENERIC_DIALOG(82000000);  //????????????



//creation of main event
static int_value_data quest_log_index_value = make_int_value(91);
static int_value_data quest_log_message_id_value = make_int_value(82000000);
static int_value_data quest_log_unk_value = make_int_value(-1);
static std::array<from::EzState::arg, 3> quest_log_args = {
    quest_log_index_value,
    quest_log_message_id_value,
    quest_log_unk_value,
};

static from::EzState::event quest_log_event{from::talk_command::add_talk_list_data, quest_log_args};
static from::EzState::transition quest_log_transition(&open_quests_state, open_quests_evaluator);
//static from::EzState::transition quest_log_transition(&open_quests_state, evaluator_91);


//irina quest tree
static int_value_data irina_h_index_value = make_int_value(3);
static int_value_data irina_h_message_id_value = make_int_value(82010000);
static int_value_data irina_h_unk_value = make_int_value(-1);
static std::array<from::EzState::arg, 3> irina_h_args = {
    irina_h_index_value,
    irina_h_message_id_value,
    irina_h_unk_value,
};


std::array<from::EzState::event, 2> open_quests_events = {
    from::EzState::event{from::talk_command::add_talk_list_data, irina_h_args},
    from::EzState::event{from::talk_command::add_talk_list_data, leave_args},
};

from::EzState::transition open_quests_next_transition(&open_quests_state,
                                                           talk_menu_closed_evaluator);
std::array<from::EzState::transition *, 1> open_quests_transitions = {
    &open_quests_next_transition};
from::EzState::state open_quests_state = {
    .id = 5000,
    .transitions = open_quests_transitions,
    .entry_events = open_quests_events,
};
/*std::array<from::EzState::transition *,1> questlog_successor_transitions = {
    &irina_h_transition, 
};

std::array<from::EzState::transition *, 7> open_quests_successor_transitions = {
    &irina_h_transition, 
    &main_menu_return_transition,
};*/


/**
 * Main menu
 */
from::EzState::transition open_quests_transition(&open_quests_state,
                                                      open_quests_evaluator);

#undef ADD_TALK_LIST_DATA_ARGS

};
