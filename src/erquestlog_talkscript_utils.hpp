/**
 * erquestlog_talkscript_utils.hpp
 *
 * Repetitive/tedious data structure setup for modded talkscript states used by
 * erquestlog_talkscript.cpp. This sets up a few new states for submenus to open various shops
 * and acquire gestures, which are then patched into Kalé's vanilla menu.
 */
#include <array>

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

int_value_data event_flag_on = make_int_value(0);

int_value_data generic_dialog_shop_message = make_int_value(0);
from::EzState::arg show_generic_dialog_shop_message_arg_list[1] = {
    generic_dialog_shop_message,
};

extern from::EzState::state browse_inventory_state;
extern from::EzState::state browse_inventory_successor_state;

#define ADD_TALK_LIST_DATA_ARGS(name, index, message_id)                                           \
    int_value_data name##_index_value = make_int_value(index);                                     \
    int_value_data name##_message_id_value = make_int_value(message_id);                           \
    int_value_data name##_unk_value = make_int_value(-1);                                          \
    std::array<from::EzState::arg, 3> name##_args = {name##_index_value, name##_message_id_value,  \
                                                     name##_unk_value}

#define OPEN_REGULAR_SHOP_STATE(state_id, name, prev_state, shop_id)                               \
    int_value_data name##_begin_id_value = make_int_value(shop_id);                                \
    int_value_data name##_end_id_value = make_int_value(shop_id + erquestlog::shop_capacity);      \
    std::array<from::EzState::arg, 2> name##_args = {name##_begin_id_value, name##_end_id_value};  \
    std::array<from::EzState::event, 1> name##_events = {                                          \
        from::EzState::event{from::talk_command::open_regular_shop, name##_args},                  \
    };                                                                                             \
    from::EzState::transition name##_transition(prev_state, shop_closed_evaluator);                \
    std::array<from::EzState::transition *, 1> name##_transitions = {                              \
        &name##_transition,                                                                        \
    };                                                                                             \
    from::EzState::state name## = {                                                                \
        .id = state_id,                                                                            \
        .transitions = name##_transitions,                                                         \
        .entry_events = name##_events,                                                             \
    }

ADD_TALK_LIST_DATA_ARGS(browse_inventory, 48, erquestlog::event_text_for_talk::browse_inventory);
ADD_TALK_LIST_DATA_ARGS(browse_cut_content, 49,
                        erquestlog::event_text_for_talk::browse_cut_content);
ADD_TALK_LIST_DATA_ARGS(weapons, 50, erquestlog::event_text_for_talk::weapons);
ADD_TALK_LIST_DATA_ARGS(ammunition, 51, erquestlog::event_text_for_talk::ammunition);
ADD_TALK_LIST_DATA_ARGS(spells, 52, erquestlog::event_text_for_talk::spells);
ADD_TALK_LIST_DATA_ARGS(ashes_of_war, 53, erquestlog::event_text_for_talk::ashes_of_war);
ADD_TALK_LIST_DATA_ARGS(armor, 54, erquestlog::event_text_for_talk::armor);
ADD_TALK_LIST_DATA_ARGS(talismans, 55, erquestlog::event_text_for_talk::talismans);
ADD_TALK_LIST_DATA_ARGS(items, 56, erquestlog::event_text_for_talk::items);
ADD_TALK_LIST_DATA_ARGS(dlc, 57, erquestlog::event_text_for_talk::dlc);
ADD_TALK_LIST_DATA_ARGS(gestures, 58, erquestlog::event_text_for_talk::gestures);
ADD_TALK_LIST_DATA_ARGS(goods, 59, erquestlog::event_text_for_talk::goods);
ADD_TALK_LIST_DATA_ARGS(consumables, 60, erquestlog::event_text_for_talk::consumables);
ADD_TALK_LIST_DATA_ARGS(materials, 61, erquestlog::event_text_for_talk::materials);
ADD_TALK_LIST_DATA_ARGS(spirit_summons, 62, erquestlog::event_text_for_talk::spirit_summons);
ADD_TALK_LIST_DATA_ARGS(miscellaneous_items, 63,
                        erquestlog::event_text_for_talk::miscellaneous_items);
ADD_TALK_LIST_DATA_ARGS(unlock, 64, erquestlog::event_text_for_talk::unlock);
ADD_TALK_LIST_DATA_ARGS(leave, 99, erquestlog::event_text_for_talk::leave);

static constexpr char browse_inventory_evaluator[] =
    "\x57\x84\x82\x30\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 48
static constexpr char browse_cut_content_evaluator[] =
    "\x57\x84\x82\x31\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 49
static constexpr char weapons_evaluator[] =
    "\x57\x84\x82\x32\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 50
static constexpr char ammunition_evaluator[] =
    "\x57\x84\x82\x33\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 51
static constexpr char spells_evaluator[] =
    "\x57\x84\x82\x34\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 52
static constexpr char ashes_of_war_evaluator[] =
    "\x57\x84\x82\x35\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 53
static constexpr char armor_evaluator[] =
    "\x57\x84\x82\x36\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 54
static constexpr char talismans_evaluator[] =
    "\x57\x84\x82\x37\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 55
static constexpr char items_evaluator[] =
    "\x57\x84\x82\x38\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 56
static constexpr char dlc_evaluator[] =
    "\x57\x84\x82\x39\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 57
static constexpr char gestures_evaluator[] =
    "\x57\x84\x82\x3a\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 58
static constexpr char goods_evaluator[] =
    "\x57\x84\x82\x3b\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 59
static constexpr char consumables_evaluator[] =
    "\x57\x84\x82\x3c\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 60
static constexpr char materials_evaluator[] =
    "\x57\x84\x82\x3d\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 61
static constexpr char spirit_summons_evaluator[] =
    "\x57\x84\x82\x3e\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 62
static constexpr char miscellaneous_items_evaluator[] =
    "\x57\x84\x82\x3f\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 63
static constexpr char unlock_evaluator[] =
    "\x57\x84\x82\x40\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 64
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

constexpr char shop_closed_evaluator[] =
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

from::EzState::transition main_menu_return_transition(nullptr, else_evaluator);

/*
 * Shop states
 */
OPEN_REGULAR_SHOP_STATE(5200, weapons_shop_state, &browse_inventory_state,
                        erquestlog::shops::weapons);
OPEN_REGULAR_SHOP_STATE(5201, armor_shop_state, &browse_inventory_state, erquestlog::shops::armor);
OPEN_REGULAR_SHOP_STATE(5202, spells_shop_state, &browse_inventory_state,
                        erquestlog::shops::spells);
OPEN_REGULAR_SHOP_STATE(5203, talismans_shop_state, &browse_inventory_state,
                        erquestlog::shops::talismans);
OPEN_REGULAR_SHOP_STATE(5204, ammunition_shop_state, &browse_inventory_state,
                        erquestlog::shops::ammunition);
OPEN_REGULAR_SHOP_STATE(5205, ashes_of_war_shop_state, &browse_inventory_state,
                        erquestlog::shops::ashes_of_war);


from::EzState::transition weapons_transition(&weapons_shop_state, weapons_evaluator);
from::EzState::transition ammunition_transition(&ammunition_shop_state, ammunition_evaluator);
from::EzState::transition spells_transition(&spells_shop_state, spells_evaluator);
from::EzState::transition ashes_of_war_transition(&ashes_of_war_shop_state, ashes_of_war_evaluator);
from::EzState::transition armor_transition(&armor_shop_state, armor_evaluator);
from::EzState::transition talismans_transition(&talismans_shop_state, talismans_evaluator);






/**
 * Generates a ListEntryResult string
 */

 /*#define OPEN_GENERIC_DIALOG(name)                                                                \
    from::EzState::event(from::talk_command::open_generic_dialog, name##_unlock_args);*/

//OPEN_GENERIC_DIALOG(82000000);  //????????????

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


/*extern from::EzState::state open_quests_state;
extern from::EzState::state open_quests_successor_state;

//events definition
ADD_TALK_LIST_DATA_ARGS(open_quests, 48, erquestlog::event_text_for_talk::questlog);

ADD_TALK_LIST_DATA_ARGS(irina, 3, erquestlog::event_text_for_talk::irina_head);*/


//creation of main event
static int_value_data quest_log_index_value = make_int_value(48);
static int_value_data quest_log_message_id_value = make_int_value(82000000);
static int_value_data quest_log_unk_value = make_int_value(-1);
static std::array<from::EzState::arg, 3> quest_log_args = {
    quest_log_index_value,
    quest_log_message_id_value,
    quest_log_unk_value,
};
static from::EzState::event quest_log{from::talk_command::add_talk_list_data, quest_log_args};

extern from::EzState::state quest_log_state;
extern from::EzState::state quest_log_successor_state;

//ADD_TALK_LIST_DATA_ARGS(quest_log, 48, erquestlog::event_text_for_talk::quest_log);

static constexpr char quest_log_evaluator[] =
    "\x57\x84\x82\x30\x00\x00\x00\x95\xa1"; // GetTalkListEntryResult() == 48

std::array<from::EzState::event, 13> quest_log_events = {
    from::EzState::event{from::talk_command::close_shop_message},
    from::EzState::event{from::talk_command::clear_talk_list_data},
    from::EzState::event{from::talk_command::add_talk_list_data, weapons_args},
    from::EzState::event{from::talk_command::add_talk_list_data, ammunition_args},
    from::EzState::event{from::talk_command::add_talk_list_data, spells_args},
    from::EzState::event{from::talk_command::add_talk_list_data, ashes_of_war_args},
    from::EzState::event{from::talk_command::add_talk_list_data, armor_args},
    from::EzState::event{from::talk_command::add_talk_list_data, talismans_args},
    from::EzState::event{from::talk_command::add_talk_list_data, leave_args},
    from::EzState::event{from::talk_command::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
from::EzState::transition quest_log_next_transition(&quest_log_successor_state,
                                                           talk_menu_closed_evaluator);
std::array<from::EzState::transition *, 1> quest_log_transitions = {
    &quest_log_next_transition};
from::EzState::state quest_log_state = {
    .id = 5000,
    .transitions = quest_log_transitions,
    .entry_events = quest_log_events,
};

std::array<from::EzState::transition *, 7> quest_log_successor_transitions = {
    &weapons_transition,  &ammunition_transition,
    &spells_transition,   &ashes_of_war_transition,
    &armor_transition,    &talismans_transition,
    &main_menu_return_transition,
};

from::EzState::state quest_log_successor_state = {
    .id = 5001,
    .transitions = quest_log_successor_transitions,
};

from::EzState::transition quest_log_transition(&quest_log_state,
                                                      quest_log_evaluator);

/*static from::EzState::transition quest_log_transition(&open_quests_state, open_quests_evaluator);
//static from::EzState::transition quest_log_transition(&open_quests_state, evaluator_91);

std::array<from::EzState::event, 1> open_quests_events = {
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
};*/










/*
 * "Browse Inventory" submenu
 */
std::array<from::EzState::event, 13> browse_inventory_events = {
    from::EzState::event{from::talk_command::close_shop_message},
    from::EzState::event{from::talk_command::clear_talk_list_data},
    from::EzState::event{from::talk_command::add_talk_list_data, weapons_args},
    from::EzState::event{from::talk_command::add_talk_list_data, ammunition_args},
    from::EzState::event{from::talk_command::add_talk_list_data, spells_args},
    from::EzState::event{from::talk_command::add_talk_list_data, ashes_of_war_args},
    from::EzState::event{from::talk_command::add_talk_list_data, armor_args},
    from::EzState::event{from::talk_command::add_talk_list_data, talismans_args},
    from::EzState::event{from::talk_command::add_talk_list_data, leave_args},
    from::EzState::event{from::talk_command::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
from::EzState::transition browse_inventory_next_transition(&browse_inventory_successor_state,
                                                           talk_menu_closed_evaluator);
std::array<from::EzState::transition *, 1> browse_inventory_transitions = {
    &browse_inventory_next_transition};
from::EzState::state browse_inventory_state = {
    .id = 5000,
    .transitions = browse_inventory_transitions,
    .entry_events = browse_inventory_events,
};

std::array<from::EzState::transition *, 7> browse_inventory_successor_transitions = {
    &weapons_transition,  &ammunition_transition,
    &spells_transition,   &ashes_of_war_transition,
    &armor_transition,    &talismans_transition,
    &main_menu_return_transition,
};

from::EzState::state browse_inventory_successor_state = {
    .id = 5001,
    .transitions = browse_inventory_successor_transitions,
};


/**
 * Main menu
 */
from::EzState::transition browse_inventory_transition(&browse_inventory_state,
                                                      browse_inventory_evaluator);

#undef ADD_TALK_LIST_DATA_ARGS

};
