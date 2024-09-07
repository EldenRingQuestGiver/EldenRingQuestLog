#pragma once
/**
 * Quest definitions
 */
#include <array>

#include "erquestlog_talkscript_utils.hpp"

namespace
{

int_value_data generic_dialog_shop_message = esd_int(0);
ezs::arg show_generic_dialog_shop_message_arg_list[1] = {
    generic_dialog_shop_message,
};

extern ezs::state quest_log_state;
extern ezs::state quest_log_list_state;

// Reference for debug
static constexpr unsigned int kale_alive_flag_id = 4700;
static constexpr unsigned int kale_hostile_flag_id = 4701;
static constexpr unsigned int kale_dead_flag_id = 4703;

ADD_TALK_LIST_DATA_ARGS(quest_log, 91, 82000000);   // Quest Log
static ezs::transition quest_log_transition(&quest_log_state, evals::get_talk_list[91]);

static ezs::event quest_log{talk_comm::add_talk_list_data, quest_log_args};

ezs::transition main_menu_return_transition(nullptr, evals::else_evaluator);
ezs::transition quest_log_return_transition(&quest_log_state, evals::else_evaluator);

ADD_TALK_LIST_DATA_ARGS(leave, 99, 20000009);   // Leave


// Separator for DLC quests
const esd_expression show_separator = 
    esd_or(
        esd_get_flag(2046429355), 
    esd_or(
        esd_get_flag(2045429206), 
    esd_or(
        esd_get_flag(2046429210), 
    esd_or(
        esd_get_flag(21009212), 
    esd_or(
        esd_get_flag(2051459220), 
    esd_or(
        esd_get_flag(2048429208), 
        esd_get_flag(22009255)
    ))))));

ADD_TALK_LIST_IF_DATA_ARGS(dlc_separator, 98, 82000100, show_separator);   // Quest Log
static ezs::transition dlc_separator_transition(&quest_log_state, evals::get_talk_list[98]);



/*
 * Irina's quest submenu
 */


/*esd_expression conditions[4][1] = {
    {nullptr},
    {esd_get_flag(1043319206)},
    {esd_get_flag(1045349255)},
    {esd_get_flag(1045349252)}
};

QUEST_BUILDER("irina", 8201, 3, esd_get_flag(1045349207), conditions);*/


extern ezs::state irina_quest_state;
extern ezs::state irina_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(irina_quest, 3, 82010000, esd_get_flag(1045349207));
//ADD_TALK_LIST_IF_DATA_ARGS(irina_quest, 3, 82010000, esd_or(esd_get_flag(4700), esd_compare_inventory(2962, 1)));
ezs::transition irina_quest_transition(&irina_quest_state, evals::get_talk_list[3]);

ADD_TALK_LIST_DATA_ARGS(irina_q1, 1, 82010100);
OPEN_GENERIC_DIALOG_MSG(820101, irina_q1_state, &irina_quest_state, 82010101);
ezs::transition irina_q1_transition(&irina_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(irina_q2, 2, 82010200, esd_get_flag(1043319206));
OPEN_GENERIC_DIALOG_MSG(820102, irina_q2_state, &irina_quest_state, 82010201);
ezs::transition irina_q2_transition(&irina_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(irina_q3, 3, 82010300, esd_get_flag(1045349255));
OPEN_GENERIC_DIALOG_MSG(820103, irina_q3_state, &irina_quest_state, 82010301);
ezs::transition irina_q3_transition(&irina_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(irina_q4, 4, 82010400, esd_get_flag(1045349252));
OPEN_GENERIC_DIALOG_MSG(820104, irina_q4_state, &irina_quest_state, 82010401);
ezs::transition irina_q4_transition(&irina_q4_state, evals::get_talk_list[4]);

std::array<ezs::event, 8> irina_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, irina_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, irina_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, irina_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, irina_q4_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition irina_quest_next_transition(&irina_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> irina_quest_transitions = {
    &irina_quest_next_transition};

ezs::state irina_quest_state = {
    .id = 8201,
    .transitions = irina_quest_transitions,
    .entry_events = irina_quest_events,
};

std::array<ezs::transition *, 50> irina_quest_list_transitions = {
    &irina_q1_transition,
    &irina_q2_transition, 
    &irina_q3_transition, 
    &irina_q4_transition, 
    &quest_log_return_transition,
};

ezs::state irina_quest_list_state = {
    .id = 82010,
    .transitions = irina_quest_list_transitions,
};

/*
 * Roderika's quest submenu
 */

extern ezs::state roderika_quest_state;
extern ezs::state roderika_quest_list_state;

//ADD_TALK_LIST_IF_DATA_ARGS(roderika_quest, 1, 82020000, esd_or(esd_or(esd_get_flag(1041389406), esd_get_flag(1041382735)), esd_get_flag(11109255)));
ADD_TALK_LIST_IF_DATA_ARGS(roderika_quest, 1, 82020000, esd_and(esd_get_flag(4700), esd_compare_inventory(2962, 1)));
ezs::transition roderika_quest_transition(&roderika_quest_state, evals::get_talk_list[1]);

ADD_TALK_LIST_DATA_ARGS(roderika_q1, 1, 82020100);
OPEN_GENERIC_DIALOG_MSG(820201, roderika_q1_state, &roderika_quest_state, 82020101);
ezs::transition roderika_q1_transition(&roderika_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q2, 2, 82020200, esd_or(esd_get_flag(1041382735), esd_get_flag(11109255)));
OPEN_GENERIC_DIALOG_MSG(820202, roderika_q2_state, &roderika_quest_state, 82020201);
ezs::transition roderika_q2_transition(&roderika_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q3, 3, 82020300, esd_get_flag(11109210));
OPEN_GENERIC_DIALOG_MSG(820203, roderika_q3_state, &roderika_quest_state, 82020301);
ezs::transition roderika_q3_transition(&roderika_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q4, 4, 82020400, esd_get_flag(11109256));
OPEN_GENERIC_DIALOG_MSG(820204, roderika_q4_state, &roderika_quest_state, 82020401);
ezs::transition roderika_q4_transition(&roderika_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q5, 5, 82020500, esd_get_flag(11109219));
OPEN_GENERIC_DIALOG_MSG(820205, roderika_q5_state, &roderika_quest_state, 82020501);
ezs::transition roderika_q5_transition(&roderika_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q6, 6, 82020600, esd_get_flag(3708));
OPEN_GENERIC_DIALOG_MSG(820206, roderika_q6_state, &roderika_quest_state, 82020601);
ezs::transition roderika_q6_transition(&roderika_q6_state, evals::get_talk_list[6]);

std::array<ezs::event, 10> roderika_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, roderika_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, roderika_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, roderika_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, roderika_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, roderika_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, roderika_q6_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition roderika_quest_next_transition(&roderika_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> roderika_quest_transitions = {
    &roderika_quest_next_transition};

ezs::state roderika_quest_state = {
    .id = 8202,
    .transitions = roderika_quest_transitions,
    .entry_events = roderika_quest_events,
};

std::array<ezs::transition *, 50> roderika_quest_list_transitions = {
    &roderika_q1_transition,
    &roderika_q2_transition, 
    &roderika_q3_transition, 
    &roderika_q4_transition, 
    &roderika_q5_transition, 
    &roderika_q6_transition, 
    &quest_log_return_transition,
};

ezs::state roderika_quest_list_state = {
    .id = 82020,
    .transitions = roderika_quest_list_transitions,
};

/*
 * Sorceress Sellen's quest submenu
 */

extern ezs::state sellen_quest_state;
extern ezs::state sellen_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(sellen_quest, 2, 82030000, esd_get_flag(1044369227));
ezs::transition sellen_quest_transition(&sellen_quest_state, evals::get_talk_list[2]);

ADD_TALK_LIST_DATA_ARGS(sellen_q1, 1, 82030100);
OPEN_GENERIC_DIALOG_MSG(820301, sellen_q1_state, &sellen_quest_state, 82030101);
ezs::transition sellen_q1_transition(&sellen_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q2, 2, 82030200, esd_get_flag(1044369219));
OPEN_GENERIC_DIALOG_MSG(820302, sellen_q2_state, &sellen_quest_state, 82030201);
ezs::transition sellen_q2_transition(&sellen_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q3, 3, 82030300, esd_get_flag(1044369222));
OPEN_GENERIC_DIALOG_MSG(820303, sellen_q3_state, &sellen_quest_state, 82030301);
ezs::transition sellen_q3_transition(&sellen_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q4, 4, 82030400, esd_get_flag(1041339256));
OPEN_GENERIC_DIALOG_MSG(820304, sellen_q4_state, &sellen_quest_state, 82030401);
ezs::transition sellen_q4_transition(&sellen_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q5, 5, 82030500, esd_get_flag(1034509255));
OPEN_GENERIC_DIALOG_MSG(820305, sellen_q5_state, &sellen_quest_state, 82030501);
ezs::transition sellen_q5_transition(&sellen_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q6, 6, 82030600, esd_get_flag(3371));
OPEN_GENERIC_DIALOG_MSG(820306, sellen_q6_state, &sellen_quest_state, 82030601);
ezs::transition sellen_q6_transition(&sellen_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q7, 7, 82030700, esd_get_flag(14009255));
OPEN_GENERIC_DIALOG_MSG(820307, sellen_q7_state, &sellen_quest_state, 82030701);
ezs::transition sellen_q7_transition(&sellen_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q8, 8, 82030800, esd_get_flag(3469));
OPEN_GENERIC_DIALOG_MSG(820308, sellen_q8_state, &sellen_quest_state, 82030801);
ezs::transition sellen_q8_transition(&sellen_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q99, 50, 82039900, esd_get_flag(3463));
OPEN_GENERIC_DIALOG_MSG(820350, sellen_q99_state, &sellen_quest_state, 82039901);
ezs::transition sellen_q99_transition(&sellen_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 13> sellen_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, sellen_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, sellen_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, sellen_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, sellen_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, sellen_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, sellen_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, sellen_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, sellen_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, sellen_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition sellen_quest_next_transition(&sellen_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> sellen_quest_transitions = {
    &sellen_quest_next_transition};

ezs::state sellen_quest_state = {
    .id = 82030,
    .transitions = sellen_quest_transitions,
    .entry_events = sellen_quest_events,
};

std::array<ezs::transition *, 50> sellen_quest_list_transitions = {
    &sellen_q1_transition,
    &sellen_q2_transition, 
    &sellen_q3_transition, 
    &sellen_q4_transition, 
    &sellen_q5_transition, 
    &sellen_q6_transition, 
    &sellen_q7_transition, 
    &sellen_q8_transition, 
    &sellen_q99_transition, 
    &quest_log_return_transition,
};

ezs::state sellen_quest_list_state = {
    .id = 820300,
    .transitions = sellen_quest_list_transitions,
};

/*
 * Kenneth Haight's quest submenu
 */

extern ezs::state kenneth_quest_state;
extern ezs::state kenneth_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_quest, 4, 82040000, esd_get_flag(1045389205));
ezs::transition kenneth_quest_transition(&kenneth_quest_state, evals::get_talk_list[4]);

ADD_TALK_LIST_DATA_ARGS(kenneth_q1, 1, 82040100);
OPEN_GENERIC_DIALOG_MSG(820401, kenneth_q1_state, &kenneth_quest_state, 82040101);
ezs::transition kenneth_q1_transition(&kenneth_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q2, 2, 82040200, esd_get_flag(1045389222));
OPEN_GENERIC_DIALOG_MSG(820402, kenneth_q2_state, &kenneth_quest_state, 82040201);
ezs::transition kenneth_q2_transition(&kenneth_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q3, 3, 82040300, esd_get_flag(1046360706));
OPEN_GENERIC_DIALOG_MSG(820403, kenneth_q3_state, &kenneth_quest_state, 82040301);
ezs::transition kenneth_q3_transition(&kenneth_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q4, 4, 82040400, esd_get_flag(1046369207));
OPEN_GENERIC_DIALOG_MSG(820404, kenneth_q4_state, &kenneth_quest_state, 82040401);
ezs::transition kenneth_q4_transition(&kenneth_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q5, 5, 82040500, esd_and(esd_get_flag(3587), esd_get_flag(4229)));
OPEN_GENERIC_DIALOG_MSG(820405, kenneth_q5_state, &kenneth_quest_state, 82040501);
ezs::transition kenneth_q5_transition(&kenneth_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q99, 50, 82049900, esd_get_flag(3583));
OPEN_GENERIC_DIALOG_MSG(820450, kenneth_q99_state, &kenneth_quest_state, 82049901);
ezs::transition kenneth_q99_transition(&kenneth_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 10> kenneth_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, kenneth_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, kenneth_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, kenneth_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, kenneth_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, kenneth_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, kenneth_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition kenneth_quest_next_transition(&kenneth_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> kenneth_quest_transitions = {
    &kenneth_quest_next_transition};

ezs::state kenneth_quest_state = {
    .id = 82040,
    .transitions = kenneth_quest_transitions,
    .entry_events = kenneth_quest_events,
};

std::array<ezs::transition *, 50> kenneth_quest_list_transitions = {
    &kenneth_q1_transition,
    &kenneth_q2_transition, 
    &kenneth_q3_transition, 
    &kenneth_q4_transition, 
    &kenneth_q5_transition, 
    &kenneth_q99_transition, 
    &quest_log_return_transition,
};

ezs::state kenneth_quest_list_state = {
    .id = 820400,
    .transitions = kenneth_quest_list_transitions,
};

/*
 * Boc's quest submenu
 */

extern ezs::state boc_quest_state;
extern ezs::state boc_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(boc_quest, 5, 82050000, esd_get_flag(1043379355));
ezs::transition boc_quest_transition(&boc_quest_state, evals::get_talk_list[5]);

ADD_TALK_LIST_DATA_ARGS(boc_q1, 1, 82050100);
OPEN_GENERIC_DIALOG_MSG(820501, boc_q1_state, &boc_quest_state, 82050101);
ezs::transition boc_q1_transition(&boc_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q2, 2, 82050200, esd_get_flag(31159202));
OPEN_GENERIC_DIALOG_MSG(820502, boc_q2_state, &boc_quest_state, 82050201);
ezs::transition boc_q2_transition(&boc_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q3, 3, 82050300, esd_get_flag(31159206));
OPEN_GENERIC_DIALOG_MSG(820503, boc_q3_state, &boc_quest_state, 82050301);
ezs::transition boc_q3_transition(&boc_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q4, 4, 82050400, esd_get_flag(1036489208));
OPEN_GENERIC_DIALOG_MSG(820504, boc_q4_state, &boc_quest_state, 82050401);
ezs::transition boc_q4_transition(&boc_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q5, 5, 82050500, esd_get_flag(1039409259));
OPEN_GENERIC_DIALOG_MSG(820505, boc_q5_state, &boc_quest_state, 82050501);
ezs::transition boc_q5_transition(&boc_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q6, 6, 82050600, esd_get_flag(11109808));
OPEN_GENERIC_DIALOG_MSG(820506, boc_q6_state, &boc_quest_state, 82050601);
ezs::transition boc_q6_transition(&boc_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q7, 7, 82050700, esd_get_flag(11109315));
OPEN_GENERIC_DIALOG_MSG(820507, boc_q7_state, &boc_quest_state, 82050701);
ezs::transition boc_q7_transition(&boc_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q99, 50, 82059900, esd_get_flag(3943));
OPEN_GENERIC_DIALOG_MSG(820550, boc_q99_state, &boc_quest_state, 82059901);
ezs::transition boc_q99_transition(&boc_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 12> boc_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, boc_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, boc_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, boc_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, boc_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, boc_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, boc_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, boc_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, boc_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition boc_quest_next_transition(&boc_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> boc_quest_transitions = {
    &boc_quest_next_transition};

ezs::state boc_quest_state = {
    .id = 82050,
    .transitions = boc_quest_transitions,
    .entry_events = boc_quest_events,
};

std::array<ezs::transition *, 50> boc_quest_list_transitions = {
    &boc_q1_transition,
    &boc_q2_transition, 
    &boc_q3_transition, 
    &boc_q4_transition, 
    &boc_q5_transition, 
    &boc_q6_transition, 
    &boc_q7_transition, 
    &boc_q99_transition, 
    &quest_log_return_transition,
};

ezs::state boc_quest_list_state = {
    .id = 820500,
    .transitions = boc_quest_list_transitions,
};

/*
 * Blaidd's quest submenu
 */

extern ezs::state blaidd_quest_state;
extern ezs::state blaidd_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_quest, 6, 82060000, esd_or(esd_get_flag(1042369320), esd_get_flag(1042369328)));
ezs::transition blaidd_quest_transition(&blaidd_quest_state, evals::get_talk_list[6]);

ADD_TALK_LIST_DATA_ARGS(blaidd_q1, 1, 82060100);
OPEN_GENERIC_DIALOG_MSG(820601, blaidd_q1_state, &blaidd_quest_state, 82060101);
ezs::transition blaidd_q1_transition(&blaidd_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q2, 2, 82060200, esd_get_flag(60830));
OPEN_GENERIC_DIALOG_MSG(820602, blaidd_q2_state, &blaidd_quest_state, 82060201);
ezs::transition blaidd_q2_transition(&blaidd_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q3, 3, 82060300, esd_get_flag(1045379205));
OPEN_GENERIC_DIALOG_MSG(820603, blaidd_q3_state, &blaidd_quest_state, 82060301);
ezs::transition blaidd_q3_transition(&blaidd_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q4, 4, 82060400, esd_get_flag(1044349256));
OPEN_GENERIC_DIALOG_MSG(820604, blaidd_q4_state, &blaidd_quest_state, 82060401);
ezs::transition blaidd_q4_transition(&blaidd_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q5, 5, 82060500, esd_get_flag(12029155));
OPEN_GENERIC_DIALOG_MSG(820605, blaidd_q5_state, &blaidd_quest_state, 82060501);
ezs::transition blaidd_q5_transition(&blaidd_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q6, 6, 82060600, esd_get_flag(1051369355));
OPEN_GENERIC_DIALOG_MSG(820606, blaidd_q6_state, &blaidd_quest_state, 82060601);
ezs::transition blaidd_q6_transition(&blaidd_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q7, 7, 82060700, esd_get_flag(1052389305));
OPEN_GENERIC_DIALOG_MSG(820607, blaidd_q7_state, &blaidd_quest_state, 82060701);
ezs::transition blaidd_q7_transition(&blaidd_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q99, 50, 82069900, esd_get_flag(3603));
OPEN_GENERIC_DIALOG_MSG(820650, blaidd_q99_state, &blaidd_quest_state, 82069901);
ezs::transition blaidd_q99_transition(&blaidd_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 12> blaidd_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, blaidd_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, blaidd_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, blaidd_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, blaidd_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, blaidd_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, blaidd_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, blaidd_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, blaidd_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition blaidd_quest_next_transition(&blaidd_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> blaidd_quest_transitions = {
    &blaidd_quest_next_transition};

ezs::state blaidd_quest_state = {
    .id = 82060,
    .transitions = blaidd_quest_transitions,
    .entry_events = blaidd_quest_events,
};

std::array<ezs::transition *, 50> blaidd_quest_list_transitions = {
    &blaidd_q1_transition,
    &blaidd_q2_transition, 
    &blaidd_q3_transition, 
    &blaidd_q4_transition, 
    &blaidd_q5_transition, 
    &blaidd_q6_transition, 
    &blaidd_q7_transition, 
    &blaidd_q99_transition, 
    &quest_log_return_transition,
};

ezs::state blaidd_quest_list_state = {
    .id = 820600,
    .transitions = blaidd_quest_list_transitions,
};

/*
 * Sorcerer Thops's quest submenu
 */

extern ezs::state thops_quest_state;
extern ezs::state thops_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(thops_quest, 7, 82070000, esd_get_flag(1039399215));
ezs::transition thops_quest_transition(&thops_quest_state, evals::get_talk_list[7]);

ADD_TALK_LIST_DATA_ARGS(thops_q1, 1, 82070100);
OPEN_GENERIC_DIALOG_MSG(820701, thops_q1_state, &thops_quest_state, 82070101);
ezs::transition thops_q1_transition(&thops_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(thops_q2, 2, 82070200, esd_get_flag(1039399220));
OPEN_GENERIC_DIALOG_MSG(820702, thops_q2_state, &thops_quest_state, 82070201);
ezs::transition thops_q2_transition(&thops_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(thops_q99, 50, 82079900, esd_get_flag(3803));
OPEN_GENERIC_DIALOG_MSG(820750, thops_q99_state, &thops_quest_state, 82079901);
ezs::transition thops_q99_transition(&thops_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 7> thops_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, thops_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, thops_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, thops_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition thops_quest_next_transition(&thops_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> thops_quest_transitions = {
    &thops_quest_next_transition};

ezs::state thops_quest_state = {
    .id = 82070,
    .transitions = thops_quest_transitions,
    .entry_events = thops_quest_events,
};

std::array<ezs::transition *, 50> thops_quest_list_transitions = {
    &thops_q1_transition,
    &thops_q2_transition, 
    &thops_q99_transition, 
    &quest_log_return_transition,
};

ezs::state thops_quest_list_state = {
    .id = 820700,
    .transitions = thops_quest_list_transitions,
};

/*
 * Patches' quest submenu
 */

extern ezs::state patches_quest_state;
extern ezs::state patches_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(patches_quest, 8, 82080000, esd_or(esd_get_flag(31009206), esd_get_flag(16009357)));
ezs::transition patches_quest_transition(&patches_quest_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q1, 1, 82080100, esd_get_flag(60819));
OPEN_GENERIC_DIALOG_MSG(820801, patches_q1_state, &patches_quest_state, 82080101);
ezs::transition patches_q1_transition(&patches_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q2, 2, 82080200, esd_get_flag(31008522));
OPEN_GENERIC_DIALOG_MSG(820802, patches_q2_state, &patches_quest_state, 82080201);
ezs::transition patches_q2_transition(&patches_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q3, 3, 82080300, esd_get_flag(1038419259));
OPEN_GENERIC_DIALOG_MSG(820803, patches_q3_state, &patches_quest_state, 82080301);
ezs::transition patches_q3_transition(&patches_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q4, 4, 82080400, esd_and(esd_get_flag(14009300), esd_get_flag(1038419259)));
OPEN_GENERIC_DIALOG_MSG(820804, patches_q4_state, &patches_quest_state, 82080401);
ezs::transition patches_q4_transition(&patches_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q5, 5, 82080500, esd_and(esd_get_flag(1037549206), esd_get_flag(1037549209, 0)));
OPEN_GENERIC_DIALOG_MSG(820805, patches_q5_state, &patches_quest_state, 82080501);
ezs::transition patches_q5_transition(&patches_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q6, 6, 82080600, esd_get_flag(3693));
OPEN_GENERIC_DIALOG_MSG(820806, patches_q6_state, &patches_quest_state, 82080601);
ezs::transition patches_q6_transition(&patches_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q7, 7, 82080700, esd_get_flag(16009355));
OPEN_GENERIC_DIALOG_MSG(820807, patches_q7_state, &patches_quest_state, 82080701);
ezs::transition patches_q7_transition(&patches_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q8, 8, 82080800, esd_get_flag(16009357));
OPEN_GENERIC_DIALOG_MSG(820808, patches_q8_state, &patches_quest_state, 82080801);
ezs::transition patches_q8_transition(&patches_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q9, 9, 82080900, esd_or(esd_get_flag(16009364), esd_or(esd_get_flag(16009358), esd_get_flag(16002721))));
OPEN_GENERIC_DIALOG_MSG(820809, patches_q9_state, &patches_quest_state, 82080901);
ezs::transition patches_q9_transition(&patches_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q99, 50, 82089900, esd_get_flag(3683));
OPEN_GENERIC_DIALOG_MSG(820850, patches_q99_state, &patches_quest_state, 82089901);
ezs::transition patches_q99_transition(&patches_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 14> patches_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, patches_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition patches_quest_next_transition(&patches_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> patches_quest_transitions = {
    &patches_quest_next_transition};

ezs::state patches_quest_state = {
    .id = 82080,
    .transitions = patches_quest_transitions,
    .entry_events = patches_quest_events,
};

std::array<ezs::transition *, 50> patches_quest_list_transitions = {
    &patches_q1_transition,
    &patches_q2_transition, 
    &patches_q3_transition, 
    &patches_q4_transition, 
    &patches_q5_transition, 
    &patches_q6_transition, 
    &patches_q7_transition, 
    &patches_q8_transition, 
    &patches_q9_transition, 
    &patches_q99_transition, 
    &quest_log_return_transition,
};

ezs::state patches_quest_list_state = {
    .id = 820800,
    .transitions = patches_quest_list_transitions,
};

/*
 * Ranni's quest submenu
 */

extern ezs::state ranni_quest_state;
extern ezs::state ranni_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(ranni_quest, 9, 82090000, esd_or(esd_get_flag(1034509410), esd_get_flag(1034509431)));
ezs::transition ranni_quest_transition(&ranni_quest_state, evals::get_talk_list[9]);

ADD_TALK_LIST_DATA_ARGS(ranni_q1, 1, 82090100);
OPEN_GENERIC_DIALOG_MSG(820901, ranni_q1_state, &ranni_quest_state, 82090101);
ezs::transition ranni_q1_transition(&ranni_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q2, 2, 82090200, esd_get_flag(1034509413));
OPEN_GENERIC_DIALOG_MSG(820902, ranni_q2_state, &ranni_quest_state, 82090201);
ezs::transition ranni_q2_transition(&ranni_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q3, 3, 82090300, esd_get_flag(1034509416));
OPEN_GENERIC_DIALOG_MSG(820903, ranni_q3_state, &ranni_quest_state, 82090301);
ezs::transition ranni_q3_transition(&ranni_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q4, 4, 82090400, esd_get_flag(1044369214));
OPEN_GENERIC_DIALOG_MSG(820904, ranni_q4_state, &ranni_quest_state, 82090401);
ezs::transition ranni_q4_transition(&ranni_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q5, 5, 82090500, esd_get_flag(1044369223, 0));
OPEN_GENERIC_DIALOG_MSG(820905, ranni_q5_state, &ranni_quest_state, 82090501);
ezs::transition ranni_q5_transition(&ranni_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q6, 6, 82090600, esd_get_flag(9130));
OPEN_GENERIC_DIALOG_MSG(820906, ranni_q6_state, &ranni_quest_state, 82090601);
ezs::transition ranni_q6_transition(&ranni_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q7, 7, 82090700, esd_or(esd_compare_inventory(8159, 1), esd_get_flag(1034509420)));
OPEN_GENERIC_DIALOG_MSG(820907, ranni_q7_state, &ranni_quest_state, 82090701);
ezs::transition ranni_q7_transition(&ranni_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q8, 8, 82090800, esd_get_flag(1034509421));
OPEN_GENERIC_DIALOG_MSG(820908, ranni_q8_state, &ranni_quest_state, 82090801);
ezs::transition ranni_q8_transition(&ranni_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q9, 9, 82090900, esd_compare_inventory(8191, 1));
OPEN_GENERIC_DIALOG_MSG(820909, ranni_q9_state, &ranni_quest_state, 82090901);
ezs::transition ranni_q9_transition(&ranni_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q10, 10, 82091000, esd_or(esd_compare_inventory(8146, 1), esd_compare_inventory(8187, 1)));
OPEN_GENERIC_DIALOG_MSG(8209010, ranni_q10_state, &ranni_quest_state, 82091001);
ezs::transition ranni_q10_transition(&ranni_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q11, 11, 82091100, esd_get_flag(12019257));
OPEN_GENERIC_DIALOG_MSG(820911, ranni_q11_state, &ranni_quest_state, 82091101);
ezs::transition ranni_q11_transition(&ranni_q11_state, evals::get_talk_list[11]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q12, 12, 82091200, esd_or(esd_compare_inventory(8121, 1, 1), esd_get_flag(1034509406)));
OPEN_GENERIC_DIALOG_MSG(820912, ranni_q12_state, &ranni_quest_state, 82091201);
ezs::transition ranni_q12_transition(&ranni_q12_state, evals::get_talk_list[12]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q13, 13, 82091300, esd_get_flag(1034509406));
OPEN_GENERIC_DIALOG_MSG(820913, ranni_q13_state, &ranni_quest_state, 82091301);
ezs::transition ranni_q13_transition(&ranni_q13_state, evals::get_talk_list[13]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q99, 50, 82099900, esd_get_flag(1034502742));
OPEN_GENERIC_DIALOG_MSG(820950, ranni_q99_state, &ranni_quest_state, 82099901);
ezs::transition ranni_q99_transition(&ranni_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 18> ranni_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, ranni_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q10_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q11_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q12_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q13_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition ranni_quest_next_transition(&ranni_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> ranni_quest_transitions = {
    &ranni_quest_next_transition};

ezs::state ranni_quest_state = {
    .id = 82090,
    .transitions = ranni_quest_transitions,
    .entry_events = ranni_quest_events,
};

std::array<ezs::transition *, 50> ranni_quest_list_transitions = {
    &ranni_q1_transition,
    &ranni_q2_transition, 
    &ranni_q3_transition, 
    &ranni_q4_transition, 
    &ranni_q5_transition, 
    &ranni_q6_transition, 
    &ranni_q7_transition, 
    &ranni_q8_transition, 
    &ranni_q9_transition, 
    &ranni_q10_transition, 
    &ranni_q11_transition, 
    &ranni_q12_transition, 
    &ranni_q13_transition, 
    &ranni_q99_transition, 
    &quest_log_return_transition,
};

ezs::state ranni_quest_list_state = {
    .id = 820900,
    .transitions = ranni_quest_list_transitions,
};

/*
 * Rya's quest submenu
 */

extern ezs::state rya_quest_state;
extern ezs::state rya_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(rya_quest, 10, 82100000, esd_get_flag(1037429209));
ezs::transition rya_quest_transition(&rya_quest_state, evals::get_talk_list[10]);

ADD_TALK_LIST_DATA_ARGS(rya_q1, 1, 82100100);
OPEN_GENERIC_DIALOG_MSG(821001, rya_q1_state, &rya_quest_state, 82100101);
ezs::transition rya_q1_transition(&rya_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q2, 2, 82100200, esd_get_flag(1037429210));
OPEN_GENERIC_DIALOG_MSG(821002, rya_q2_state, &rya_quest_state, 82100201);
ezs::transition rya_q2_transition(&rya_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q3, 3, 82100300, esd_get_flag(1038519205));
OPEN_GENERIC_DIALOG_MSG(821003, rya_q3_state, &rya_quest_state, 82100301);
ezs::transition rya_q3_transition(&rya_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q4, 4, 82100400, esd_get_flag(16009305));
OPEN_GENERIC_DIALOG_MSG(821004, rya_q4_state, &rya_quest_state, 82100401);
ezs::transition rya_q4_transition(&rya_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q5, 5, 82100500, esd_get_flag(16009308));
OPEN_GENERIC_DIALOG_MSG(821005, rya_q5_state, &rya_quest_state, 82100501);
ezs::transition rya_q5_transition(&rya_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q6, 6, 82100600, esd_get_flag(16009307));
OPEN_GENERIC_DIALOG_MSG(821006, rya_q6_state, &rya_quest_state, 82100601);
ezs::transition rya_q6_transition(&rya_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q7, 7, 82100700, esd_get_flag(16009315));
OPEN_GENERIC_DIALOG_MSG(821007, rya_q7_state, &rya_quest_state, 82100701);
ezs::transition rya_q7_transition(&rya_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q8, 8, 82100800, esd_get_flag(16009318));
OPEN_GENERIC_DIALOG_MSG(821008, rya_q8_state, &rya_quest_state, 82100801);
ezs::transition rya_q8_transition(&rya_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q9, 9, 82100900, esd_get_flag(16009319));
OPEN_GENERIC_DIALOG_MSG(821009, rya_q9_state, &rya_quest_state, 82100901);
ezs::transition rya_q9_transition(&rya_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q10, 10, 82101000, esd_get_flag(16009222));
OPEN_GENERIC_DIALOG_MSG(8210010, rya_q10_state, &rya_quest_state, 82101001);
ezs::transition rya_q10_transition(&rya_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q11, 11, 82101100, esd_get_flag(16009326));
OPEN_GENERIC_DIALOG_MSG(821011, rya_q11_state, &rya_quest_state, 82101101);
ezs::transition rya_q11_transition(&rya_q11_state, evals::get_talk_list[11]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q12, 12, 82101200, esd_compare_inventory(8221, 1, 1));
OPEN_GENERIC_DIALOG_MSG(821012, rya_q12_state, &rya_quest_state, 82101201);
ezs::transition rya_q12_transition(&rya_q12_state, evals::get_talk_list[12]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q13, 13, 82101300, esd_get_flag(16009327));
OPEN_GENERIC_DIALOG_MSG(821013, rya_q13_state, &rya_quest_state, 82101301);
ezs::transition rya_q13_transition(&rya_q13_state, evals::get_talk_list[13]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q99, 50, 82109900, esd_get_flag(3429));
OPEN_GENERIC_DIALOG_MSG(821050, rya_q99_state, &rya_quest_state, 82109901);
ezs::transition rya_q99_transition(&rya_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 18> rya_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, rya_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q10_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q11_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q12_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q13_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition rya_quest_next_transition(&rya_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> rya_quest_transitions = {
    &rya_quest_next_transition};

ezs::state rya_quest_state = {
    .id = 82100,
    .transitions = rya_quest_transitions,
    .entry_events = rya_quest_events,
};

std::array<ezs::transition *, 50> rya_quest_list_transitions = {
    &rya_q1_transition,
    &rya_q2_transition, 
    &rya_q3_transition, 
    &rya_q4_transition, 
    &rya_q5_transition, 
    &rya_q6_transition, 
    &rya_q7_transition, 
    &rya_q8_transition, 
    &rya_q9_transition, 
    &rya_q10_transition, 
    &rya_q11_transition, 
    &rya_q12_transition, 
    &rya_q13_transition, 
    &rya_q99_transition, 
    &quest_log_return_transition,
};

ezs::state rya_quest_list_state = {
    .id = 821000,
    .transitions = rya_quest_list_transitions,
};

/*
 * Gowry's quest submenu
 */

extern ezs::state gowry_quest_state;
extern ezs::state gowry_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(gowry_quest, 11, 82110000, esd_get_flag(1050389205));
ezs::transition gowry_quest_transition(&gowry_quest_state, evals::get_talk_list[11]);

ADD_TALK_LIST_DATA_ARGS(gowry_q1, 1, 82110100);
OPEN_GENERIC_DIALOG_MSG(821101, gowry_q1_state, &gowry_quest_state, 82110101);
ezs::transition gowry_q1_transition(&gowry_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q2, 2, 82110200, esd_get_flag(1050389207));
OPEN_GENERIC_DIALOG_MSG(821102, gowry_q2_state, &gowry_quest_state, 82110201);
ezs::transition gowry_q2_transition(&gowry_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q3, 3, 82110300, esd_get_flag(1050389210));
OPEN_GENERIC_DIALOG_MSG(821103, gowry_q3_state, &gowry_quest_state, 82110301);
ezs::transition gowry_q3_transition(&gowry_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q4, 4, 82110400, esd_get_flag(1050389257));
OPEN_GENERIC_DIALOG_MSG(821104, gowry_q4_state, &gowry_quest_state, 82110401);
ezs::transition gowry_q4_transition(&gowry_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q5, 5, 82110500, esd_get_flag(1050389219));
OPEN_GENERIC_DIALOG_MSG(821105, gowry_q5_state, &gowry_quest_state, 82110501);
ezs::transition gowry_q5_transition(&gowry_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q6, 6, 82110600, esd_get_flag(1050389221));
OPEN_GENERIC_DIALOG_MSG(821106, gowry_q6_state, &gowry_quest_state, 82110601);
ezs::transition gowry_q6_transition(&gowry_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q7, 7, 82110700, esd_get_flag(1050389227));
OPEN_GENERIC_DIALOG_MSG(821107, gowry_q7_state, &gowry_quest_state, 82110701);
ezs::transition gowry_q7_transition(&gowry_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q8, 8, 82110800, esd_get_flag(1050389230));
OPEN_GENERIC_DIALOG_MSG(821108, gowry_q8_state, &gowry_quest_state, 82110801);
ezs::transition gowry_q8_transition(&gowry_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q9, 9, 82110900, esd_get_flag(1050389234));
OPEN_GENERIC_DIALOG_MSG(821109, gowry_q9_state, &gowry_quest_state, 82110901);
ezs::transition gowry_q9_transition(&gowry_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q10, 10, 82111000, esd_get_flag(1050389235));
OPEN_GENERIC_DIALOG_MSG(8211010, gowry_q10_state, &gowry_quest_state, 82111001);
ezs::transition gowry_q10_transition(&gowry_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q99, 50, 82119900, esd_get_flag(3429));
OPEN_GENERIC_DIALOG_MSG(821150, gowry_q99_state, &gowry_quest_state, 82119901);
ezs::transition gowry_q99_transition(&gowry_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 15> gowry_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, gowry_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q10_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition gowry_quest_next_transition(&gowry_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> gowry_quest_transitions = {
    &gowry_quest_next_transition};

ezs::state gowry_quest_state = {
    .id = 82110,
    .transitions = gowry_quest_transitions,
    .entry_events = gowry_quest_events,
};

std::array<ezs::transition *, 50> gowry_quest_list_transitions = {
    &gowry_q1_transition,
    &gowry_q2_transition, 
    &gowry_q3_transition, 
    &gowry_q4_transition, 
    &gowry_q5_transition, 
    &gowry_q6_transition, 
    &gowry_q7_transition, 
    &gowry_q8_transition, 
    &gowry_q9_transition, 
    &gowry_q10_transition, 
    &gowry_q99_transition, 
    &quest_log_return_transition,
};

ezs::state gowry_quest_list_state = {
    .id = 821100,
    .transitions = gowry_quest_list_transitions,
};

/*
 * D's quest submenu
 */

extern ezs::state d_quest_state;
extern ezs::state d_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(d_quest, 12, 82120000, esd_or(esd_get_flag(1044399206), esd_and(esd_get_flag(1051439205), esd_get_flag(11109617))));
ezs::transition d_quest_transition(&d_quest_state, evals::get_talk_list[12]);

ADD_TALK_LIST_DATA_ARGS(d_q1, 1, 82120100);
OPEN_GENERIC_DIALOG_MSG(821201, d_q1_state, &d_quest_state, 82120101);
ezs::transition d_q1_transition(&d_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q2, 2, 82120200, esd_and(esd_get_flag(1051439205), esd_get_flag(11109617, 0)));
OPEN_GENERIC_DIALOG_MSG(821202, d_q2_state, &d_quest_state, 82120201);
ezs::transition d_q2_transition(&d_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q3, 3, 82120300, esd_get_flag(1044399206));
OPEN_GENERIC_DIALOG_MSG(821203, d_q3_state, &d_quest_state, 82120301);
ezs::transition d_q3_transition(&d_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q4, 4, 82120400, esd_get_flag(11109625));
OPEN_GENERIC_DIALOG_MSG(821204, d_q4_state, &d_quest_state, 82120401);
ezs::transition d_q4_transition(&d_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q5, 5, 82120500, esd_get_flag(11102843));
OPEN_GENERIC_DIALOG_MSG(821205, d_q5_state, &d_quest_state, 82120501);
ezs::transition d_q5_transition(&d_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q6, 6, 82120600, esd_get_flag(12029015));
OPEN_GENERIC_DIALOG_MSG(821206, d_q6_state, &d_quest_state, 82120601);
ezs::transition d_q6_transition(&d_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q7, 7, 82120700, esd_get_flag(12039005));
OPEN_GENERIC_DIALOG_MSG(821207, d_q7_state, &d_quest_state, 82120701);
ezs::transition d_q7_transition(&d_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q99, 50, 82129900, esd_get_flag(3429));
OPEN_GENERIC_DIALOG_MSG(821250, d_q99_state, &d_quest_state, 82129901);
ezs::transition d_q99_transition(&d_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 12> d_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, d_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, d_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, d_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, d_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, d_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, d_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, d_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, d_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition d_quest_next_transition(&d_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> d_quest_transitions = {
    &d_quest_next_transition};

ezs::state d_quest_state = {
    .id = 82120,
    .transitions = d_quest_transitions,
    .entry_events = d_quest_events,
};

std::array<ezs::transition *, 50> d_quest_list_transitions = {
    &d_q1_transition,
    &d_q2_transition, 
    &d_q3_transition, 
    &d_q4_transition, 
    &d_q5_transition, 
    &d_q6_transition, 
    &d_q7_transition, 
    &d_q99_transition, 
    &quest_log_return_transition,
};

ezs::state d_quest_list_state = {
    .id = 821200,
    .transitions = d_quest_list_transitions,
};


/*
 * Gurranq's quest submenu
 */

extern ezs::state gurranq_quest_state;
extern ezs::state gurranq_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_quest, 13, 82130000, esd_and(esd_get_flag(1051439205), esd_get_flag(11109617)));
ezs::transition gurranq_quest_transition(&gurranq_quest_state, evals::get_talk_list[13]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q1, 1, 82130100, esd_get_flag_value(1051439230, 1, 0));
OPEN_GENERIC_DIALOG_MSG(821301, gurranq_q1_state, &gurranq_quest_state, 82130101);
ezs::transition gurranq_q1_transition(&gurranq_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q2, 2, 82130100, esd_get_flag_value(1051439230, 2, 0));
OPEN_GENERIC_DIALOG_MSG(821302, gurranq_q2_state, &gurranq_quest_state, 82130102);
ezs::transition gurranq_q2_transition(&gurranq_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q3, 3, 82130100, esd_get_flag_value(1051439230, 3, 0));
OPEN_GENERIC_DIALOG_MSG(821303, gurranq_q3_state, &gurranq_quest_state, 82130103);
ezs::transition gurranq_q3_transition(&gurranq_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q4, 4, 82130100, esd_get_flag_value(1051439230, 4, 0));
OPEN_GENERIC_DIALOG_MSG(821304, gurranq_q4_state, &gurranq_quest_state, 82130104);
ezs::transition gurranq_q4_transition(&gurranq_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q5, 5, 82130100, esd_get_flag_value(1051439230, 5, 0));
OPEN_GENERIC_DIALOG_MSG(821305, gurranq_q5_state, &gurranq_quest_state, 82130105);
ezs::transition gurranq_q5_transition(&gurranq_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q6, 6, 82130100, esd_get_flag_value(1051439230, 6, 0));
OPEN_GENERIC_DIALOG_MSG(821306, gurranq_q6_state, &gurranq_quest_state, 82130106);
ezs::transition gurranq_q6_transition(&gurranq_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q7, 7, 82130100, esd_get_flag_value(1051439230, 7, 0));
OPEN_GENERIC_DIALOG_MSG(821307, gurranq_q7_state, &gurranq_quest_state, 82130107);
ezs::transition gurranq_q7_transition(&gurranq_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q8, 8, 82130100, esd_get_flag_value(1051439230, 8, 0));
OPEN_GENERIC_DIALOG_MSG(821308, gurranq_q8_state, &gurranq_quest_state, 82130108);
ezs::transition gurranq_q8_transition(&gurranq_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q9, 9, 82130100, esd_get_flag_value(1051439230, 9, 2));
OPEN_GENERIC_DIALOG_MSG(821309, gurranq_q9_state, &gurranq_quest_state, 82130109);
ezs::transition gurranq_q9_transition(&gurranq_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q10, 10, 82130200, esd_get_flag(1051439211));
OPEN_GENERIC_DIALOG_MSG(8213010, gurranq_q10_state, &gurranq_quest_state, 82130201);
ezs::transition gurranq_q10_transition(&gurranq_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q11, 11, 82130300, esd_get_flag_value(1051439230, 9, 2));
OPEN_GENERIC_DIALOG_MSG(821311, gurranq_q11_state, &gurranq_quest_state, 82130301);
ezs::transition gurranq_q11_transition(&gurranq_q11_state, evals::get_talk_list[11]);

std::array<ezs::event, 15> gurranq_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q10_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_q11_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition gurranq_quest_next_transition(&gurranq_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> gurranq_quest_transitions = {
    &gurranq_quest_next_transition};

ezs::state gurranq_quest_state = {
    .id = 82130,
    .transitions = gurranq_quest_transitions,
    .entry_events = gurranq_quest_events,
};

std::array<ezs::transition *, 50> gurranq_quest_list_transitions = {
    &gurranq_q1_transition,
    &gurranq_q2_transition, 
    &gurranq_q3_transition, 
    &gurranq_q4_transition, 
    &gurranq_q5_transition, 
    &gurranq_q6_transition, 
    &gurranq_q7_transition, 
    &gurranq_q8_transition, 
    &gurranq_q9_transition, 
    &gurranq_q10_transition, 
    &gurranq_q11_transition, 
    &quest_log_return_transition,
};

ezs::state gurranq_quest_list_state = {
    .id = 821300,
    .transitions = gurranq_quest_list_transitions,
};

/*
 * Diallos' quest submenu
 */

extern ezs::state diallos_quest_state;
extern ezs::state diallos_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(diallos_quest, 14, 82140000, esd_get_flag(11109406));
ezs::transition diallos_quest_transition(&diallos_quest_state, evals::get_talk_list[14]);

ADD_TALK_LIST_DATA_ARGS(diallos_q1, 1, 82140100);
OPEN_GENERIC_DIALOG_MSG(821401, diallos_q1_state, &diallos_quest_state, 82140101);
ezs::transition diallos_q1_transition(&diallos_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q2, 2, 82140200, esd_get_flag(1037449205));
OPEN_GENERIC_DIALOG_MSG(821402, diallos_q2_state, &diallos_quest_state, 82140201);
ezs::transition diallos_q2_transition(&diallos_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q3, 3, 82140300, esd_get_flag(11109430));
OPEN_GENERIC_DIALOG_MSG(821403, diallos_q3_state, &diallos_quest_state, 82140301);
ezs::transition diallos_q3_transition(&diallos_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q4, 4, 82140400, esd_get_flag(16009405));
OPEN_GENERIC_DIALOG_MSG(821404, diallos_q4_state, &diallos_quest_state, 82140401);
ezs::transition diallos_q4_transition(&diallos_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q5, 5, 82140500, esd_get_flag(16002730));
OPEN_GENERIC_DIALOG_MSG(821405, diallos_q5_state, &diallos_quest_state, 82140501);
ezs::transition diallos_q5_transition(&diallos_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q6, 6, 82140600, esd_get_flag(1039449305));
OPEN_GENERIC_DIALOG_MSG(821406, diallos_q6_state, &diallos_quest_state, 82140601);
ezs::transition diallos_q6_transition(&diallos_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q7, 7, 82140700, esd_get_flag(1039449315));
OPEN_GENERIC_DIALOG_MSG(821407, diallos_q7_state, &diallos_quest_state, 82140701);
ezs::transition diallos_q7_transition(&diallos_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q8, 8, 82140800, esd_get_flag(1039449285));
OPEN_GENERIC_DIALOG_MSG(821408, diallos_q8_state, &diallos_quest_state, 82140801);
ezs::transition diallos_q8_transition(&diallos_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q99, 50, 82149900, esd_get_flag(3443));
OPEN_GENERIC_DIALOG_MSG(821450, diallos_q99_state, &diallos_quest_state, 82149901);
ezs::transition diallos_q99_transition(&diallos_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 13> diallos_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, diallos_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, diallos_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, diallos_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, diallos_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, diallos_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, diallos_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, diallos_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, diallos_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, diallos_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition diallos_quest_next_transition(&diallos_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> diallos_quest_transitions = {
    &diallos_quest_next_transition};

ezs::state diallos_quest_state = {
    .id = 82140,
    .transitions = diallos_quest_transitions,
    .entry_events = diallos_quest_events,
};

std::array<ezs::transition *, 50> diallos_quest_list_transitions = {
    &diallos_q1_transition,
    &diallos_q2_transition, 
    &diallos_q3_transition, 
    &diallos_q4_transition, 
    &diallos_q5_transition, 
    &diallos_q6_transition, 
    &diallos_q7_transition, 
    &diallos_q8_transition, 
    &diallos_q99_transition, 
    &quest_log_return_transition,
};

ezs::state diallos_quest_list_state = {
    .id = 821400,
    .transitions = diallos_quest_list_transitions,
};

/*
 * Seluvis' quest submenu
 */

extern ezs::state seluvis_quest_state;
extern ezs::state seluvis_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_quest, 15, 82150000, esd_get_flag(1034509312));
ezs::transition seluvis_quest_transition(&seluvis_quest_state, evals::get_talk_list[15]);

ADD_TALK_LIST_DATA_ARGS(seluvis_q1, 1, 82150100);
OPEN_GENERIC_DIALOG_MSG(821501, seluvis_q1_state, &seluvis_quest_state, 82150101);
ezs::transition seluvis_q1_transition(&seluvis_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q2, 2, 82150200, esd_get_flag(11109919));
OPEN_GENERIC_DIALOG_MSG(821502, seluvis_q2_state, &seluvis_quest_state, 82150201);
ezs::transition seluvis_q2_transition(&seluvis_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q3, 3, 82150300, esd_get_flag(35009326));
OPEN_GENERIC_DIALOG_MSG(821503, seluvis_q3_state, &seluvis_quest_state, 82150301);
ezs::transition seluvis_q3_transition(&seluvis_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q4, 4, 82150400, esd_get_flag(11109553));
OPEN_GENERIC_DIALOG_MSG(821504, seluvis_q4_state, &seluvis_quest_state, 82150401);
ezs::transition seluvis_q4_transition(&seluvis_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q5, 5, 82150500, esd_get_flag(1034509313));
OPEN_GENERIC_DIALOG_MSG(821505, seluvis_q5_state, &seluvis_quest_state, 82150501);
ezs::transition seluvis_q5_transition(&seluvis_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q6, 6, 82150600, esd_get_flag(1034509328));
OPEN_GENERIC_DIALOG_MSG(821506, seluvis_q6_state, &seluvis_quest_state, 82150601);
ezs::transition seluvis_q6_transition(&seluvis_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q7, 7, 82150700, esd_get_flag(1034509333));
OPEN_GENERIC_DIALOG_MSG(821507, seluvis_q7_state, &seluvis_quest_state, 82150701);
ezs::transition seluvis_q7_transition(&seluvis_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q8, 8, 82150800, esd_get_flag(1034509335));
OPEN_GENERIC_DIALOG_MSG(821508, seluvis_q8_state, &seluvis_quest_state, 82150801);
ezs::transition seluvis_q8_transition(&seluvis_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q9, 9, 82150900, esd_get_flag(1034509316));
OPEN_GENERIC_DIALOG_MSG(821509, seluvis_q9_state, &seluvis_quest_state, 82150901);
ezs::transition seluvis_q9_transition(&seluvis_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q10, 10, 82151000, esd_get_flag(1034509426));
OPEN_GENERIC_DIALOG_MSG(8215010, seluvis_q10_state, &seluvis_quest_state, 82151001);
ezs::transition seluvis_q10_transition(&seluvis_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q99, 50, 82159900, esd_get_flag(1034509302));
OPEN_GENERIC_DIALOG_MSG(821550, seluvis_q99_state, &seluvis_quest_state, 82159901);
ezs::transition seluvis_q99_transition(&seluvis_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 15> seluvis_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, seluvis_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q10_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition seluvis_quest_next_transition(&seluvis_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> seluvis_quest_transitions = {
    &seluvis_quest_next_transition};

ezs::state seluvis_quest_state = {
    .id = 82150,
    .transitions = seluvis_quest_transitions,
    .entry_events = seluvis_quest_events,
};

std::array<ezs::transition *, 50> seluvis_quest_list_transitions = {
    &seluvis_q1_transition,
    &seluvis_q2_transition, 
    &seluvis_q3_transition, 
    &seluvis_q4_transition, 
    &seluvis_q5_transition, 
    &seluvis_q6_transition, 
    &seluvis_q7_transition, 
    &seluvis_q8_transition, 
    &seluvis_q9_transition, 
    &seluvis_q10_transition, 
    &seluvis_q99_transition, 
    &quest_log_return_transition,
};

ezs::state seluvis_quest_list_state = {
    .id = 821500,
    .transitions = seluvis_quest_list_transitions,
};

/*
 * Dung Eater's quest submenu
 */

extern ezs::state dungeater_quest_state;
extern ezs::state dungeater_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_quest, 16, 82160000, esd_get_flag(11109955));
ezs::transition dungeater_quest_transition(&dungeater_quest_state, evals::get_talk_list[16]);

ADD_TALK_LIST_DATA_ARGS(dungeater_q1, 1, 82160100);
OPEN_GENERIC_DIALOG_MSG(821601, dungeater_q1_state, &dungeater_quest_state, 82160101);
ezs::transition dungeater_q1_transition(&dungeater_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q2, 2, 82160200, esd_get_flag(11109957));
OPEN_GENERIC_DIALOG_MSG(821602, dungeater_q2_state, &dungeater_quest_state, 82160201);
ezs::transition dungeater_q2_transition(&dungeater_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q3, 3, 82160300, esd_get_flag(35009306));
OPEN_GENERIC_DIALOG_MSG(821603, dungeater_q3_state, &dungeater_quest_state, 82160301);
ezs::transition dungeater_q3_transition(&dungeater_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q4, 4, 82160400, esd_get_flag(4248));
OPEN_GENERIC_DIALOG_MSG(821604, dungeater_q4_state, &dungeater_quest_state, 82160401);
ezs::transition dungeater_q4_transition(&dungeater_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q5, 5, 82160500, esd_get_flag(11109959));
OPEN_GENERIC_DIALOG_MSG(821605, dungeater_q5_state, &dungeater_quest_state, 82160501);
ezs::transition dungeater_q5_transition(&dungeater_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q6, 6, 82160600, esd_get_flag(35009334));
OPEN_GENERIC_DIALOG_MSG(821606, dungeater_q6_state, &dungeater_quest_state, 82160601);
ezs::transition dungeater_q6_transition(&dungeater_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q99, 50, 82169900, esd_get_flag(1034509302));
OPEN_GENERIC_DIALOG_MSG(821650, dungeater_q99_state, &dungeater_quest_state, 82169901);
ezs::transition dungeater_q99_transition(&dungeater_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 11> dungeater_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, dungeater_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, dungeater_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, dungeater_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, dungeater_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, dungeater_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, dungeater_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, dungeater_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition dungeater_quest_next_transition(&dungeater_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> dungeater_quest_transitions = {
    &dungeater_quest_next_transition};

ezs::state dungeater_quest_state = {
    .id = 82160,
    .transitions = dungeater_quest_transitions,
    .entry_events = dungeater_quest_events,
};

std::array<ezs::transition *, 50> dungeater_quest_list_transitions = {
    &dungeater_q1_transition,
    &dungeater_q2_transition, 
    &dungeater_q3_transition, 
    &dungeater_q4_transition, 
    &dungeater_q5_transition, 
    &dungeater_q6_transition, 
    &dungeater_q99_transition, 
    &quest_log_return_transition,
};

ezs::state dungeater_quest_list_state = {
    .id = 821600,
    .transitions = dungeater_quest_list_transitions,
};

/*
 * Rogier's quest submenu
 */

extern ezs::state rogier_quest_state;
extern ezs::state rogier_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(rogier_quest, 17, 82170000, esd_or(esd_get_flag(10009617), esd_or(esd_get_flag(10009616), esd_get_flag(10009619))));
ezs::transition rogier_quest_transition(&rogier_quest_state, evals::get_talk_list[17]);

ADD_TALK_LIST_DATA_ARGS(rogier_q1, 1, 82170100);
OPEN_GENERIC_DIALOG_MSG(821701, rogier_q1_state, &rogier_quest_state, 82170101);
ezs::transition rogier_q1_transition(&rogier_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q2, 2, 82170200, esd_get_flag(11109505));
OPEN_GENERIC_DIALOG_MSG(821702, rogier_q2_state, &rogier_quest_state, 82170201);
ezs::transition rogier_q2_transition(&rogier_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q3, 3, 82170300, esd_get_flag(11109521));
OPEN_GENERIC_DIALOG_MSG(821703, rogier_q3_state, &rogier_quest_state, 82170301);
ezs::transition rogier_q3_transition(&rogier_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q4, 4, 82170400, esd_get_flag(11109017));
OPEN_GENERIC_DIALOG_MSG(821704, rogier_q4_state, &rogier_quest_state, 82170401);
ezs::transition rogier_q4_transition(&rogier_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q5, 5, 82170500, esd_get_flag(11109527));
OPEN_GENERIC_DIALOG_MSG(821705, rogier_q5_state, &rogier_quest_state, 82170501);
ezs::transition rogier_q5_transition(&rogier_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q6, 6, 82170600, esd_get_flag(11109506));
OPEN_GENERIC_DIALOG_MSG(821706, rogier_q6_state, &rogier_quest_state, 82170601);
ezs::transition rogier_q6_transition(&rogier_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q7, 7, 82170700, esd_get_flag(1034509432));
OPEN_GENERIC_DIALOG_MSG(821707, rogier_q7_state, &rogier_quest_state, 82170701);
ezs::transition rogier_q7_transition(&rogier_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q8, 8, 82170800, esd_get_flag(11109518));
OPEN_GENERIC_DIALOG_MSG(821708, rogier_q8_state, &rogier_quest_state, 82170801);
ezs::transition rogier_q8_transition(&rogier_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q9, 9, 82170900, esd_get_flag(1034509410));
OPEN_GENERIC_DIALOG_MSG(821709, rogier_q9_state, &rogier_quest_state, 82170901);
ezs::transition rogier_q9_transition(&rogier_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q10, 10, 82171000, esd_get_flag(11109532));
OPEN_GENERIC_DIALOG_MSG(8217010, rogier_q10_state, &rogier_quest_state, 82171001);
ezs::transition rogier_q10_transition(&rogier_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q99, 50, 82179900, esd_get_flag(3903));
OPEN_GENERIC_DIALOG_MSG(821750, rogier_q99_state, &rogier_quest_state, 82179901);
ezs::transition rogier_q99_transition(&rogier_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 15> rogier_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, rogier_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q10_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition rogier_quest_next_transition(&rogier_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> rogier_quest_transitions = {
    &rogier_quest_next_transition};

ezs::state rogier_quest_state = {
    .id = 82170,
    .transitions = rogier_quest_transitions,
    .entry_events = rogier_quest_events,
};

std::array<ezs::transition *, 50> rogier_quest_list_transitions = {
    &rogier_q1_transition,
    &rogier_q2_transition, 
    &rogier_q3_transition, 
    &rogier_q4_transition, 
    &rogier_q5_transition, 
    &rogier_q6_transition, 
    &rogier_q7_transition, 
    &rogier_q8_transition, 
    &rogier_q9_transition, 
    &rogier_q10_transition, 
    &rogier_q99_transition, 
    &quest_log_return_transition,
};

ezs::state rogier_quest_list_state = {
    .id = 821700,
    .transitions = rogier_quest_list_transitions,
};

/*
 * Nepheli's quest submenu
 */

extern ezs::state nepheli_quest_state;
extern ezs::state nepheli_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_quest, 18, 82180000, esd_or(esd_get_flag(10009706), esd_get_flag(11109905)));
ezs::transition nepheli_quest_transition(&nepheli_quest_state, evals::get_talk_list[18]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q1, 1, 82180100, esd_get_flag(10009706));
OPEN_GENERIC_DIALOG_MSG(821801, nepheli_q1_state, &nepheli_quest_state, 82180101);
ezs::transition nepheli_q1_transition(&nepheli_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q2, 2, 82180200, esd_and(esd_get_flag(11109905), esd_get_flag(11109905)));
OPEN_GENERIC_DIALOG_MSG(821802, nepheli_q2_state, &nepheli_quest_state, 82180201);
ezs::transition nepheli_q2_transition(&nepheli_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q3, 3, 82180300, esd_get_flag(1034429205));
OPEN_GENERIC_DIALOG_MSG(821803, nepheli_q3_state, &nepheli_quest_state, 82180301);
ezs::transition nepheli_q3_transition(&nepheli_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q4, 4, 82180400, esd_get_flag(11109923));
OPEN_GENERIC_DIALOG_MSG(821804, nepheli_q4_state, &nepheli_quest_state, 82180401);
ezs::transition nepheli_q4_transition(&nepheli_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q5, 5, 82180500, esd_get_flag(11109678));
OPEN_GENERIC_DIALOG_MSG(821805, nepheli_q5_state, &nepheli_quest_state, 82180501);
ezs::transition nepheli_q5_transition(&nepheli_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q6, 6, 82180600, esd_get_flag(11109917));
OPEN_GENERIC_DIALOG_MSG(821806, nepheli_q6_state, &nepheli_quest_state, 82180601);
ezs::transition nepheli_q6_transition(&nepheli_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q7, 7, 82180700, esd_get_flag(11109921));
OPEN_GENERIC_DIALOG_MSG(821807, nepheli_q7_state, &nepheli_quest_state, 82180701);
ezs::transition nepheli_q7_transition(&nepheli_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q8, 8, 82180800, esd_get_flag(10009716));
OPEN_GENERIC_DIALOG_MSG(821808, nepheli_q8_state, &nepheli_quest_state, 82180801);
ezs::transition nepheli_q8_transition(&nepheli_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q99, 50, 82189900, esd_get_flag(4223));
OPEN_GENERIC_DIALOG_MSG(821850, nepheli_q99_state, &nepheli_quest_state, 82189901);
ezs::transition nepheli_q99_transition(&nepheli_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 13> nepheli_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition nepheli_quest_next_transition(&nepheli_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> nepheli_quest_transitions = {
    &nepheli_quest_next_transition};

ezs::state nepheli_quest_state = {
    .id = 82180,
    .transitions = nepheli_quest_transitions,
    .entry_events = nepheli_quest_events,
};

std::array<ezs::transition *, 50> nepheli_quest_list_transitions = {
    &nepheli_q1_transition,
    &nepheli_q2_transition, 
    &nepheli_q3_transition, 
    &nepheli_q4_transition, 
    &nepheli_q5_transition, 
    &nepheli_q6_transition, 
    &nepheli_q7_transition, 
    &nepheli_q8_transition, 
    &nepheli_q99_transition, 
    &quest_log_return_transition,
};

ezs::state nepheli_quest_list_state = {
    .id = 821800,
    .transitions = nepheli_quest_list_transitions,
};

/*
 * Hyetta's quest submenu
 */

extern ezs::state hyetta_quest_state;
extern ezs::state hyetta_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_quest, 19, 82190000, esd_get_flag(1039409205));
ezs::transition hyetta_quest_transition(&hyetta_quest_state, evals::get_talk_list[19]);

ADD_TALK_LIST_DATA_ARGS(hyetta_q1, 1, 82190100);
OPEN_GENERIC_DIALOG_MSG(821901, hyetta_q1_state, &hyetta_quest_state, 82190101);
ezs::transition hyetta_q1_transition(&hyetta_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q2, 2, 82190200, esd_get_flag(1038439206));
OPEN_GENERIC_DIALOG_MSG(821902, hyetta_q2_state, &hyetta_quest_state, 82190201);
ezs::transition hyetta_q2_transition(&hyetta_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q3, 3, 82190300, esd_or(esd_compare_inventory(8126, 1, 0), esd_get_flag(1036499206)));
OPEN_GENERIC_DIALOG_MSG(821903, hyetta_q3_state, &hyetta_quest_state, 82190301);
ezs::transition hyetta_q3_transition(&hyetta_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q4, 4, 82190400, esd_get_flag(1036499206));
OPEN_GENERIC_DIALOG_MSG(821904, hyetta_q4_state, &hyetta_quest_state, 82190401);
ezs::transition hyetta_q4_transition(&hyetta_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q5, 5, 82190500, esd_get_flag(35009205));
OPEN_GENERIC_DIALOG_MSG(821905, hyetta_q5_state, &hyetta_quest_state, 82190501);
ezs::transition hyetta_q5_transition(&hyetta_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q6, 6, 82190600, esd_get_flag(35000500));
OPEN_GENERIC_DIALOG_MSG(821906, hyetta_q6_state, &hyetta_quest_state, 82190601);
ezs::transition hyetta_q6_transition(&hyetta_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q7, 7, 82190700, esd_get_flag(35000701));
OPEN_GENERIC_DIALOG_MSG(821907, hyetta_q7_state, &hyetta_quest_state, 82190701);
ezs::transition hyetta_q7_transition(&hyetta_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q99, 50, 82199900, esd_get_flag(3383));
OPEN_GENERIC_DIALOG_MSG(821950, hyetta_q99_state, &hyetta_quest_state, 82199901);
ezs::transition hyetta_q99_transition(&hyetta_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 12> hyetta_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, hyetta_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, hyetta_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, hyetta_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, hyetta_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, hyetta_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, hyetta_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, hyetta_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, hyetta_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition hyetta_quest_next_transition(&hyetta_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> hyetta_quest_transitions = {
    &hyetta_quest_next_transition};

ezs::state hyetta_quest_state = {
    .id = 82190,
    .transitions = hyetta_quest_transitions,
    .entry_events = hyetta_quest_events,
};

std::array<ezs::transition *, 50> hyetta_quest_list_transitions = {
    &hyetta_q1_transition,
    &hyetta_q2_transition, 
    &hyetta_q3_transition, 
    &hyetta_q4_transition, 
    &hyetta_q5_transition, 
    &hyetta_q6_transition, 
    &hyetta_q7_transition, 
    &hyetta_q99_transition, 
    &quest_log_return_transition,
};

ezs::state hyetta_quest_list_state = {
    .id = 821900,
    .transitions = hyetta_quest_list_transitions,
};

/*
 * Alexander's quest submenu
 */

extern ezs::state alexander_quest_state;
extern ezs::state alexander_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(alexander_quest, 20, 82200000, esd_or(esd_get_flag(1043399306), esd_or(esd_get_flag(1051369255), esd_get_flag(1051369265))));
ezs::transition alexander_quest_transition(&alexander_quest_state, evals::get_talk_list[20]);

ADD_TALK_LIST_DATA_ARGS(alexander_q1, 1, 82200100);
OPEN_GENERIC_DIALOG_MSG(822001, alexander_q1_state, &alexander_quest_state, 82200101);
ezs::transition alexander_q1_transition(&alexander_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q2, 2, 82200200, esd_get_flag(32009206));
OPEN_GENERIC_DIALOG_MSG(822002, alexander_q2_state, &alexander_quest_state, 82200201);
ezs::transition alexander_q2_transition(&alexander_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q3, 3, 82200300, esd_get_flag(1051369255));
OPEN_GENERIC_DIALOG_MSG(822003, alexander_q3_state, &alexander_quest_state, 82200301);
ezs::transition alexander_q3_transition(&alexander_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q4, 4, 82200400, esd_get_flag(1051369265));
OPEN_GENERIC_DIALOG_MSG(822004, alexander_q4_state, &alexander_quest_state, 82200401);
ezs::transition alexander_q4_transition(&alexander_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q5, 5, 82200500, esd_and(esd_get_flag(1043399306), esd_get_flag(1039449206)));
OPEN_GENERIC_DIALOG_MSG(822005, alexander_q5_state, &alexander_quest_state, 82200501);
ezs::transition alexander_q5_transition(&alexander_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q6, 6, 82200600, esd_get_flag(1035539205));
OPEN_GENERIC_DIALOG_MSG(822006, alexander_q6_state, &alexander_quest_state, 82200601);
ezs::transition alexander_q6_transition(&alexander_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q7, 7, 82200700, esd_get_flag(13009255));
OPEN_GENERIC_DIALOG_MSG(822007, alexander_q7_state, &alexander_quest_state, 82200701);
ezs::transition alexander_q7_transition(&alexander_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q8, 8, 82200800, esd_get_flag(13009257));
OPEN_GENERIC_DIALOG_MSG(822008, alexander_q8_state, &alexander_quest_state, 82200801);
ezs::transition alexander_q8_transition(&alexander_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q99, 50, 82209900, esd_or(esd_get_flag(13009260), esd_get_flag(13009256)));
OPEN_GENERIC_DIALOG_MSG(822050, alexander_q99_state, &alexander_quest_state, 82209901);
ezs::transition alexander_q99_transition(&alexander_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 13> alexander_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, alexander_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, alexander_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, alexander_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, alexander_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, alexander_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, alexander_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, alexander_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, alexander_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, alexander_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition alexander_quest_next_transition(&alexander_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> alexander_quest_transitions = {
    &alexander_quest_next_transition};

ezs::state alexander_quest_state = {
    .id = 82200,
    .transitions = alexander_quest_transitions,
    .entry_events = alexander_quest_events,
};

std::array<ezs::transition *, 50> alexander_quest_list_transitions = {
    &alexander_q1_transition,
    &alexander_q2_transition, 
    &alexander_q3_transition, 
    &alexander_q4_transition, 
    &alexander_q5_transition, 
    &alexander_q6_transition, 
    &alexander_q7_transition, 
    &alexander_q8_transition,
    &alexander_q99_transition, 
    &quest_log_return_transition,
};

ezs::state alexander_quest_list_state = {
    .id = 822000,
    .transitions = alexander_quest_list_transitions,
};

/*
 * Yura's quest submenu
 */

extern ezs::state yura_quest_state;
extern ezs::state yura_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(yura_quest, 21, 82210000, esd_get_flag(1043379260));
ezs::transition yura_quest_transition(&yura_quest_state, evals::get_talk_list[21]);

ADD_TALK_LIST_DATA_ARGS(yura_q1, 1, 82210100);
OPEN_GENERIC_DIALOG_MSG(822101, yura_q1_state, &yura_quest_state, 82210101);
ezs::transition yura_q1_transition(&yura_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q2, 2, 82210200, esd_and(esd_get_flag(1043379260), esd_and(esd_not(esd_get_flag(1043369201)), esd_get_flag(1043359257))));
OPEN_GENERIC_DIALOG_MSG(822102, yura_q2_state, &yura_quest_state, 82210201);
ezs::transition yura_q2_transition(&yura_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q3, 3, 82210300, esd_get_flag(1043379262));
OPEN_GENERIC_DIALOG_MSG(822103, yura_q3_state, &yura_quest_state, 82210301);
ezs::transition yura_q3_transition(&yura_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q4, 4, 82210400, esd_get_flag(1035469207));
OPEN_GENERIC_DIALOG_MSG(822104, yura_q4_state, &yura_quest_state, 82210401);
ezs::transition yura_q4_transition(&yura_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q5, 5, 82210500, esd_get_flag(1039529205));
OPEN_GENERIC_DIALOG_MSG(822105, yura_q5_state, &yura_quest_state, 82210501);
ezs::transition yura_q5_transition(&yura_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q6, 6, 82210600, esd_get_flag(1049539209));
OPEN_GENERIC_DIALOG_MSG(822106, yura_q6_state, &yura_quest_state, 82210601);
ezs::transition yura_q6_transition(&yura_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q99, 50, 82219900, esd_get_flag(3623));
OPEN_GENERIC_DIALOG_MSG(822150, yura_q99_state, &yura_quest_state, 82219901);
ezs::transition yura_q99_transition(&yura_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 11> yura_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, yura_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, yura_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, yura_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, yura_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, yura_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, yura_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, yura_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition yura_quest_next_transition(&yura_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> yura_quest_transitions = {
    &yura_quest_next_transition};

ezs::state yura_quest_state = {
    .id = 82210,
    .transitions = yura_quest_transitions,
    .entry_events = yura_quest_events,
};

std::array<ezs::transition *, 50> yura_quest_list_transitions = {
    &yura_q1_transition,
    &yura_q2_transition, 
    &yura_q3_transition, 
    &yura_q4_transition, 
    &yura_q5_transition, 
    &yura_q6_transition, 
    &yura_q99_transition, 
    &quest_log_return_transition,
};

ezs::state yura_quest_list_state = {
    .id = 822100,
    .transitions = yura_quest_list_transitions,
};

/*
 * Fia's quest submenu
 */

extern ezs::state fia_quest_state;
extern ezs::state fia_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(fia_quest, 22, 82220000, esd_get_flag(11109008));
ezs::transition fia_quest_transition(&fia_quest_state, evals::get_talk_list[22]);

ADD_TALK_LIST_DATA_ARGS(fia_q1, 1, 82220100);
OPEN_GENERIC_DIALOG_MSG(822201, fia_q1_state, &fia_quest_state, 82220101);
ezs::transition fia_q1_transition(&fia_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q2, 2, 82220200, esd_get_flag(11109625));
OPEN_GENERIC_DIALOG_MSG(822202, fia_q2_state, &fia_quest_state, 82220201);
ezs::transition fia_q2_transition(&fia_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q3, 3, 82220300, esd_get_flag(11109015));
OPEN_GENERIC_DIALOG_MSG(822203, fia_q3_state, &fia_quest_state, 82220301);
ezs::transition fia_q3_transition(&fia_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q4, 4, 82220400, esd_compare_inventory(8191, 1, 0));
OPEN_GENERIC_DIALOG_MSG(822204, fia_q4_state, &fia_quest_state, 82220401);
ezs::transition fia_q4_transition(&fia_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q5, 5, 82220500, esd_get_flag(12039156));
OPEN_GENERIC_DIALOG_MSG(822205, fia_q5_state, &fia_quest_state, 82220501);
ezs::transition fia_q5_transition(&fia_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q6, 6, 82220600, esd_get_flag(12039161));
OPEN_GENERIC_DIALOG_MSG(822206, fia_q6_state, &fia_quest_state, 82220601);
ezs::transition fia_q6_transition(&fia_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q7, 7, 82220700, esd_compare_inventory(8183, 1, 0));
OPEN_GENERIC_DIALOG_MSG(822207, fia_q7_state, &fia_quest_state, 82220701);
ezs::transition fia_q7_transition(&fia_q7_state, evals::get_talk_list[7]);

std::array<ezs::event, 11> fia_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, fia_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, fia_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, fia_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, fia_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, fia_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, fia_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, fia_q7_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition fia_quest_next_transition(&fia_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> fia_quest_transitions = {
    &fia_quest_next_transition};

ezs::state fia_quest_state = {
    .id = 82220,
    .transitions = fia_quest_transitions,
    .entry_events = fia_quest_events,
};

std::array<ezs::transition *, 50> fia_quest_list_transitions = {
    &fia_q1_transition,
    &fia_q2_transition, 
    &fia_q3_transition, 
    &fia_q4_transition, 
    &fia_q5_transition, 
    &fia_q6_transition, 
    &fia_q7_transition, 
    &quest_log_return_transition,
};

ezs::state fia_quest_list_state = {
    .id = 822200,
    .transitions = fia_quest_list_transitions,
};

/*
 * Varre's quest submenu
 */

extern ezs::state varre_quest_state;
extern ezs::state varre_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(varre_quest, 23, 82230000, esd_get_flag(1042369206));
ezs::transition varre_quest_transition(&varre_quest_state, evals::get_talk_list[23]);

ADD_TALK_LIST_DATA_ARGS(varre_q1, 1, 82230100);
OPEN_GENERIC_DIALOG_MSG(822301, varre_q1_state, &varre_quest_state, 82230101);
ezs::transition varre_q1_transition(&varre_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q2, 2, 82230200, esd_get_flag(1035449206));
OPEN_GENERIC_DIALOG_MSG(822302, varre_q2_state, &varre_quest_state, 82230201);
ezs::transition varre_q2_transition(&varre_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q3, 3, 82230300, esd_get_flag(1035449216));
OPEN_GENERIC_DIALOG_MSG(822303, varre_q3_state, &varre_quest_state, 82230301);
ezs::transition varre_q3_transition(&varre_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q4, 4, 82230400, esd_get_flag(1035449225));
OPEN_GENERIC_DIALOG_MSG(822304, varre_q4_state, &varre_quest_state, 82230401);
ezs::transition varre_q4_transition(&varre_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q5, 5, 82230500, esd_get_flag(12059155));
OPEN_GENERIC_DIALOG_MSG(822305, varre_q5_state, &varre_quest_state, 82230501);
ezs::transition varre_q5_transition(&varre_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q6, 6, 82230600, esd_get_flag(12059165));
OPEN_GENERIC_DIALOG_MSG(822306, varre_q6_state, &varre_quest_state, 82230601);
ezs::transition varre_q6_transition(&varre_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q99, 50, 82239900, esd_get_flag(3183));
OPEN_GENERIC_DIALOG_MSG(822350, varre_q99_state, &varre_quest_state, 82239901);
ezs::transition varre_q99_transition(&varre_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 11> varre_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, varre_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, varre_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, varre_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, varre_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, varre_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, varre_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, varre_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition varre_quest_next_transition(&varre_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> varre_quest_transitions = {
    &varre_quest_next_transition};

ezs::state varre_quest_state = {
    .id = 82230,
    .transitions = varre_quest_transitions,
    .entry_events = varre_quest_events,
};

std::array<ezs::transition *, 50> varre_quest_list_transitions = {
    &varre_q1_transition,
    &varre_q2_transition, 
    &varre_q3_transition, 
    &varre_q4_transition, 
    &varre_q5_transition, 
    &varre_q6_transition, 
    &varre_q99_transition, 
    &quest_log_return_transition,
};

ezs::state varre_quest_list_state = {
    .id = 822300,
    .transitions = varre_quest_list_transitions,
};

/*
 * Millicent's quest submenu
 */

extern ezs::state millicent_quest_state;
extern ezs::state millicent_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(millicent_quest, 24, 82240000, esd_or(esd_get_flag(1050389258), esd_get_flag(1038519256)));
ezs::transition millicent_quest_transition(&millicent_quest_state, evals::get_talk_list[24]);

ADD_TALK_LIST_DATA_ARGS(millicent_q1, 1, 82240100);
OPEN_GENERIC_DIALOG_MSG(822401, millicent_q1_state, &millicent_quest_state, 82240101);
ezs::transition millicent_q1_transition(&millicent_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q2, 2, 82240200, esd_get_flag(1038519256));
OPEN_GENERIC_DIALOG_MSG(822402, millicent_q2_state, &millicent_quest_state, 82240201);
ezs::transition millicent_q2_transition(&millicent_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q3, 3, 82240300, esd_get_flag(1038519257));
OPEN_GENERIC_DIALOG_MSG(822403, millicent_q3_state, &millicent_quest_state, 82240301);
ezs::transition millicent_q3_transition(&millicent_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q4, 4, 82240400, esd_get_flag(1042559205));
OPEN_GENERIC_DIALOG_MSG(822404, millicent_q4_state, &millicent_quest_state, 82240401);
ezs::transition millicent_q4_transition(&millicent_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q5, 5, 82240500, esd_get_flag(1051569255));
OPEN_GENERIC_DIALOG_MSG(822405, millicent_q5_state, &millicent_quest_state, 82240501);
ezs::transition millicent_q5_transition(&millicent_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q6, 6, 82240600, esd_get_flag(15009205));
OPEN_GENERIC_DIALOG_MSG(822406, millicent_q6_state, &millicent_quest_state, 82240601);
ezs::transition millicent_q6_transition(&millicent_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q7, 7, 82240700, esd_and(esd_get_flag(4183), esd_compare_inventory(1250, 1)));
OPEN_GENERIC_DIALOG_MSG(822407, millicent_q7_state, &millicent_quest_state, 82240701);
ezs::transition millicent_q7_transition(&millicent_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q8, 8, 82240800, esd_get_flag(15009210));
OPEN_GENERIC_DIALOG_MSG(822408, millicent_q8_state, &millicent_quest_state, 82240801);
ezs::transition millicent_q8_transition(&millicent_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q99, 50, 82249900, esd_get_flag(4183));
OPEN_GENERIC_DIALOG_MSG(822450, millicent_q99_state, &millicent_quest_state, 82249901);
ezs::transition millicent_q99_transition(&millicent_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 13> millicent_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, millicent_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, millicent_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, millicent_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, millicent_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, millicent_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, millicent_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, millicent_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, millicent_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, millicent_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition millicent_quest_next_transition(&millicent_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> millicent_quest_transitions = {
    &millicent_quest_next_transition};

ezs::state millicent_quest_state = {
    .id = 82240,
    .transitions = millicent_quest_transitions,
    .entry_events = millicent_quest_events,
};

std::array<ezs::transition *, 50> millicent_quest_list_transitions = {
    &millicent_q1_transition,
    &millicent_q2_transition, 
    &millicent_q3_transition, 
    &millicent_q4_transition, 
    &millicent_q5_transition, 
    &millicent_q6_transition, 
    &millicent_q7_transition, 
    &millicent_q8_transition, 
    &millicent_q99_transition, 
    &quest_log_return_transition,
};

ezs::state millicent_quest_list_state = {
    .id = 822400,
    .transitions = millicent_quest_list_transitions,
};

/*
 * Jar Bairn's quest submenu
 */

extern ezs::state jarbairn_quest_state;
extern ezs::state jarbairn_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_quest, 25, 82250000, esd_or(esd_get_flag(1039449255), esd_get_flag(1039449256)));
ezs::transition jarbairn_quest_transition(&jarbairn_quest_state, evals::get_talk_list[25]);

ADD_TALK_LIST_DATA_ARGS(jarbairn_q1, 1, 82250100);
OPEN_GENERIC_DIALOG_MSG(822501, jarbairn_q1_state, &jarbairn_quest_state, 82250101);
ezs::transition jarbairn_q1_transition(&jarbairn_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_q2, 2, 82250200, esd_get_flag(1039449263));
OPEN_GENERIC_DIALOG_MSG(822502, jarbairn_q2_state, &jarbairn_quest_state, 82250201);
ezs::transition jarbairn_q2_transition(&jarbairn_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_q3, 3, 82250300, esd_get_flag(1039449270));
OPEN_GENERIC_DIALOG_MSG(822503, jarbairn_q3_state, &jarbairn_quest_state, 82250301);
ezs::transition jarbairn_q3_transition(&jarbairn_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_q4, 4, 82250400, esd_get_flag(1039449289));
OPEN_GENERIC_DIALOG_MSG(822504, jarbairn_q4_state, &jarbairn_quest_state, 82250401);
ezs::transition jarbairn_q4_transition(&jarbairn_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_q99, 50, 82259900, esd_get_flag(3823));
OPEN_GENERIC_DIALOG_MSG(822550, jarbairn_q99_state, &jarbairn_quest_state, 82259901);
ezs::transition jarbairn_q99_transition(&jarbairn_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 9> jarbairn_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, jarbairn_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, jarbairn_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, jarbairn_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, jarbairn_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, jarbairn_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition jarbairn_quest_next_transition(&jarbairn_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> jarbairn_quest_transitions = {
    &jarbairn_quest_next_transition};

ezs::state jarbairn_quest_state = {
    .id = 82250,
    .transitions = jarbairn_quest_transitions,
    .entry_events = jarbairn_quest_events,
};

std::array<ezs::transition *, 50> jarbairn_quest_list_transitions = {
    &jarbairn_q1_transition,
    &jarbairn_q2_transition, 
    &jarbairn_q3_transition, 
    &jarbairn_q4_transition, 
    &jarbairn_q99_transition, 
    &quest_log_return_transition,
};

ezs::state jarbairn_quest_list_state = {
    .id = 822500,
    .transitions = jarbairn_quest_list_transitions,
};

/*
 * Corhyn's quest submenu
 */

extern ezs::state corhyn_quest_state;
extern ezs::state corhyn_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_quest, 26, 82260000, esd_get_flag(11109855));
ezs::transition corhyn_quest_transition(&corhyn_quest_state, evals::get_talk_list[26]);

ADD_TALK_LIST_DATA_ARGS(corhyn_q1, 1, 82260100);
OPEN_GENERIC_DIALOG_MSG(822601, corhyn_q1_state, &corhyn_quest_state, 82260101);
ezs::transition corhyn_q1_transition(&corhyn_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q2, 2, 82260200, esd_get_flag(11109859));
OPEN_GENERIC_DIALOG_MSG(822602, corhyn_q2_state, &corhyn_quest_state, 82260201);
ezs::transition corhyn_q2_transition(&corhyn_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q3, 3, 82260300, esd_get_flag(1040529255));
OPEN_GENERIC_DIALOG_MSG(822603, corhyn_q3_state, &corhyn_quest_state, 82260301);
ezs::transition corhyn_q3_transition(&corhyn_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q4, 4, 82260400, esd_or(esd_get_flag(1040529258), esd_get_flag(1040529259)));
OPEN_GENERIC_DIALOG_MSG(822604, corhyn_q4_state, &corhyn_quest_state, 82260401);
ezs::transition corhyn_q4_transition(&corhyn_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q5, 5, 82260500, esd_get_flag(1040529259));
OPEN_GENERIC_DIALOG_MSG(822605, corhyn_q5_state, &corhyn_quest_state, 82260501);
ezs::transition corhyn_q5_transition(&corhyn_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q6, 6, 82260600, esd_get_flag(1040549205));
OPEN_GENERIC_DIALOG_MSG(822606, corhyn_q6_state, &corhyn_quest_state, 82260601);
ezs::transition corhyn_q6_transition(&corhyn_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q7, 7, 82260700, esd_get_flag(11109881));
OPEN_GENERIC_DIALOG_MSG(822607, corhyn_q7_state, &corhyn_quest_state, 82260701);
ezs::transition corhyn_q7_transition(&corhyn_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q8, 8, 82260800, esd_get_flag(11009555));
OPEN_GENERIC_DIALOG_MSG(822608, corhyn_q8_state, &corhyn_quest_state, 82260801);
ezs::transition corhyn_q8_transition(&corhyn_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q9, 9, 82260900, esd_get_flag(1051569355));
OPEN_GENERIC_DIALOG_MSG(822609, corhyn_q9_state, &corhyn_quest_state, 82260901);
ezs::transition corhyn_q9_transition(&corhyn_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q10, 10, 82261000, esd_compare_inventory(8182, 1));
OPEN_GENERIC_DIALOG_MSG(8226010, corhyn_q10_state, &corhyn_quest_state, 82261001);
ezs::transition corhyn_q10_transition(&corhyn_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q99, 50, 82269900, esd_get_flag(4203));
OPEN_GENERIC_DIALOG_MSG(822650, corhyn_q99_state, &corhyn_quest_state, 82269901);
ezs::transition corhyn_q99_transition(&corhyn_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 15> corhyn_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, corhyn_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q10_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition corhyn_quest_next_transition(&corhyn_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> corhyn_quest_transitions = {
    &corhyn_quest_next_transition};

ezs::state corhyn_quest_state = {
    .id = 82260,
    .transitions = corhyn_quest_transitions,
    .entry_events = corhyn_quest_events,
};

std::array<ezs::transition *, 50> corhyn_quest_list_transitions = {
    &corhyn_q1_transition,
    &corhyn_q2_transition, 
    &corhyn_q3_transition, 
    &corhyn_q4_transition, 
    &corhyn_q5_transition, 
    &corhyn_q6_transition, 
    &corhyn_q7_transition, 
    &corhyn_q8_transition, 
    &corhyn_q9_transition, 
    &corhyn_q10_transition, 
    &corhyn_q99_transition, 
    &quest_log_return_transition,
};

ezs::state corhyn_quest_list_state = {
    .id = 822600,
    .transitions = corhyn_quest_list_transitions,
};

/*
 * Latenna's quest submenu
 */

extern ezs::state latenna_quest_state;
extern ezs::state latenna_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(latenna_quest, 27, 82270000, esd_get_flag(1035429209));
ezs::transition latenna_quest_transition(&latenna_quest_state, evals::get_talk_list[27]);

ADD_TALK_LIST_DATA_ARGS(latenna_q1, 1, 82270100);
OPEN_GENERIC_DIALOG_MSG(822701, latenna_q1_state, &latenna_quest_state, 82270101);
ezs::transition latenna_q1_transition(&latenna_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(latenna_q2, 2, 82270200, esd_get_flag(1036419207));
OPEN_GENERIC_DIALOG_MSG(822702, latenna_q2_state, &latenna_quest_state, 82270201);
ezs::transition latenna_q2_transition(&latenna_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(latenna_q3, 3, 82270300, esd_or(esd_get_flag(1051569301), esd_get_flag(1051562720)));
OPEN_GENERIC_DIALOG_MSG(822703, latenna_q3_state, &latenna_quest_state, 82270301);
ezs::transition latenna_q3_transition(&latenna_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(latenna_q4, 4, 82270400, esd_get_flag(1047589206));
OPEN_GENERIC_DIALOG_MSG(822704, latenna_q4_state, &latenna_quest_state, 82270401);
ezs::transition latenna_q4_transition(&latenna_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(latenna_q99, 50, 82279900, esd_get_flag(4103));
OPEN_GENERIC_DIALOG_MSG(822750, latenna_q99_state, &latenna_quest_state, 82279901);
ezs::transition latenna_q99_transition(&latenna_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 9> latenna_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, latenna_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, latenna_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, latenna_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, latenna_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, latenna_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition latenna_quest_next_transition(&latenna_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> latenna_quest_transitions = {
    &latenna_quest_next_transition};

ezs::state latenna_quest_state = {
    .id = 82270,
    .transitions = latenna_quest_transitions,
    .entry_events = latenna_quest_events,
};

std::array<ezs::transition *, 50> latenna_quest_list_transitions = {
    &latenna_q1_transition,
    &latenna_q2_transition, 
    &latenna_q3_transition, 
    &latenna_q4_transition, 
    &latenna_q99_transition, 
    &quest_log_return_transition,
};

ezs::state latenna_quest_list_state = {
    .id = 822700,
    .transitions = latenna_quest_list_transitions,
};

/*
 * Bernahl's quest submenu
 */

extern ezs::state bernahl_quest_state;
extern ezs::state bernahl_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_quest, 28, 82280000, esd_or(esd_get_flag(1042382713), esd_or(esd_get_flag(16009455), esd_get_flag(16009456))));
ezs::transition bernahl_quest_transition(&bernahl_quest_state, evals::get_talk_list[28]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q1, 1, 82280100, esd_get_flag(1042382713));
OPEN_GENERIC_DIALOG_MSG(822801, bernahl_q1_state, &bernahl_quest_state, 82280101);
ezs::transition bernahl_q1_transition(&bernahl_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q2, 2, 82280200, esd_or(esd_get_flag(16009455), esd_get_flag(16009456)));
OPEN_GENERIC_DIALOG_MSG(822802, bernahl_q2_state, &bernahl_quest_state, 82280201);
ezs::transition bernahl_q2_transition(&bernahl_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q3, 3, 82280300, esd_get_flag(16009457));
OPEN_GENERIC_DIALOG_MSG(822803, bernahl_q3_state, &bernahl_quest_state, 82280301);
ezs::transition bernahl_q3_transition(&bernahl_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q4, 4, 82280400, esd_get_flag(16009458));
OPEN_GENERIC_DIALOG_MSG(822804, bernahl_q4_state, &bernahl_quest_state, 82280401);
ezs::transition bernahl_q4_transition(&bernahl_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q5, 5, 82280500, esd_get_flag(7605));
OPEN_GENERIC_DIALOG_MSG(822805, bernahl_q5_state, &bernahl_quest_state, 82280501);
ezs::transition bernahl_q5_transition(&bernahl_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q6, 6, 82280600, esd_get_flag(16009461));
OPEN_GENERIC_DIALOG_MSG(822806, bernahl_q6_state, &bernahl_quest_state, 82280601);
ezs::transition bernahl_q6_transition(&bernahl_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q7, 7, 82280700, esd_get_flag(16009460));
OPEN_GENERIC_DIALOG_MSG(822807, bernahl_q7_state, &bernahl_quest_state, 82280701);
ezs::transition bernahl_q7_transition(&bernahl_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q8, 8, 82280800, esd_and(esd_get_flag(3883), esd_compare_inventory(2080, 1)));
OPEN_GENERIC_DIALOG_MSG(822808, bernahl_q8_state, &bernahl_quest_state, 82280801);
ezs::transition bernahl_q8_transition(&bernahl_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q99, 50, 82289900, esd_get_flag(3883));
OPEN_GENERIC_DIALOG_MSG(822850, bernahl_q99_state, &bernahl_quest_state, 82289901);
ezs::transition bernahl_q99_transition(&bernahl_q99_state, evals::get_talk_list[50]);

std::array<ezs::event, 13> bernahl_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_q99_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition bernahl_quest_next_transition(&bernahl_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> bernahl_quest_transitions = {
    &bernahl_quest_next_transition};

ezs::state bernahl_quest_state = {
    .id = 82280,
    .transitions = bernahl_quest_transitions,
    .entry_events = bernahl_quest_events,
};

std::array<ezs::transition *, 50> bernahl_quest_list_transitions = {
    &bernahl_q1_transition,
    &bernahl_q2_transition, 
    &bernahl_q3_transition, 
    &bernahl_q4_transition, 
    &bernahl_q5_transition, 
    &bernahl_q6_transition, 
    &bernahl_q7_transition, 
    &bernahl_q8_transition, 
    &bernahl_q99_transition, 
    &quest_log_return_transition,
};

ezs::state bernahl_quest_list_state = {
    .id = 822800,
    .transitions = bernahl_quest_list_transitions,
};

/*
 * Ansbach's quest submenu
 */

extern ezs::state ansbach_quest_state;
extern ezs::state ansbach_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_quest, 29, 82290000, esd_or(esd_get_flag(2046429355), esd_get_flag(2045429206)));
ezs::transition ansbach_quest_transition(&ansbach_quest_state, evals::get_talk_list[29]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q1, 1, 82290100, esd_get_flag(2046429355));
OPEN_GENERIC_DIALOG_MSG(822901, ansbach_q1_state, &ansbach_quest_state, 82290101);
ezs::transition ansbach_q1_transition(&ansbach_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q2, 2, 82290200, esd_get_flag(2045429206));
OPEN_GENERIC_DIALOG_MSG(822902, ansbach_q2_state, &ansbach_quest_state, 82290201);
ezs::transition ansbach_q2_transition(&ansbach_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q3, 3, 82290300, esd_get_flag(2046429365));
OPEN_GENERIC_DIALOG_MSG(822903, ansbach_q3_state, &ansbach_quest_state, 82290301);
ezs::transition ansbach_q3_transition(&ansbach_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q4, 4, 82290400, esd_get_flag(2045429213));
OPEN_GENERIC_DIALOG_MSG(822904, ansbach_q4_state, &ansbach_quest_state, 82290401);
ezs::transition ansbach_q4_transition(&ansbach_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q5, 5, 82290500, esd_get_flag(21019305));
OPEN_GENERIC_DIALOG_MSG(822905, ansbach_q5_state, &ansbach_quest_state, 82290501);
ezs::transition ansbach_q5_transition(&ansbach_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q6, 6, 82290600, esd_get_flag(21019316));
OPEN_GENERIC_DIALOG_MSG(822906, ansbach_q6_state, &ansbach_quest_state, 82290601);
ezs::transition ansbach_q6_transition(&ansbach_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q7, 7, 82290700, esd_get_flag(21019360));
OPEN_GENERIC_DIALOG_MSG(822907, ansbach_q7_state, &ansbach_quest_state, 82290701);
ezs::transition ansbach_q7_transition(&ansbach_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q8, 8, 82290800, esd_or(esd_compare_inventory(2008014, 1), esd_get_flag(21019310)));
OPEN_GENERIC_DIALOG_MSG(822908, ansbach_q8_state, &ansbach_quest_state, 82290801);
ezs::transition ansbach_q8_transition(&ansbach_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q9, 9, 82290900, esd_get_flag(21019310));
OPEN_GENERIC_DIALOG_MSG(822909, ansbach_q9_state, &ansbach_quest_state, 82290901);
ezs::transition ansbach_q9_transition(&ansbach_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q10, 10, 82291000, esd_get_flag(21019323));
OPEN_GENERIC_DIALOG_MSG(8229010, ansbach_q10_state, &ansbach_quest_state, 82291001);
ezs::transition ansbach_q10_transition(&ansbach_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q11, 11, 82291100, esd_get_flag(21019363));
OPEN_GENERIC_DIALOG_MSG(822911, ansbach_q11_state, &ansbach_quest_state, 82291101);
ezs::transition ansbach_q11_transition(&ansbach_q11_state, evals::get_talk_list[11]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q12, 12, 82291200, esd_get_flag(21019321));
OPEN_GENERIC_DIALOG_MSG(822912, ansbach_q12_state, &ansbach_quest_state, 82291201);
ezs::transition ansbach_q12_transition(&ansbach_q12_state, evals::get_talk_list[12]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q13, 13, 82291300, esd_get_flag(20019211));
OPEN_GENERIC_DIALOG_MSG(822913, ansbach_q13_state, &ansbach_quest_state, 82291301);
ezs::transition ansbach_q13_transition(&ansbach_q13_state, evals::get_talk_list[13]);

std::array<ezs::event, 17> ansbach_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q10_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q11_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q12_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_q13_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition ansbach_quest_next_transition(&ansbach_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> ansbach_quest_transitions = {
    &ansbach_quest_next_transition};

ezs::state ansbach_quest_state = {
    .id = 82290,
    .transitions = ansbach_quest_transitions,
    .entry_events = ansbach_quest_events,
};

std::array<ezs::transition *, 50> ansbach_quest_list_transitions = {
    &ansbach_q1_transition,
    &ansbach_q2_transition, 
    &ansbach_q3_transition, 
    &ansbach_q4_transition, 
    &ansbach_q5_transition, 
    &ansbach_q6_transition, 
    &ansbach_q7_transition, 
    &ansbach_q8_transition, 
    &ansbach_q9_transition, 
    &ansbach_q10_transition, 
    &ansbach_q11_transition, 
    &ansbach_q12_transition, 
    &ansbach_q13_transition, 
    &quest_log_return_transition,
};

ezs::state ansbach_quest_list_state = {
    .id = 822900,
    .transitions = ansbach_quest_list_transitions,
};

/*
 * Hornsent's quest submenu
 */

extern ezs::state hornsent_quest_state;
extern ezs::state hornsent_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_quest, 31, 82310000, esd_or(esd_get_flag(2048459278), esd_and(esd_get_flag(2046429210), esd_and(esd_not(esd_get_flag(2048459278)), esd_not(esd_get_flag(21019205))))));
ezs::transition hornsent_quest_transition(&hornsent_quest_state, evals::get_talk_list[31]);

ADD_TALK_LIST_DATA_ARGS(hornsent_q1, 1, 82310100);
OPEN_GENERIC_DIALOG_MSG(823101, hornsent_q1_state, &hornsent_quest_state, 82310101);
ezs::transition hornsent_q1_transition(&hornsent_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_q2, 2, 82310200, esd_get_flag(2048459278));
OPEN_GENERIC_DIALOG_MSG(823102, hornsent_q2_state, &hornsent_quest_state, 82310201);
ezs::transition hornsent_q2_transition(&hornsent_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_q3, 3, 82310300, esd_get_flag(2048459261));
OPEN_GENERIC_DIALOG_MSG(823103, hornsent_q3_state, &hornsent_quest_state, 82310301);
ezs::transition hornsent_q3_transition(&hornsent_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_q4, 4, 82310400, esd_get_flag(21012703));
OPEN_GENERIC_DIALOG_MSG(823104, hornsent_q4_state, &hornsent_quest_state, 82310401);
ezs::transition hornsent_q4_transition(&hornsent_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_q5, 5, 82310500, esd_get_flag(21019207));
OPEN_GENERIC_DIALOG_MSG(823105, hornsent_q5_state, &hornsent_quest_state, 82310501);
ezs::transition hornsent_q5_transition(&hornsent_q5_state, evals::get_talk_list[5]);

std::array<ezs::event, 9> hornsent_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, hornsent_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, hornsent_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, hornsent_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, hornsent_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, hornsent_q5_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition hornsent_quest_next_transition(&hornsent_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> hornsent_quest_transitions = {
    &hornsent_quest_next_transition};

ezs::state hornsent_quest_state = {
    .id = 82310,
    .transitions = hornsent_quest_transitions,
    .entry_events = hornsent_quest_events,
};

std::array<ezs::transition *, 50> hornsent_quest_list_transitions = {
    &hornsent_q1_transition,
    &hornsent_q2_transition, 
    &hornsent_q3_transition, 
    &hornsent_q4_transition, 
    &hornsent_q5_transition, 
    &quest_log_return_transition,
};

ezs::state hornsent_quest_list_state = {
    .id = 823100,
    .transitions = hornsent_quest_list_transitions,
};

/*
 * Queelign's quest submenu
 */

extern ezs::state queelign_quest_state;
extern ezs::state queelign_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(queelign_quest, 32, 82320000, esd_get_flag(21009212));
ezs::transition queelign_quest_transition(&queelign_quest_state, evals::get_talk_list[32]);

ADD_TALK_LIST_DATA_ARGS(queelign_q1, 1, 82320100);
OPEN_GENERIC_DIALOG_MSG(823201, queelign_q1_state, &queelign_quest_state, 82320101);
ezs::transition queelign_q1_transition(&queelign_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(queelign_q2, 2, 82320200, esd_get_flag(21009210));
OPEN_GENERIC_DIALOG_MSG(823202, queelign_q2_state, &queelign_quest_state, 82320201);
ezs::transition queelign_q2_transition(&queelign_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(queelign_q3, 3, 82320300, esd_get_flag(21009211));
OPEN_GENERIC_DIALOG_MSG(823203, queelign_q3_state, &queelign_quest_state, 82320301);
ezs::transition queelign_q3_transition(&queelign_q3_state, evals::get_talk_list[3]);

std::array<ezs::event, 7> queelign_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, queelign_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, queelign_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, queelign_q3_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition queelign_quest_next_transition(&queelign_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> queelign_quest_transitions = {
    &queelign_quest_next_transition};

ezs::state queelign_quest_state = {
    .id = 82320,
    .transitions = queelign_quest_transitions,
    .entry_events = queelign_quest_events,
};

std::array<ezs::transition *, 50> queelign_quest_list_transitions = {
    &queelign_q1_transition,
    &queelign_q2_transition, 
    &queelign_q3_transition, 
    &quest_log_return_transition,
};

ezs::state queelign_quest_list_state = {
    .id = 823200,
    .transitions = queelign_quest_list_transitions,
};

/*
 * Ymir's quest submenu
 */

extern ezs::state ymir_quest_state;
extern ezs::state ymir_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(ymir_quest, 33, 82330000, esd_get_flag(2051459220));
ezs::transition ymir_quest_transition(&ymir_quest_state, evals::get_talk_list[33]);

ADD_TALK_LIST_DATA_ARGS(ymir_q1, 1, 82330100);
OPEN_GENERIC_DIALOG_MSG(823301, ymir_q1_state, &ymir_quest_state, 82330101);
ezs::transition ymir_q1_transition(&ymir_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q2, 2, 82330200, esd_get_flag(2050400600));
OPEN_GENERIC_DIALOG_MSG(823302, ymir_q2_state, &ymir_quest_state, 82330201);
ezs::transition ymir_q2_transition(&ymir_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q3, 3, 82330300, esd_or(esd_get_flag(2051459235), esd_get_flag(2051459237)));
OPEN_GENERIC_DIALOG_MSG(823303, ymir_q3_state, &ymir_quest_state, 82330301);
ezs::transition ymir_q3_transition(&ymir_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q4, 4, 82330400, esd_get_flag(2053460600));
OPEN_GENERIC_DIALOG_MSG(823304, ymir_q4_state, &ymir_quest_state, 82330401);
ezs::transition ymir_q4_transition(&ymir_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q5, 5, 82330500, esd_or(esd_get_flag(2051459208), esd_get_flag(2051459247)));
OPEN_GENERIC_DIALOG_MSG(823305, ymir_q5_state, &ymir_quest_state, 82330501);
ezs::transition ymir_q5_transition(&ymir_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q6, 6, 82330600, esd_or(esd_get_flag(4326), esd_get_flag(2051459234)));
OPEN_GENERIC_DIALOG_MSG(823306, ymir_q6_state, &ymir_quest_state, 82330601);
ezs::transition ymir_q6_transition(&ymir_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q7, 7, 82330700, esd_get_flag(2051459743));
OPEN_GENERIC_DIALOG_MSG(823307, ymir_q7_state, &ymir_quest_state, 82330701);
ezs::transition ymir_q7_transition(&ymir_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q8, 8, 82330800, esd_get_flag(2051459744));
OPEN_GENERIC_DIALOG_MSG(823308, ymir_q8_state, &ymir_quest_state, 82330801);
ezs::transition ymir_q8_transition(&ymir_q8_state, evals::get_talk_list[8]);

std::array<ezs::event, 12> ymir_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, ymir_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, ymir_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, ymir_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, ymir_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, ymir_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, ymir_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, ymir_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, ymir_q8_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition ymir_quest_next_transition(&ymir_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> ymir_quest_transitions = {
    &ymir_quest_next_transition};

ezs::state ymir_quest_state = {
    .id = 82330,
    .transitions = ymir_quest_transitions,
    .entry_events = ymir_quest_events,
};

std::array<ezs::transition *, 50> ymir_quest_list_transitions = {
    &ymir_q1_transition,
    &ymir_q2_transition, 
    &ymir_q3_transition, 
    &ymir_q4_transition, 
    &ymir_q5_transition, 
    &ymir_q6_transition, 
    &ymir_q7_transition, 
    &ymir_q8_transition,  
    &quest_log_return_transition,
};

ezs::state ymir_quest_list_state = {
    .id = 823300,
    .transitions = ymir_quest_list_transitions,
};

/*
 * Igon's quest submenu
 */

extern ezs::state igon_quest_state;
extern ezs::state igon_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(igon_quest, 34, 82340000, esd_get_flag(2048429208));
ezs::transition igon_quest_transition(&igon_quest_state, evals::get_talk_list[34]);

ADD_TALK_LIST_DATA_ARGS(igon_q1, 1, 82340100);
OPEN_GENERIC_DIALOG_MSG(823401, igon_q1_state, &igon_quest_state, 82340101);
ezs::transition igon_q1_transition(&igon_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(igon_q2, 2, 82340200, esd_get_flag(2049399706));
OPEN_GENERIC_DIALOG_MSG(823402, igon_q2_state, &igon_quest_state, 82340201);
ezs::transition igon_q2_transition(&igon_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(igon_q3, 3, 82340300, esd_get_flag(2052409207));
OPEN_GENERIC_DIALOG_MSG(823403, igon_q3_state, &igon_quest_state, 82340301);
ezs::transition igon_q3_transition(&igon_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(igon_q4, 4, 82340400, esd_get_flag(2054399208));
OPEN_GENERIC_DIALOG_MSG(823404, igon_q4_state, &igon_quest_state, 82340401);
ezs::transition igon_q4_transition(&igon_q4_state, evals::get_talk_list[4]);

std::array<ezs::event, 8> igon_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data, igon_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, igon_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, igon_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, igon_q4_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition igon_quest_next_transition(&igon_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> igon_quest_transitions = {
    &igon_quest_next_transition};

ezs::state igon_quest_state = {
    .id = 82340,
    .transitions = igon_quest_transitions,
    .entry_events = igon_quest_events,
};

std::array<ezs::transition *, 50> igon_quest_list_transitions = {
    &igon_q1_transition,
    &igon_q2_transition, 
    &igon_q3_transition, 
    &igon_q4_transition, 
    &quest_log_return_transition,
};

ezs::state igon_quest_list_state = {
    .id = 823400,
    .transitions = igon_quest_list_transitions,
};

/*
 * St. Trina's quest submenu
 */

extern ezs::state trina_quest_state;
extern ezs::state trina_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(trina_quest, 35, 82350000, esd_get_flag(22009255));
ezs::transition trina_quest_transition(&trina_quest_state, evals::get_talk_list[35]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q1, 1, 82350100, esd_get_flag(2048439223));
OPEN_GENERIC_DIALOG_MSG(823501, trina_q1_state, &trina_quest_state, 82350101);
ezs::transition trina_q1_transition(&trina_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q2, 2, 82350200, esd_get_flag(22009255));
OPEN_GENERIC_DIALOG_MSG(823502, trina_q2_state, &trina_quest_state, 82350201);
ezs::transition trina_q2_transition(&trina_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q3, 3, 82350300, esd_get_flag(2048439228));
OPEN_GENERIC_DIALOG_MSG(823503, trina_q3_state, &trina_quest_state, 82350301);
ezs::transition trina_q3_transition(&trina_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q4, 4, 82350400, esd_get_flag(22009218));
OPEN_GENERIC_DIALOG_MSG(823504, trina_q4_state, &trina_quest_state, 82350401);
ezs::transition trina_q4_transition(&trina_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q5, 5, 82350500, esd_get_flag(22000710));
OPEN_GENERIC_DIALOG_MSG(823505, trina_q5_state, &trina_quest_state, 82350501);
ezs::transition trina_q5_transition(&trina_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q6, 6, 82350600, esd_get_flag(22009221));
OPEN_GENERIC_DIALOG_MSG(823506, trina_q6_state, &trina_quest_state, 82350601);
ezs::transition trina_q6_transition(&trina_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q7, 7, 82350700, esd_get_flag(22009222));
OPEN_GENERIC_DIALOG_MSG(823507, trina_q7_state, &trina_quest_state, 82350701);
ezs::transition trina_q7_transition(&trina_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q8, 8, 82350800, esd_get_flag(22009231));
OPEN_GENERIC_DIALOG_MSG(823508, trina_q8_state, &trina_quest_state, 82350801);
ezs::transition trina_q8_transition(&trina_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q9, 9, 82350900, esd_get_flag(22009235));
OPEN_GENERIC_DIALOG_MSG(823509, trina_q9_state, &trina_quest_state, 82350901);
ezs::transition trina_q9_transition(&trina_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q10, 10, 82351000, esd_get_flag(22009239));
OPEN_GENERIC_DIALOG_MSG(8235010, trina_q10_state, &trina_quest_state, 82351001);
ezs::transition trina_q10_transition(&trina_q10_state, evals::get_talk_list[10]);

std::array<ezs::event, 14> trina_quest_events = {
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q1_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q2_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q3_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q4_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q5_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q6_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q7_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q8_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q9_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_q10_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition trina_quest_next_transition(&trina_quest_list_state,
                                                           evals::talk_menu_closed_evaluator);

std::array<ezs::transition *, 1> trina_quest_transitions = {
    &trina_quest_next_transition};

ezs::state trina_quest_state = {
    .id = 82350,
    .transitions = trina_quest_transitions,
    .entry_events = trina_quest_events,
};

std::array<ezs::transition *, 50> trina_quest_list_transitions = {
    &trina_q1_transition,
    &trina_q2_transition, 
    &trina_q3_transition, 
    &trina_q4_transition, 
    &trina_q5_transition, 
    &trina_q6_transition, 
    &trina_q7_transition, 
    &trina_q8_transition, 
    &trina_q9_transition, 
    &trina_q10_transition, 
    &quest_log_return_transition,
};

ezs::state trina_quest_list_state = {
    .id = 823500,
    .transitions = trina_quest_list_transitions,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * "Quest log list" submenu
 */

std::array<ezs::event, 38> quest_log_events = {        //DO NOT CHANGE NUMBER, MUST BE EXACTLY THE SAME NUMBER AS OPTIONS, NOT ONE MORE
    ezs::event{talk_comm::close_shop_message},
    ezs::event{talk_comm::clear_talk_list_data},
    ezs::event{talk_comm::add_talk_list_data_if, alexander_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, blaidd_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, bernahl_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, boc_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, corhyn_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, d_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, diallos_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, dungeater_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, fia_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, gowry_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, gurranq_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, hyetta_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, irina_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, kenneth_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, latenna_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, millicent_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, nepheli_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, patches_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, ranni_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, roderika_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, rogier_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, rya_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, sellen_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, seluvis_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, thops_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, varre_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, yura_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, dlc_separator_args},
    ezs::event{talk_comm::add_talk_list_data_if, ansbach_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, hornsent_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, queelign_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, ymir_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, igon_quest_args},
    ezs::event{talk_comm::add_talk_list_data_if, trina_quest_args},
    ezs::event{talk_comm::add_talk_list_data, leave_args},
    ezs::event{talk_comm::show_shop_message,
                         show_generic_dialog_shop_message_arg_list},
};
ezs::transition quest_log_next_transition(&quest_log_list_state,
                                                           evals::talk_menu_closed_evaluator);
std::array<ezs::transition *, 1> quest_log_transitions = {
    &quest_log_next_transition};
ezs::state quest_log_state = {
    .id = 99000,
    .transitions = quest_log_transitions,
    .entry_events = quest_log_events,
};

std::array<ezs::transition *, 50> quest_log_list_transitions = {
    &roderika_quest_transition,
    &sellen_quest_transition,
    &irina_quest_transition,
    &kenneth_quest_transition,
    &boc_quest_transition,
    &blaidd_quest_transition,
    &thops_quest_transition,
    &patches_quest_transition,
    &ranni_quest_transition,
    &rya_quest_transition,
    &gowry_quest_transition,
    &d_quest_transition,
    &gurranq_quest_transition,
    &diallos_quest_transition,
    &seluvis_quest_transition,
    &dungeater_quest_transition,
    &rogier_quest_transition,
    &nepheli_quest_transition,
    &hyetta_quest_transition,
    &alexander_quest_transition,
    &yura_quest_transition,
    &fia_quest_transition,
    &varre_quest_transition,
    &millicent_quest_transition,
    &jarbairn_quest_transition,
    &corhyn_quest_transition,
    &latenna_quest_transition,
    &bernahl_quest_transition,
    &ansbach_quest_transition,
    &hornsent_quest_transition,
    &queelign_quest_transition,
    &ymir_quest_transition,
    &igon_quest_transition,
    &trina_quest_transition,
    &dlc_separator_transition,
    &main_menu_return_transition,
};

ezs::state quest_log_list_state = {
    .id = 99900,
    .transitions = quest_log_list_transitions,
};

#undef ADD_TALK_LIST_DATA_ARGS
#undef OPEN_GENERIC_DIALOG_MSG

};
