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
const int questlog_main_index = 87;

// Reference for debug
/*static constexpr unsigned int kale_alive_flag_id = 4700;
static constexpr unsigned int kale_hostile_flag_id = 4701;
static constexpr unsigned int kale_dead_flag_id = 4703;*/

ADD_TALK_LIST_DATA_ARGS(quest_log, questlog_main_index, 87000000);   // Quest Log
static ezs::transition quest_log_transition(&quest_log_state, evals::get_talk_list[questlog_main_index]);
//static ezs::transition quest_log_transition(&quest_log_state, (esd_get_talk_list(questlog_main_index)));

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

ADD_TALK_LIST_IF_DATA_ARGS(dlc_separator, 98, 87000100, show_separator);   // Quest Log
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

QUEST_BUILDER("irina", 8701, 3, esd_get_flag(1045349207), conditions);*/


extern ezs::state irina_quest_state;
extern ezs::state irina_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(irina_quest, 3, 87010000, esd_get_flag(1045349207));
//ADD_TALK_LIST_IF_DATA_ARGS(irina_quest, 3, 87010000, esd_or(esd_get_flag(4700), esd_compare_inventory(2962, 1)));
ezs::transition irina_quest_transition(&irina_quest_state, evals::get_talk_list[3]);

ADD_TALK_LIST_DATA_ARGS(irina_q1, 1, 87010100);
OPEN_GENERIC_DIALOG_MSG(870101, irina_q1_state, &irina_quest_state, 87010101);
ezs::transition irina_q1_transition(&irina_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(irina_q2, 2, 87010200, esd_get_flag(1043319206));
OPEN_GENERIC_DIALOG_MSG(870102, irina_q2_state, &irina_quest_state, 87010201);
ezs::transition irina_q2_transition(&irina_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(irina_q3, 3, 87010300, esd_get_flag(1045349255));
OPEN_GENERIC_DIALOG_MSG(870103, irina_q3_state, &irina_quest_state, 87010301);
ezs::transition irina_q3_transition(&irina_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(irina_q4, 4, 87010400, esd_get_flag(1045349252));
OPEN_GENERIC_DIALOG_MSG(870104, irina_q4_state, &irina_quest_state, 87010401);
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
    .id = 8701,
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
    .id = 87010,
    .transitions = irina_quest_list_transitions,
};

/*
 * Roderika's quest submenu
 */

extern ezs::state roderika_quest_state;
extern ezs::state roderika_quest_list_state;

//ADD_TALK_LIST_IF_DATA_ARGS(roderika_quest, 1, 87020000, esd_or(esd_or(esd_get_flag(1041389406), esd_get_flag(1041382735)), esd_get_flag(11109255)));
ADD_TALK_LIST_IF_DATA_ARGS(roderika_quest, 1, 87020000, esd_and(esd_get_flag(4700), esd_compare_inventory(2962, 1)));
ezs::transition roderika_quest_transition(&roderika_quest_state, evals::get_talk_list[1]);

ADD_TALK_LIST_DATA_ARGS(roderika_q1, 1, 87020100);
OPEN_GENERIC_DIALOG_MSG(870201, roderika_q1_state, &roderika_quest_state, 87020101);
ezs::transition roderika_q1_transition(&roderika_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q2, 2, 87020200, esd_or(esd_get_flag(1041382735), esd_get_flag(11109255)));
OPEN_GENERIC_DIALOG_MSG(870202, roderika_q2_state, &roderika_quest_state, 87020201);
ezs::transition roderika_q2_transition(&roderika_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q3, 3, 87020300, esd_get_flag(11109210));
OPEN_GENERIC_DIALOG_MSG(870203, roderika_q3_state, &roderika_quest_state, 87020301);
ezs::transition roderika_q3_transition(&roderika_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q4, 4, 87020400, esd_get_flag(11109256));
OPEN_GENERIC_DIALOG_MSG(870204, roderika_q4_state, &roderika_quest_state, 87020401);
ezs::transition roderika_q4_transition(&roderika_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q5, 5, 87020500, esd_get_flag(11109219));
OPEN_GENERIC_DIALOG_MSG(870205, roderika_q5_state, &roderika_quest_state, 87020501);
ezs::transition roderika_q5_transition(&roderika_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(roderika_q6, 6, 87020600, esd_get_flag(3708));
OPEN_GENERIC_DIALOG_MSG(870206, roderika_q6_state, &roderika_quest_state, 87020601);
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
    .id = 8702,
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
    .id = 87020,
    .transitions = roderika_quest_list_transitions,
};

/*
 * Sorceress Sellen's quest submenu
 */

extern ezs::state sellen_quest_state;
extern ezs::state sellen_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(sellen_quest, 2, 87030000, esd_get_flag(1044369227));
ezs::transition sellen_quest_transition(&sellen_quest_state, evals::get_talk_list[2]);

ADD_TALK_LIST_DATA_ARGS(sellen_q1, 1, 87030100);
OPEN_GENERIC_DIALOG_MSG(870301, sellen_q1_state, &sellen_quest_state, 87030101);
ezs::transition sellen_q1_transition(&sellen_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q2, 2, 87030200, esd_get_flag(1044369219));
OPEN_GENERIC_DIALOG_MSG(870302, sellen_q2_state, &sellen_quest_state, 87030201);
ezs::transition sellen_q2_transition(&sellen_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q3, 3, 87030300, esd_get_flag(1044369222));
OPEN_GENERIC_DIALOG_MSG(870303, sellen_q3_state, &sellen_quest_state, 87030301);
ezs::transition sellen_q3_transition(&sellen_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q4, 4, 87030400, esd_get_flag(1041339256));
OPEN_GENERIC_DIALOG_MSG(870304, sellen_q4_state, &sellen_quest_state, 87030401);
ezs::transition sellen_q4_transition(&sellen_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q5, 5, 87030500, esd_get_flag(1034509255));
OPEN_GENERIC_DIALOG_MSG(870305, sellen_q5_state, &sellen_quest_state, 87030501);
ezs::transition sellen_q5_transition(&sellen_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q6, 6, 87030600, esd_get_flag(3371));
OPEN_GENERIC_DIALOG_MSG(870306, sellen_q6_state, &sellen_quest_state, 87030601);
ezs::transition sellen_q6_transition(&sellen_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q7, 7, 87030700, esd_get_flag(14009255));
OPEN_GENERIC_DIALOG_MSG(870307, sellen_q7_state, &sellen_quest_state, 87030701);
ezs::transition sellen_q7_transition(&sellen_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q8, 8, 87030800, esd_get_flag(3469));
OPEN_GENERIC_DIALOG_MSG(870308, sellen_q8_state, &sellen_quest_state, 87030801);
ezs::transition sellen_q8_transition(&sellen_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(sellen_q99, 50, 87039900, esd_get_flag(3463));
OPEN_GENERIC_DIALOG_MSG(870350, sellen_q99_state, &sellen_quest_state, 87039901);
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
    .id = 87030,
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
    .id = 870300,
    .transitions = sellen_quest_list_transitions,
};

/*
 * Kenneth Haight's quest submenu
 */

extern ezs::state kenneth_quest_state;
extern ezs::state kenneth_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_quest, 4, 87040000, esd_get_flag(1045389205));
ezs::transition kenneth_quest_transition(&kenneth_quest_state, evals::get_talk_list[4]);

ADD_TALK_LIST_DATA_ARGS(kenneth_q1, 1, 87040100);
OPEN_GENERIC_DIALOG_MSG(870401, kenneth_q1_state, &kenneth_quest_state, 87040101);
ezs::transition kenneth_q1_transition(&kenneth_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q2, 2, 87040200, esd_get_flag(1045389222));
OPEN_GENERIC_DIALOG_MSG(870402, kenneth_q2_state, &kenneth_quest_state, 87040201);
ezs::transition kenneth_q2_transition(&kenneth_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q3, 3, 87040300, esd_get_flag(1046360706));
OPEN_GENERIC_DIALOG_MSG(870403, kenneth_q3_state, &kenneth_quest_state, 87040301);
ezs::transition kenneth_q3_transition(&kenneth_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q4, 4, 87040400, esd_get_flag(1046369207));
OPEN_GENERIC_DIALOG_MSG(870404, kenneth_q4_state, &kenneth_quest_state, 87040401);
ezs::transition kenneth_q4_transition(&kenneth_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q5, 5, 87040500, esd_and(esd_get_flag(3587), esd_get_flag(4229)));
OPEN_GENERIC_DIALOG_MSG(870405, kenneth_q5_state, &kenneth_quest_state, 87040501);
ezs::transition kenneth_q5_transition(&kenneth_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(kenneth_q99, 50, 87049900, esd_get_flag(3583));
OPEN_GENERIC_DIALOG_MSG(870450, kenneth_q99_state, &kenneth_quest_state, 87049901);
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
    .id = 87040,
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
    .id = 870400,
    .transitions = kenneth_quest_list_transitions,
};

/*
 * Boc's quest submenu
 */

extern ezs::state boc_quest_state;
extern ezs::state boc_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(boc_quest, 5, 87050000, esd_get_flag(1043379355));
ezs::transition boc_quest_transition(&boc_quest_state, evals::get_talk_list[5]);

ADD_TALK_LIST_DATA_ARGS(boc_q1, 1, 87050100);
OPEN_GENERIC_DIALOG_MSG(870501, boc_q1_state, &boc_quest_state, 87050101);
ezs::transition boc_q1_transition(&boc_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q2, 2, 87050200, esd_get_flag(31159202));
OPEN_GENERIC_DIALOG_MSG(870502, boc_q2_state, &boc_quest_state, 87050201);
ezs::transition boc_q2_transition(&boc_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q3, 3, 87050300, esd_get_flag(31159206));
OPEN_GENERIC_DIALOG_MSG(870503, boc_q3_state, &boc_quest_state, 87050301);
ezs::transition boc_q3_transition(&boc_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q4, 4, 87050400, esd_get_flag(1036489208));
OPEN_GENERIC_DIALOG_MSG(870504, boc_q4_state, &boc_quest_state, 87050401);
ezs::transition boc_q4_transition(&boc_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q5, 5, 87050500, esd_get_flag(1039409259));
OPEN_GENERIC_DIALOG_MSG(870505, boc_q5_state, &boc_quest_state, 87050501);
ezs::transition boc_q5_transition(&boc_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q6, 6, 87050600, esd_get_flag(11109808));
OPEN_GENERIC_DIALOG_MSG(870506, boc_q6_state, &boc_quest_state, 87050601);
ezs::transition boc_q6_transition(&boc_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q7, 7, 87050700, esd_get_flag(11109315));
OPEN_GENERIC_DIALOG_MSG(870507, boc_q7_state, &boc_quest_state, 87050701);
ezs::transition boc_q7_transition(&boc_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(boc_q99, 50, 87059900, esd_get_flag(3943));
OPEN_GENERIC_DIALOG_MSG(870550, boc_q99_state, &boc_quest_state, 87059901);
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
    .id = 87050,
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
    .id = 870500,
    .transitions = boc_quest_list_transitions,
};

/*
 * Blaidd's quest submenu
 */

extern ezs::state blaidd_quest_state;
extern ezs::state blaidd_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_quest, 6, 87060000, esd_or(esd_get_flag(1042369320), esd_get_flag(1042369328)));
ezs::transition blaidd_quest_transition(&blaidd_quest_state, evals::get_talk_list[6]);

ADD_TALK_LIST_DATA_ARGS(blaidd_q1, 1, 87060100);
OPEN_GENERIC_DIALOG_MSG(870601, blaidd_q1_state, &blaidd_quest_state, 87060101);
ezs::transition blaidd_q1_transition(&blaidd_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q2, 2, 87060200, esd_get_flag(60830));
OPEN_GENERIC_DIALOG_MSG(870602, blaidd_q2_state, &blaidd_quest_state, 87060201);
ezs::transition blaidd_q2_transition(&blaidd_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q3, 3, 87060300, esd_get_flag(1045379205));
OPEN_GENERIC_DIALOG_MSG(870603, blaidd_q3_state, &blaidd_quest_state, 87060301);
ezs::transition blaidd_q3_transition(&blaidd_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q4, 4, 87060400, esd_get_flag(1044349256));
OPEN_GENERIC_DIALOG_MSG(870604, blaidd_q4_state, &blaidd_quest_state, 87060401);
ezs::transition blaidd_q4_transition(&blaidd_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q5, 5, 87060500, esd_get_flag(12029155));
OPEN_GENERIC_DIALOG_MSG(870605, blaidd_q5_state, &blaidd_quest_state, 87060501);
ezs::transition blaidd_q5_transition(&blaidd_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q6, 6, 87060600, esd_get_flag(1051369355));
OPEN_GENERIC_DIALOG_MSG(870606, blaidd_q6_state, &blaidd_quest_state, 87060601);
ezs::transition blaidd_q6_transition(&blaidd_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q7, 7, 87060700, esd_get_flag(1052389305));
OPEN_GENERIC_DIALOG_MSG(870607, blaidd_q7_state, &blaidd_quest_state, 87060701);
ezs::transition blaidd_q7_transition(&blaidd_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(blaidd_q99, 50, 87069900, esd_get_flag(3603));
OPEN_GENERIC_DIALOG_MSG(870650, blaidd_q99_state, &blaidd_quest_state, 87069901);
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
    .id = 87060,
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
    .id = 870600,
    .transitions = blaidd_quest_list_transitions,
};

/*
 * Sorcerer Thops's quest submenu
 */

extern ezs::state thops_quest_state;
extern ezs::state thops_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(thops_quest, 7, 87070000, esd_get_flag(1039399215));
ezs::transition thops_quest_transition(&thops_quest_state, evals::get_talk_list[7]);

ADD_TALK_LIST_DATA_ARGS(thops_q1, 1, 87070100);
OPEN_GENERIC_DIALOG_MSG(870701, thops_q1_state, &thops_quest_state, 87070101);
ezs::transition thops_q1_transition(&thops_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(thops_q2, 2, 87070200, esd_get_flag(1039399220));
OPEN_GENERIC_DIALOG_MSG(870702, thops_q2_state, &thops_quest_state, 87070201);
ezs::transition thops_q2_transition(&thops_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(thops_q99, 50, 87079900, esd_get_flag(3803));
OPEN_GENERIC_DIALOG_MSG(870750, thops_q99_state, &thops_quest_state, 87079901);
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
    .id = 87070,
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
    .id = 870700,
    .transitions = thops_quest_list_transitions,
};

/*
 * Patches' quest submenu
 */

extern ezs::state patches_quest_state;
extern ezs::state patches_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(patches_quest, 8, 87080000, esd_or(esd_get_flag(31009206), esd_get_flag(16009357)));
ezs::transition patches_quest_transition(&patches_quest_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q1, 1, 87080100, esd_get_flag(60819));
OPEN_GENERIC_DIALOG_MSG(870801, patches_q1_state, &patches_quest_state, 87080101);
ezs::transition patches_q1_transition(&patches_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q2, 2, 87080200, esd_get_flag(31008522));
OPEN_GENERIC_DIALOG_MSG(870802, patches_q2_state, &patches_quest_state, 87080201);
ezs::transition patches_q2_transition(&patches_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q3, 3, 87080300, esd_get_flag(1038419259));
OPEN_GENERIC_DIALOG_MSG(870803, patches_q3_state, &patches_quest_state, 87080301);
ezs::transition patches_q3_transition(&patches_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q4, 4, 87080400, esd_and(esd_get_flag(14009300), esd_get_flag(1038419259)));
OPEN_GENERIC_DIALOG_MSG(870804, patches_q4_state, &patches_quest_state, 87080401);
ezs::transition patches_q4_transition(&patches_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q5, 5, 87080500, esd_and(esd_get_flag(1037549206), esd_get_flag(1037549209, 0)));
OPEN_GENERIC_DIALOG_MSG(870805, patches_q5_state, &patches_quest_state, 87080501);
ezs::transition patches_q5_transition(&patches_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q6, 6, 87080600, esd_get_flag(3693));
OPEN_GENERIC_DIALOG_MSG(870806, patches_q6_state, &patches_quest_state, 87080601);
ezs::transition patches_q6_transition(&patches_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q7, 7, 87080700, esd_get_flag(16009355));
OPEN_GENERIC_DIALOG_MSG(870807, patches_q7_state, &patches_quest_state, 87080701);
ezs::transition patches_q7_transition(&patches_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q8, 8, 87080800, esd_get_flag(16009357));
OPEN_GENERIC_DIALOG_MSG(870808, patches_q8_state, &patches_quest_state, 87080801);
ezs::transition patches_q8_transition(&patches_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q9, 9, 87080900, esd_or(esd_get_flag(16009364), esd_or(esd_get_flag(16009358), esd_get_flag(16002721))));
OPEN_GENERIC_DIALOG_MSG(870809, patches_q9_state, &patches_quest_state, 87080901);
ezs::transition patches_q9_transition(&patches_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(patches_q99, 50, 87089900, esd_get_flag(3683));
OPEN_GENERIC_DIALOG_MSG(870850, patches_q99_state, &patches_quest_state, 87089901);
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
    .id = 87080,
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
    .id = 870800,
    .transitions = patches_quest_list_transitions,
};

/*
 * Ranni's quest submenu
 */

extern ezs::state ranni_quest_state;
extern ezs::state ranni_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(ranni_quest, 9, 87090000, esd_or(esd_get_flag(1034509410), esd_get_flag(1034509431)));
ezs::transition ranni_quest_transition(&ranni_quest_state, evals::get_talk_list[9]);

ADD_TALK_LIST_DATA_ARGS(ranni_q1, 1, 87090100);
OPEN_GENERIC_DIALOG_MSG(870901, ranni_q1_state, &ranni_quest_state, 87090101);
ezs::transition ranni_q1_transition(&ranni_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q2, 2, 87090200, esd_get_flag(1034509413));
OPEN_GENERIC_DIALOG_MSG(870902, ranni_q2_state, &ranni_quest_state, 87090201);
ezs::transition ranni_q2_transition(&ranni_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q3, 3, 87090300, esd_get_flag(1034509416));
OPEN_GENERIC_DIALOG_MSG(870903, ranni_q3_state, &ranni_quest_state, 87090301);
ezs::transition ranni_q3_transition(&ranni_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q4, 4, 87090400, esd_get_flag(1044369214));
OPEN_GENERIC_DIALOG_MSG(870904, ranni_q4_state, &ranni_quest_state, 87090401);
ezs::transition ranni_q4_transition(&ranni_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q5, 5, 87090500, esd_get_flag(1044369223, 0));
OPEN_GENERIC_DIALOG_MSG(870905, ranni_q5_state, &ranni_quest_state, 87090501);
ezs::transition ranni_q5_transition(&ranni_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q6, 6, 87090600, esd_get_flag(9130));
OPEN_GENERIC_DIALOG_MSG(870906, ranni_q6_state, &ranni_quest_state, 87090601);
ezs::transition ranni_q6_transition(&ranni_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q7, 7, 87090700, esd_or(esd_compare_inventory(8159, 1), esd_get_flag(1034509420)));
OPEN_GENERIC_DIALOG_MSG(870907, ranni_q7_state, &ranni_quest_state, 87090701);
ezs::transition ranni_q7_transition(&ranni_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q8, 8, 87090800, esd_get_flag(1034509421));
OPEN_GENERIC_DIALOG_MSG(870908, ranni_q8_state, &ranni_quest_state, 87090801);
ezs::transition ranni_q8_transition(&ranni_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q9, 9, 87090900, esd_compare_inventory(8191, 1));
OPEN_GENERIC_DIALOG_MSG(870909, ranni_q9_state, &ranni_quest_state, 87090901);
ezs::transition ranni_q9_transition(&ranni_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q10, 10, 87091000, esd_or(esd_compare_inventory(8146, 1), esd_compare_inventory(8187, 1)));
OPEN_GENERIC_DIALOG_MSG(8709010, ranni_q10_state, &ranni_quest_state, 87091001);
ezs::transition ranni_q10_transition(&ranni_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q11, 11, 87091100, esd_get_flag(12019257));
OPEN_GENERIC_DIALOG_MSG(870911, ranni_q11_state, &ranni_quest_state, 87091101);
ezs::transition ranni_q11_transition(&ranni_q11_state, evals::get_talk_list[11]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q12, 12, 87091200, esd_or(esd_compare_inventory(8121, 1, 1), esd_get_flag(1034509406)));
OPEN_GENERIC_DIALOG_MSG(870912, ranni_q12_state, &ranni_quest_state, 87091201);
ezs::transition ranni_q12_transition(&ranni_q12_state, evals::get_talk_list[12]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q13, 13, 87091300, esd_get_flag(1034509406));
OPEN_GENERIC_DIALOG_MSG(870913, ranni_q13_state, &ranni_quest_state, 87091301);
ezs::transition ranni_q13_transition(&ranni_q13_state, evals::get_talk_list[13]);

ADD_TALK_LIST_IF_DATA_ARGS(ranni_q99, 50, 87099900, esd_get_flag(1034502742));
OPEN_GENERIC_DIALOG_MSG(870950, ranni_q99_state, &ranni_quest_state, 87099901);
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
    .id = 87090,
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
    .id = 870900,
    .transitions = ranni_quest_list_transitions,
};

/*
 * Rya's quest submenu
 */

extern ezs::state rya_quest_state;
extern ezs::state rya_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(rya_quest, 10, 87100000, esd_get_flag(1037429209));
ezs::transition rya_quest_transition(&rya_quest_state, evals::get_talk_list[10]);

ADD_TALK_LIST_DATA_ARGS(rya_q1, 1, 87100100);
OPEN_GENERIC_DIALOG_MSG(871001, rya_q1_state, &rya_quest_state, 87100101);
ezs::transition rya_q1_transition(&rya_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q2, 2, 87100200, esd_get_flag(1037429210));
OPEN_GENERIC_DIALOG_MSG(871002, rya_q2_state, &rya_quest_state, 87100201);
ezs::transition rya_q2_transition(&rya_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q3, 3, 87100300, esd_get_flag(1038519205));
OPEN_GENERIC_DIALOG_MSG(871003, rya_q3_state, &rya_quest_state, 87100301);
ezs::transition rya_q3_transition(&rya_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q4, 4, 87100400, esd_get_flag(16009305));
OPEN_GENERIC_DIALOG_MSG(871004, rya_q4_state, &rya_quest_state, 87100401);
ezs::transition rya_q4_transition(&rya_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q5, 5, 87100500, esd_get_flag(16009308));
OPEN_GENERIC_DIALOG_MSG(871005, rya_q5_state, &rya_quest_state, 87100501);
ezs::transition rya_q5_transition(&rya_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q6, 6, 87100600, esd_get_flag(16009307));
OPEN_GENERIC_DIALOG_MSG(871006, rya_q6_state, &rya_quest_state, 87100601);
ezs::transition rya_q6_transition(&rya_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q7, 7, 87100700, esd_get_flag(16009315));
OPEN_GENERIC_DIALOG_MSG(871007, rya_q7_state, &rya_quest_state, 87100701);
ezs::transition rya_q7_transition(&rya_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q8, 8, 87100800, esd_get_flag(16009318));
OPEN_GENERIC_DIALOG_MSG(871008, rya_q8_state, &rya_quest_state, 87100801);
ezs::transition rya_q8_transition(&rya_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q9, 9, 87100900, esd_get_flag(16009319));
OPEN_GENERIC_DIALOG_MSG(871009, rya_q9_state, &rya_quest_state, 87100901);
ezs::transition rya_q9_transition(&rya_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q10, 10, 87101000, esd_get_flag(16009222));
OPEN_GENERIC_DIALOG_MSG(8710010, rya_q10_state, &rya_quest_state, 87101001);
ezs::transition rya_q10_transition(&rya_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q11, 11, 87101100, esd_get_flag(16009326));
OPEN_GENERIC_DIALOG_MSG(871011, rya_q11_state, &rya_quest_state, 87101101);
ezs::transition rya_q11_transition(&rya_q11_state, evals::get_talk_list[11]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q12, 12, 87101200, esd_compare_inventory(8721, 1, 1));
OPEN_GENERIC_DIALOG_MSG(871012, rya_q12_state, &rya_quest_state, 87101201);
ezs::transition rya_q12_transition(&rya_q12_state, evals::get_talk_list[12]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q13, 13, 87101300, esd_get_flag(16009327));
OPEN_GENERIC_DIALOG_MSG(871013, rya_q13_state, &rya_quest_state, 87101301);
ezs::transition rya_q13_transition(&rya_q13_state, evals::get_talk_list[13]);

ADD_TALK_LIST_IF_DATA_ARGS(rya_q99, 50, 87109900, esd_get_flag(3429));
OPEN_GENERIC_DIALOG_MSG(871050, rya_q99_state, &rya_quest_state, 87109901);
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
    .id = 87100,
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
    .id = 871000,
    .transitions = rya_quest_list_transitions,
};

/*
 * Gowry's quest submenu
 */

extern ezs::state gowry_quest_state;
extern ezs::state gowry_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(gowry_quest, 11, 87110000, esd_get_flag(1050389205));
ezs::transition gowry_quest_transition(&gowry_quest_state, evals::get_talk_list[11]);

ADD_TALK_LIST_DATA_ARGS(gowry_q1, 1, 87110100);
OPEN_GENERIC_DIALOG_MSG(871101, gowry_q1_state, &gowry_quest_state, 87110101);
ezs::transition gowry_q1_transition(&gowry_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q2, 2, 87110200, esd_get_flag(1050389207));
OPEN_GENERIC_DIALOG_MSG(871102, gowry_q2_state, &gowry_quest_state, 87110201);
ezs::transition gowry_q2_transition(&gowry_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q3, 3, 87110300, esd_get_flag(1050389210));
OPEN_GENERIC_DIALOG_MSG(871103, gowry_q3_state, &gowry_quest_state, 87110301);
ezs::transition gowry_q3_transition(&gowry_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q4, 4, 87110400, esd_get_flag(1050389257));
OPEN_GENERIC_DIALOG_MSG(871104, gowry_q4_state, &gowry_quest_state, 87110401);
ezs::transition gowry_q4_transition(&gowry_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q5, 5, 87110500, esd_get_flag(1050389219));
OPEN_GENERIC_DIALOG_MSG(871105, gowry_q5_state, &gowry_quest_state, 87110501);
ezs::transition gowry_q5_transition(&gowry_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q6, 6, 87110600, esd_get_flag(1050389221));
OPEN_GENERIC_DIALOG_MSG(871106, gowry_q6_state, &gowry_quest_state, 87110601);
ezs::transition gowry_q6_transition(&gowry_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q7, 7, 87110700, esd_get_flag(1050389227));
OPEN_GENERIC_DIALOG_MSG(871107, gowry_q7_state, &gowry_quest_state, 87110701);
ezs::transition gowry_q7_transition(&gowry_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q8, 8, 87110800, esd_get_flag(1050389230));
OPEN_GENERIC_DIALOG_MSG(871108, gowry_q8_state, &gowry_quest_state, 87110801);
ezs::transition gowry_q8_transition(&gowry_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q9, 9, 87110900, esd_get_flag(1050389234));
OPEN_GENERIC_DIALOG_MSG(871109, gowry_q9_state, &gowry_quest_state, 87110901);
ezs::transition gowry_q9_transition(&gowry_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q10, 10, 87111000, esd_get_flag(1050389235));
OPEN_GENERIC_DIALOG_MSG(8711010, gowry_q10_state, &gowry_quest_state, 87111001);
ezs::transition gowry_q10_transition(&gowry_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(gowry_q99, 50, 87119900, esd_get_flag(3429));
OPEN_GENERIC_DIALOG_MSG(871150, gowry_q99_state, &gowry_quest_state, 87119901);
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
    .id = 87110,
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
    .id = 871100,
    .transitions = gowry_quest_list_transitions,
};

/*
 * D's quest submenu
 */

extern ezs::state d_quest_state;
extern ezs::state d_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(d_quest, 12, 87120000, esd_or(esd_get_flag(1044399206), esd_and(esd_get_flag(1051439205), esd_get_flag(11109617))));
ezs::transition d_quest_transition(&d_quest_state, evals::get_talk_list[12]);

ADD_TALK_LIST_DATA_ARGS(d_q1, 1, 87120100);
OPEN_GENERIC_DIALOG_MSG(871201, d_q1_state, &d_quest_state, 87120101);
ezs::transition d_q1_transition(&d_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q2, 2, 87120200, esd_and(esd_get_flag(1051439205), esd_get_flag(11109617, 0)));
OPEN_GENERIC_DIALOG_MSG(871202, d_q2_state, &d_quest_state, 87120201);
ezs::transition d_q2_transition(&d_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q3, 3, 87120300, esd_get_flag(1044399206));
OPEN_GENERIC_DIALOG_MSG(871203, d_q3_state, &d_quest_state, 87120301);
ezs::transition d_q3_transition(&d_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q4, 4, 87120400, esd_get_flag(11109625));
OPEN_GENERIC_DIALOG_MSG(871204, d_q4_state, &d_quest_state, 87120401);
ezs::transition d_q4_transition(&d_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q5, 5, 87120500, esd_get_flag(11102843));
OPEN_GENERIC_DIALOG_MSG(871205, d_q5_state, &d_quest_state, 87120501);
ezs::transition d_q5_transition(&d_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q6, 6, 87120600, esd_get_flag(12029015));
OPEN_GENERIC_DIALOG_MSG(871206, d_q6_state, &d_quest_state, 87120601);
ezs::transition d_q6_transition(&d_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q7, 7, 87120700, esd_get_flag(12039005));
OPEN_GENERIC_DIALOG_MSG(871207, d_q7_state, &d_quest_state, 87120701);
ezs::transition d_q7_transition(&d_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(d_q99, 50, 87129900, esd_get_flag(3429));
OPEN_GENERIC_DIALOG_MSG(871250, d_q99_state, &d_quest_state, 87129901);
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
    .id = 87120,
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
    .id = 871200,
    .transitions = d_quest_list_transitions,
};


/*
 * Gurranq's quest submenu
 */

extern ezs::state gurranq_quest_state;
extern ezs::state gurranq_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_quest, 13, 87130000, esd_and(esd_get_flag(1051439205), esd_get_flag(11109617)));
ezs::transition gurranq_quest_transition(&gurranq_quest_state, evals::get_talk_list[13]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q1, 1, 87130100, esd_get_flag_value(1051439230, 1, 0));
OPEN_GENERIC_DIALOG_MSG(871301, gurranq_q1_state, &gurranq_quest_state, 87130101);
ezs::transition gurranq_q1_transition(&gurranq_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q2, 2, 87130100, esd_get_flag_value(1051439230, 2, 0));
OPEN_GENERIC_DIALOG_MSG(871302, gurranq_q2_state, &gurranq_quest_state, 87130102);
ezs::transition gurranq_q2_transition(&gurranq_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q3, 3, 87130100, esd_get_flag_value(1051439230, 3, 0));
OPEN_GENERIC_DIALOG_MSG(871303, gurranq_q3_state, &gurranq_quest_state, 87130103);
ezs::transition gurranq_q3_transition(&gurranq_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q4, 4, 87130100, esd_get_flag_value(1051439230, 4, 0));
OPEN_GENERIC_DIALOG_MSG(871304, gurranq_q4_state, &gurranq_quest_state, 87130104);
ezs::transition gurranq_q4_transition(&gurranq_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q5, 5, 87130100, esd_get_flag_value(1051439230, 5, 0));
OPEN_GENERIC_DIALOG_MSG(871305, gurranq_q5_state, &gurranq_quest_state, 87130105);
ezs::transition gurranq_q5_transition(&gurranq_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q6, 6, 87130100, esd_get_flag_value(1051439230, 6, 0));
OPEN_GENERIC_DIALOG_MSG(871306, gurranq_q6_state, &gurranq_quest_state, 87130106);
ezs::transition gurranq_q6_transition(&gurranq_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q7, 7, 87130100, esd_get_flag_value(1051439230, 7, 0));
OPEN_GENERIC_DIALOG_MSG(871307, gurranq_q7_state, &gurranq_quest_state, 87130107);
ezs::transition gurranq_q7_transition(&gurranq_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q8, 8, 87130100, esd_get_flag_value(1051439230, 8, 0));
OPEN_GENERIC_DIALOG_MSG(871308, gurranq_q8_state, &gurranq_quest_state, 87130108);
ezs::transition gurranq_q8_transition(&gurranq_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q9, 9, 87130100, esd_get_flag_value(1051439230, 9, 2));
OPEN_GENERIC_DIALOG_MSG(871309, gurranq_q9_state, &gurranq_quest_state, 87130109);
ezs::transition gurranq_q9_transition(&gurranq_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q10, 10, 87130200, esd_get_flag(1051439211));
OPEN_GENERIC_DIALOG_MSG(8713010, gurranq_q10_state, &gurranq_quest_state, 87130201);
ezs::transition gurranq_q10_transition(&gurranq_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(gurranq_q11, 11, 87130300, esd_get_flag_value(1051439230, 9, 2));
OPEN_GENERIC_DIALOG_MSG(871311, gurranq_q11_state, &gurranq_quest_state, 87130301);
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
    .id = 87130,
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
    .id = 871300,
    .transitions = gurranq_quest_list_transitions,
};

/*
 * Diallos' quest submenu
 */

extern ezs::state diallos_quest_state;
extern ezs::state diallos_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(diallos_quest, 14, 87140000, esd_get_flag(11109406));
ezs::transition diallos_quest_transition(&diallos_quest_state, evals::get_talk_list[14]);

ADD_TALK_LIST_DATA_ARGS(diallos_q1, 1, 87140100);
OPEN_GENERIC_DIALOG_MSG(871401, diallos_q1_state, &diallos_quest_state, 87140101);
ezs::transition diallos_q1_transition(&diallos_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q2, 2, 87140200, esd_get_flag(1037449205));
OPEN_GENERIC_DIALOG_MSG(871402, diallos_q2_state, &diallos_quest_state, 87140201);
ezs::transition diallos_q2_transition(&diallos_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q3, 3, 87140300, esd_get_flag(11109430));
OPEN_GENERIC_DIALOG_MSG(871403, diallos_q3_state, &diallos_quest_state, 87140301);
ezs::transition diallos_q3_transition(&diallos_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q4, 4, 87140400, esd_get_flag(16009405));
OPEN_GENERIC_DIALOG_MSG(871404, diallos_q4_state, &diallos_quest_state, 87140401);
ezs::transition diallos_q4_transition(&diallos_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q5, 5, 87140500, esd_get_flag(16002730));
OPEN_GENERIC_DIALOG_MSG(871405, diallos_q5_state, &diallos_quest_state, 87140501);
ezs::transition diallos_q5_transition(&diallos_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q6, 6, 87140600, esd_get_flag(1039449305));
OPEN_GENERIC_DIALOG_MSG(871406, diallos_q6_state, &diallos_quest_state, 87140601);
ezs::transition diallos_q6_transition(&diallos_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q7, 7, 87140700, esd_get_flag(1039449315));
OPEN_GENERIC_DIALOG_MSG(871407, diallos_q7_state, &diallos_quest_state, 87140701);
ezs::transition diallos_q7_transition(&diallos_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q8, 8, 87140800, esd_get_flag(1039449285));
OPEN_GENERIC_DIALOG_MSG(871408, diallos_q8_state, &diallos_quest_state, 87140801);
ezs::transition diallos_q8_transition(&diallos_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(diallos_q99, 50, 87149900, esd_get_flag(3443));
OPEN_GENERIC_DIALOG_MSG(871450, diallos_q99_state, &diallos_quest_state, 87149901);
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
    .id = 87140,
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
    .id = 871400,
    .transitions = diallos_quest_list_transitions,
};

/*
 * Seluvis' quest submenu
 */

extern ezs::state seluvis_quest_state;
extern ezs::state seluvis_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_quest, 15, 87150000, esd_get_flag(1034509312));
ezs::transition seluvis_quest_transition(&seluvis_quest_state, evals::get_talk_list[15]);

ADD_TALK_LIST_DATA_ARGS(seluvis_q1, 1, 87150100);
OPEN_GENERIC_DIALOG_MSG(871501, seluvis_q1_state, &seluvis_quest_state, 87150101);
ezs::transition seluvis_q1_transition(&seluvis_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q2, 2, 87150200, esd_get_flag(11109919));
OPEN_GENERIC_DIALOG_MSG(871502, seluvis_q2_state, &seluvis_quest_state, 87150201);
ezs::transition seluvis_q2_transition(&seluvis_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q3, 3, 87150300, esd_get_flag(35009326));
OPEN_GENERIC_DIALOG_MSG(871503, seluvis_q3_state, &seluvis_quest_state, 87150301);
ezs::transition seluvis_q3_transition(&seluvis_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q4, 4, 87150400, esd_get_flag(11109553));
OPEN_GENERIC_DIALOG_MSG(871504, seluvis_q4_state, &seluvis_quest_state, 87150401);
ezs::transition seluvis_q4_transition(&seluvis_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q5, 5, 87150500, esd_get_flag(1034509313));
OPEN_GENERIC_DIALOG_MSG(871505, seluvis_q5_state, &seluvis_quest_state, 87150501);
ezs::transition seluvis_q5_transition(&seluvis_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q6, 6, 87150600, esd_get_flag(1034509328));
OPEN_GENERIC_DIALOG_MSG(871506, seluvis_q6_state, &seluvis_quest_state, 87150601);
ezs::transition seluvis_q6_transition(&seluvis_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q7, 7, 87150700, esd_get_flag(1034509333));
OPEN_GENERIC_DIALOG_MSG(871507, seluvis_q7_state, &seluvis_quest_state, 87150701);
ezs::transition seluvis_q7_transition(&seluvis_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q8, 8, 87150800, esd_get_flag(1034509335));
OPEN_GENERIC_DIALOG_MSG(871508, seluvis_q8_state, &seluvis_quest_state, 87150801);
ezs::transition seluvis_q8_transition(&seluvis_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q9, 9, 87150900, esd_get_flag(1034509316));
OPEN_GENERIC_DIALOG_MSG(871509, seluvis_q9_state, &seluvis_quest_state, 87150901);
ezs::transition seluvis_q9_transition(&seluvis_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q10, 10, 87151000, esd_get_flag(1034509426));
OPEN_GENERIC_DIALOG_MSG(8715010, seluvis_q10_state, &seluvis_quest_state, 87151001);
ezs::transition seluvis_q10_transition(&seluvis_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(seluvis_q99, 50, 87159900, esd_get_flag(1034509302));
OPEN_GENERIC_DIALOG_MSG(871550, seluvis_q99_state, &seluvis_quest_state, 87159901);
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
    .id = 87150,
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
    .id = 871500,
    .transitions = seluvis_quest_list_transitions,
};

/*
 * Dung Eater's quest submenu
 */

extern ezs::state dungeater_quest_state;
extern ezs::state dungeater_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_quest, 16, 87160000, esd_get_flag(11109955));
ezs::transition dungeater_quest_transition(&dungeater_quest_state, evals::get_talk_list[16]);

ADD_TALK_LIST_DATA_ARGS(dungeater_q1, 1, 87160100);
OPEN_GENERIC_DIALOG_MSG(871601, dungeater_q1_state, &dungeater_quest_state, 87160101);
ezs::transition dungeater_q1_transition(&dungeater_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q2, 2, 87160200, esd_get_flag(11109957));
OPEN_GENERIC_DIALOG_MSG(871602, dungeater_q2_state, &dungeater_quest_state, 87160201);
ezs::transition dungeater_q2_transition(&dungeater_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q3, 3, 87160300, esd_get_flag(35009306));
OPEN_GENERIC_DIALOG_MSG(871603, dungeater_q3_state, &dungeater_quest_state, 87160301);
ezs::transition dungeater_q3_transition(&dungeater_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q4, 4, 87160400, esd_get_flag(4248));
OPEN_GENERIC_DIALOG_MSG(871604, dungeater_q4_state, &dungeater_quest_state, 87160401);
ezs::transition dungeater_q4_transition(&dungeater_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q5, 5, 87160500, esd_get_flag(11109959));
OPEN_GENERIC_DIALOG_MSG(871605, dungeater_q5_state, &dungeater_quest_state, 87160501);
ezs::transition dungeater_q5_transition(&dungeater_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q6, 6, 87160600, esd_get_flag(35009334));
OPEN_GENERIC_DIALOG_MSG(871606, dungeater_q6_state, &dungeater_quest_state, 87160601);
ezs::transition dungeater_q6_transition(&dungeater_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(dungeater_q99, 50, 87169900, esd_get_flag(1034509302));
OPEN_GENERIC_DIALOG_MSG(871650, dungeater_q99_state, &dungeater_quest_state, 87169901);
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
    .id = 87160,
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
    .id = 871600,
    .transitions = dungeater_quest_list_transitions,
};

/*
 * Rogier's quest submenu
 */

extern ezs::state rogier_quest_state;
extern ezs::state rogier_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(rogier_quest, 17, 87170000, esd_or(esd_get_flag(10009617), esd_or(esd_get_flag(10009616), esd_get_flag(10009619))));
ezs::transition rogier_quest_transition(&rogier_quest_state, evals::get_talk_list[17]);

ADD_TALK_LIST_DATA_ARGS(rogier_q1, 1, 87170100);
OPEN_GENERIC_DIALOG_MSG(871701, rogier_q1_state, &rogier_quest_state, 87170101);
ezs::transition rogier_q1_transition(&rogier_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q2, 2, 87170200, esd_get_flag(11109505));
OPEN_GENERIC_DIALOG_MSG(871702, rogier_q2_state, &rogier_quest_state, 87170201);
ezs::transition rogier_q2_transition(&rogier_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q3, 3, 87170300, esd_get_flag(11109521));
OPEN_GENERIC_DIALOG_MSG(871703, rogier_q3_state, &rogier_quest_state, 87170301);
ezs::transition rogier_q3_transition(&rogier_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q4, 4, 87170400, esd_get_flag(11109017));
OPEN_GENERIC_DIALOG_MSG(871704, rogier_q4_state, &rogier_quest_state, 87170401);
ezs::transition rogier_q4_transition(&rogier_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q5, 5, 87170500, esd_get_flag(11109527));
OPEN_GENERIC_DIALOG_MSG(871705, rogier_q5_state, &rogier_quest_state, 87170501);
ezs::transition rogier_q5_transition(&rogier_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q6, 6, 87170600, esd_get_flag(11109506));
OPEN_GENERIC_DIALOG_MSG(871706, rogier_q6_state, &rogier_quest_state, 87170601);
ezs::transition rogier_q6_transition(&rogier_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q7, 7, 87170700, esd_get_flag(1034509432));
OPEN_GENERIC_DIALOG_MSG(871707, rogier_q7_state, &rogier_quest_state, 87170701);
ezs::transition rogier_q7_transition(&rogier_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q8, 8, 87170800, esd_get_flag(11109518));
OPEN_GENERIC_DIALOG_MSG(871708, rogier_q8_state, &rogier_quest_state, 87170801);
ezs::transition rogier_q8_transition(&rogier_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q9, 9, 87170900, esd_get_flag(1034509410));
OPEN_GENERIC_DIALOG_MSG(871709, rogier_q9_state, &rogier_quest_state, 87170901);
ezs::transition rogier_q9_transition(&rogier_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q10, 10, 87171000, esd_get_flag(11109532));
OPEN_GENERIC_DIALOG_MSG(8717010, rogier_q10_state, &rogier_quest_state, 87171001);
ezs::transition rogier_q10_transition(&rogier_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(rogier_q99, 50, 87179900, esd_get_flag(3903));
OPEN_GENERIC_DIALOG_MSG(871750, rogier_q99_state, &rogier_quest_state, 87179901);
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
    .id = 87170,
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
    .id = 871700,
    .transitions = rogier_quest_list_transitions,
};

/*
 * Nepheli's quest submenu
 */

extern ezs::state nepheli_quest_state;
extern ezs::state nepheli_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_quest, 18, 87180000, esd_or(esd_get_flag(10009706), esd_get_flag(11109905)));
ezs::transition nepheli_quest_transition(&nepheli_quest_state, evals::get_talk_list[18]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q1, 1, 87180100, esd_get_flag(10009706));
OPEN_GENERIC_DIALOG_MSG(871801, nepheli_q1_state, &nepheli_quest_state, 87180101);
ezs::transition nepheli_q1_transition(&nepheli_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q2, 2, 87180200, esd_and(esd_get_flag(11109905), esd_get_flag(11109905)));
OPEN_GENERIC_DIALOG_MSG(871802, nepheli_q2_state, &nepheli_quest_state, 87180201);
ezs::transition nepheli_q2_transition(&nepheli_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q3, 3, 87180300, esd_get_flag(1034429205));
OPEN_GENERIC_DIALOG_MSG(871803, nepheli_q3_state, &nepheli_quest_state, 87180301);
ezs::transition nepheli_q3_transition(&nepheli_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q4, 4, 87180400, esd_get_flag(11109923));
OPEN_GENERIC_DIALOG_MSG(871804, nepheli_q4_state, &nepheli_quest_state, 87180401);
ezs::transition nepheli_q4_transition(&nepheli_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q5, 5, 87180500, esd_get_flag(11109678));
OPEN_GENERIC_DIALOG_MSG(871805, nepheli_q5_state, &nepheli_quest_state, 87180501);
ezs::transition nepheli_q5_transition(&nepheli_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q6, 6, 87180600, esd_get_flag(11109917));
OPEN_GENERIC_DIALOG_MSG(871806, nepheli_q6_state, &nepheli_quest_state, 87180601);
ezs::transition nepheli_q6_transition(&nepheli_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q7, 7, 87180700, esd_get_flag(11109921));
OPEN_GENERIC_DIALOG_MSG(871807, nepheli_q7_state, &nepheli_quest_state, 87180701);
ezs::transition nepheli_q7_transition(&nepheli_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q8, 8, 87180800, esd_get_flag(10009716));
OPEN_GENERIC_DIALOG_MSG(871808, nepheli_q8_state, &nepheli_quest_state, 87180801);
ezs::transition nepheli_q8_transition(&nepheli_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(nepheli_q99, 50, 87189900, esd_get_flag(4223));
OPEN_GENERIC_DIALOG_MSG(871850, nepheli_q99_state, &nepheli_quest_state, 87189901);
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
    .id = 87180,
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
    .id = 871800,
    .transitions = nepheli_quest_list_transitions,
};

/*
 * Hyetta's quest submenu
 */

extern ezs::state hyetta_quest_state;
extern ezs::state hyetta_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_quest, 19, 87190000, esd_get_flag(1039409205));
ezs::transition hyetta_quest_transition(&hyetta_quest_state, evals::get_talk_list[19]);

ADD_TALK_LIST_DATA_ARGS(hyetta_q1, 1, 87190100);
OPEN_GENERIC_DIALOG_MSG(871901, hyetta_q1_state, &hyetta_quest_state, 87190101);
ezs::transition hyetta_q1_transition(&hyetta_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q2, 2, 87190200, esd_get_flag(1038439206));
OPEN_GENERIC_DIALOG_MSG(871902, hyetta_q2_state, &hyetta_quest_state, 87190201);
ezs::transition hyetta_q2_transition(&hyetta_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q3, 3, 87190300, esd_or(esd_compare_inventory(8126, 1, 0), esd_get_flag(1036499206)));
OPEN_GENERIC_DIALOG_MSG(871903, hyetta_q3_state, &hyetta_quest_state, 87190301);
ezs::transition hyetta_q3_transition(&hyetta_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q4, 4, 87190400, esd_get_flag(1036499206));
OPEN_GENERIC_DIALOG_MSG(871904, hyetta_q4_state, &hyetta_quest_state, 87190401);
ezs::transition hyetta_q4_transition(&hyetta_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q5, 5, 87190500, esd_get_flag(35009205));
OPEN_GENERIC_DIALOG_MSG(871905, hyetta_q5_state, &hyetta_quest_state, 87190501);
ezs::transition hyetta_q5_transition(&hyetta_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q6, 6, 87190600, esd_get_flag(35000500));
OPEN_GENERIC_DIALOG_MSG(871906, hyetta_q6_state, &hyetta_quest_state, 87190601);
ezs::transition hyetta_q6_transition(&hyetta_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q7, 7, 87190700, esd_get_flag(35000701));
OPEN_GENERIC_DIALOG_MSG(871907, hyetta_q7_state, &hyetta_quest_state, 87190701);
ezs::transition hyetta_q7_transition(&hyetta_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(hyetta_q99, 50, 87199900, esd_get_flag(3383));
OPEN_GENERIC_DIALOG_MSG(871950, hyetta_q99_state, &hyetta_quest_state, 87199901);
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
    .id = 87190,
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
    .id = 871900,
    .transitions = hyetta_quest_list_transitions,
};

/*
 * Alexander's quest submenu
 */

extern ezs::state alexander_quest_state;
extern ezs::state alexander_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(alexander_quest, 20, 87200000, esd_or(esd_get_flag(1043399306), esd_or(esd_get_flag(1051369255), esd_get_flag(1051369265))));
ezs::transition alexander_quest_transition(&alexander_quest_state, evals::get_talk_list[20]);

ADD_TALK_LIST_DATA_ARGS(alexander_q1, 1, 87200100);
OPEN_GENERIC_DIALOG_MSG(872001, alexander_q1_state, &alexander_quest_state, 87200101);
ezs::transition alexander_q1_transition(&alexander_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q2, 2, 87200200, esd_get_flag(32009206));
OPEN_GENERIC_DIALOG_MSG(872002, alexander_q2_state, &alexander_quest_state, 87200201);
ezs::transition alexander_q2_transition(&alexander_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q3, 3, 87200300, esd_get_flag(1051369255));
OPEN_GENERIC_DIALOG_MSG(872003, alexander_q3_state, &alexander_quest_state, 87200301);
ezs::transition alexander_q3_transition(&alexander_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q4, 4, 87200400, esd_get_flag(1051369265));
OPEN_GENERIC_DIALOG_MSG(872004, alexander_q4_state, &alexander_quest_state, 87200401);
ezs::transition alexander_q4_transition(&alexander_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q5, 5, 87200500, esd_and(esd_get_flag(1043399306), esd_get_flag(1039449206)));
OPEN_GENERIC_DIALOG_MSG(872005, alexander_q5_state, &alexander_quest_state, 87200501);
ezs::transition alexander_q5_transition(&alexander_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q6, 6, 87200600, esd_get_flag(1035539205));
OPEN_GENERIC_DIALOG_MSG(872006, alexander_q6_state, &alexander_quest_state, 87200601);
ezs::transition alexander_q6_transition(&alexander_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q7, 7, 87200700, esd_get_flag(13009255));
OPEN_GENERIC_DIALOG_MSG(872007, alexander_q7_state, &alexander_quest_state, 87200701);
ezs::transition alexander_q7_transition(&alexander_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q8, 8, 87200800, esd_get_flag(13009257));
OPEN_GENERIC_DIALOG_MSG(872008, alexander_q8_state, &alexander_quest_state, 87200801);
ezs::transition alexander_q8_transition(&alexander_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(alexander_q99, 50, 87209900, esd_or(esd_get_flag(13009260), esd_get_flag(13009256)));
OPEN_GENERIC_DIALOG_MSG(872050, alexander_q99_state, &alexander_quest_state, 87209901);
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
    .id = 87200,
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
    .id = 872000,
    .transitions = alexander_quest_list_transitions,
};

/*
 * Yura's quest submenu
 */

extern ezs::state yura_quest_state;
extern ezs::state yura_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(yura_quest, 21, 87210000, esd_get_flag(1043379260));
ezs::transition yura_quest_transition(&yura_quest_state, evals::get_talk_list[21]);

ADD_TALK_LIST_DATA_ARGS(yura_q1, 1, 87210100);
OPEN_GENERIC_DIALOG_MSG(872101, yura_q1_state, &yura_quest_state, 87210101);
ezs::transition yura_q1_transition(&yura_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q2, 2, 87210200, esd_and(esd_get_flag(1043379260), esd_and(esd_not(esd_get_flag(1043369201)), esd_get_flag(1043359257))));
OPEN_GENERIC_DIALOG_MSG(872102, yura_q2_state, &yura_quest_state, 87210201);
ezs::transition yura_q2_transition(&yura_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q3, 3, 87210300, esd_get_flag(1043379262));
OPEN_GENERIC_DIALOG_MSG(872103, yura_q3_state, &yura_quest_state, 87210301);
ezs::transition yura_q3_transition(&yura_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q4, 4, 87210400, esd_get_flag(1035469207));
OPEN_GENERIC_DIALOG_MSG(872104, yura_q4_state, &yura_quest_state, 87210401);
ezs::transition yura_q4_transition(&yura_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q5, 5, 87210500, esd_get_flag(1039529205));
OPEN_GENERIC_DIALOG_MSG(872105, yura_q5_state, &yura_quest_state, 87210501);
ezs::transition yura_q5_transition(&yura_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q6, 6, 87210600, esd_get_flag(1049539209));
OPEN_GENERIC_DIALOG_MSG(872106, yura_q6_state, &yura_quest_state, 87210601);
ezs::transition yura_q6_transition(&yura_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(yura_q99, 50, 87219900, esd_get_flag(3623));
OPEN_GENERIC_DIALOG_MSG(872150, yura_q99_state, &yura_quest_state, 87219901);
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
    .id = 87210,
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
    .id = 872100,
    .transitions = yura_quest_list_transitions,
};

/*
 * Fia's quest submenu
 */

extern ezs::state fia_quest_state;
extern ezs::state fia_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(fia_quest, 22, 87220000, esd_get_flag(11109008));
ezs::transition fia_quest_transition(&fia_quest_state, evals::get_talk_list[22]);

ADD_TALK_LIST_DATA_ARGS(fia_q1, 1, 87220100);
OPEN_GENERIC_DIALOG_MSG(872201, fia_q1_state, &fia_quest_state, 87220101);
ezs::transition fia_q1_transition(&fia_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q2, 2, 87220200, esd_get_flag(11109625));
OPEN_GENERIC_DIALOG_MSG(872202, fia_q2_state, &fia_quest_state, 87220201);
ezs::transition fia_q2_transition(&fia_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q3, 3, 87220300, esd_get_flag(11109015));
OPEN_GENERIC_DIALOG_MSG(872203, fia_q3_state, &fia_quest_state, 87220301);
ezs::transition fia_q3_transition(&fia_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q4, 4, 87220400, esd_compare_inventory(8191, 1, 0));
OPEN_GENERIC_DIALOG_MSG(872204, fia_q4_state, &fia_quest_state, 87220401);
ezs::transition fia_q4_transition(&fia_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q5, 5, 87220500, esd_get_flag(12039156));
OPEN_GENERIC_DIALOG_MSG(872205, fia_q5_state, &fia_quest_state, 87220501);
ezs::transition fia_q5_transition(&fia_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q6, 6, 87220600, esd_get_flag(12039161));
OPEN_GENERIC_DIALOG_MSG(872206, fia_q6_state, &fia_quest_state, 87220601);
ezs::transition fia_q6_transition(&fia_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(fia_q7, 7, 87220700, esd_compare_inventory(8183, 1, 0));
OPEN_GENERIC_DIALOG_MSG(872207, fia_q7_state, &fia_quest_state, 87220701);
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
    .id = 87220,
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
    .id = 872200,
    .transitions = fia_quest_list_transitions,
};

/*
 * Varre's quest submenu
 */

extern ezs::state varre_quest_state;
extern ezs::state varre_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(varre_quest, 23, 87230000, esd_get_flag(1042369206));
ezs::transition varre_quest_transition(&varre_quest_state, evals::get_talk_list[23]);

ADD_TALK_LIST_DATA_ARGS(varre_q1, 1, 87230100);
OPEN_GENERIC_DIALOG_MSG(872301, varre_q1_state, &varre_quest_state, 87230101);
ezs::transition varre_q1_transition(&varre_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q2, 2, 87230200, esd_get_flag(1035449206));
OPEN_GENERIC_DIALOG_MSG(872302, varre_q2_state, &varre_quest_state, 87230201);
ezs::transition varre_q2_transition(&varre_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q3, 3, 87230300, esd_get_flag(1035449216));
OPEN_GENERIC_DIALOG_MSG(872303, varre_q3_state, &varre_quest_state, 87230301);
ezs::transition varre_q3_transition(&varre_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q4, 4, 87230400, esd_get_flag(1035449225));
OPEN_GENERIC_DIALOG_MSG(872304, varre_q4_state, &varre_quest_state, 87230401);
ezs::transition varre_q4_transition(&varre_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q5, 5, 87230500, esd_get_flag(12059155));
OPEN_GENERIC_DIALOG_MSG(872305, varre_q5_state, &varre_quest_state, 87230501);
ezs::transition varre_q5_transition(&varre_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q6, 6, 87230600, esd_get_flag(12059165));
OPEN_GENERIC_DIALOG_MSG(872306, varre_q6_state, &varre_quest_state, 87230601);
ezs::transition varre_q6_transition(&varre_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(varre_q99, 50, 87239900, esd_get_flag(3183));
OPEN_GENERIC_DIALOG_MSG(872350, varre_q99_state, &varre_quest_state, 87239901);
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
    .id = 87230,
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
    .id = 872300,
    .transitions = varre_quest_list_transitions,
};

/*
 * Millicent's quest submenu
 */

extern ezs::state millicent_quest_state;
extern ezs::state millicent_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(millicent_quest, 24, 87240000, esd_or(esd_get_flag(1050389258), esd_get_flag(1038519256)));
ezs::transition millicent_quest_transition(&millicent_quest_state, evals::get_talk_list[24]);

ADD_TALK_LIST_DATA_ARGS(millicent_q1, 1, 87240100);
OPEN_GENERIC_DIALOG_MSG(872401, millicent_q1_state, &millicent_quest_state, 87240101);
ezs::transition millicent_q1_transition(&millicent_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q2, 2, 87240200, esd_get_flag(1038519256));
OPEN_GENERIC_DIALOG_MSG(872402, millicent_q2_state, &millicent_quest_state, 87240201);
ezs::transition millicent_q2_transition(&millicent_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q3, 3, 87240300, esd_get_flag(1038519257));
OPEN_GENERIC_DIALOG_MSG(872403, millicent_q3_state, &millicent_quest_state, 87240301);
ezs::transition millicent_q3_transition(&millicent_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q4, 4, 87240400, esd_get_flag(1042559205));
OPEN_GENERIC_DIALOG_MSG(872404, millicent_q4_state, &millicent_quest_state, 87240401);
ezs::transition millicent_q4_transition(&millicent_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q5, 5, 87240500, esd_get_flag(1051569255));
OPEN_GENERIC_DIALOG_MSG(872405, millicent_q5_state, &millicent_quest_state, 87240501);
ezs::transition millicent_q5_transition(&millicent_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q6, 6, 87240600, esd_get_flag(15009205));
OPEN_GENERIC_DIALOG_MSG(872406, millicent_q6_state, &millicent_quest_state, 87240601);
ezs::transition millicent_q6_transition(&millicent_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q7, 7, 87240700, esd_and(esd_get_flag(4183), esd_compare_inventory(1250, 1)));
OPEN_GENERIC_DIALOG_MSG(872407, millicent_q7_state, &millicent_quest_state, 87240701);
ezs::transition millicent_q7_transition(&millicent_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q8, 8, 87240800, esd_get_flag(15009210));
OPEN_GENERIC_DIALOG_MSG(872408, millicent_q8_state, &millicent_quest_state, 87240801);
ezs::transition millicent_q8_transition(&millicent_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(millicent_q99, 50, 87249900, esd_get_flag(4183));
OPEN_GENERIC_DIALOG_MSG(872450, millicent_q99_state, &millicent_quest_state, 87249901);
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
    .id = 87240,
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
    .id = 872400,
    .transitions = millicent_quest_list_transitions,
};

/*
 * Jar Bairn's quest submenu
 */

extern ezs::state jarbairn_quest_state;
extern ezs::state jarbairn_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_quest, 25, 87250000, esd_or(esd_get_flag(1039449255), esd_get_flag(1039449256)));
ezs::transition jarbairn_quest_transition(&jarbairn_quest_state, evals::get_talk_list[25]);

ADD_TALK_LIST_DATA_ARGS(jarbairn_q1, 1, 87250100);
OPEN_GENERIC_DIALOG_MSG(872501, jarbairn_q1_state, &jarbairn_quest_state, 87250101);
ezs::transition jarbairn_q1_transition(&jarbairn_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_q2, 2, 87250200, esd_get_flag(1039449263));
OPEN_GENERIC_DIALOG_MSG(872502, jarbairn_q2_state, &jarbairn_quest_state, 87250201);
ezs::transition jarbairn_q2_transition(&jarbairn_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_q3, 3, 87250300, esd_get_flag(1039449270));
OPEN_GENERIC_DIALOG_MSG(872503, jarbairn_q3_state, &jarbairn_quest_state, 87250301);
ezs::transition jarbairn_q3_transition(&jarbairn_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_q4, 4, 87250400, esd_get_flag(1039449289));
OPEN_GENERIC_DIALOG_MSG(872504, jarbairn_q4_state, &jarbairn_quest_state, 87250401);
ezs::transition jarbairn_q4_transition(&jarbairn_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(jarbairn_q99, 50, 87259900, esd_get_flag(3823));
OPEN_GENERIC_DIALOG_MSG(872550, jarbairn_q99_state, &jarbairn_quest_state, 87259901);
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
    .id = 87250,
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
    .id = 872500,
    .transitions = jarbairn_quest_list_transitions,
};

/*
 * Corhyn's quest submenu
 */

extern ezs::state corhyn_quest_state;
extern ezs::state corhyn_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_quest, 26, 87260000, esd_get_flag(11109855));
ezs::transition corhyn_quest_transition(&corhyn_quest_state, evals::get_talk_list[26]);

ADD_TALK_LIST_DATA_ARGS(corhyn_q1, 1, 87260100);
OPEN_GENERIC_DIALOG_MSG(872601, corhyn_q1_state, &corhyn_quest_state, 87260101);
ezs::transition corhyn_q1_transition(&corhyn_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q2, 2, 87260200, esd_get_flag(11109859));
OPEN_GENERIC_DIALOG_MSG(872602, corhyn_q2_state, &corhyn_quest_state, 87260201);
ezs::transition corhyn_q2_transition(&corhyn_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q3, 3, 87260300, esd_get_flag(1040529255));
OPEN_GENERIC_DIALOG_MSG(872603, corhyn_q3_state, &corhyn_quest_state, 87260301);
ezs::transition corhyn_q3_transition(&corhyn_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q4, 4, 87260400, esd_or(esd_get_flag(1040529258), esd_get_flag(1040529259)));
OPEN_GENERIC_DIALOG_MSG(872604, corhyn_q4_state, &corhyn_quest_state, 87260401);
ezs::transition corhyn_q4_transition(&corhyn_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q5, 5, 87260500, esd_get_flag(1040529259));
OPEN_GENERIC_DIALOG_MSG(872605, corhyn_q5_state, &corhyn_quest_state, 87260501);
ezs::transition corhyn_q5_transition(&corhyn_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q6, 6, 87260600, esd_get_flag(1040549205));
OPEN_GENERIC_DIALOG_MSG(872606, corhyn_q6_state, &corhyn_quest_state, 87260601);
ezs::transition corhyn_q6_transition(&corhyn_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q7, 7, 87260700, esd_get_flag(11109881));
OPEN_GENERIC_DIALOG_MSG(872607, corhyn_q7_state, &corhyn_quest_state, 87260701);
ezs::transition corhyn_q7_transition(&corhyn_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q8, 8, 87260800, esd_get_flag(11009555));
OPEN_GENERIC_DIALOG_MSG(872608, corhyn_q8_state, &corhyn_quest_state, 87260801);
ezs::transition corhyn_q8_transition(&corhyn_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q9, 9, 87260900, esd_get_flag(1051569355));
OPEN_GENERIC_DIALOG_MSG(872609, corhyn_q9_state, &corhyn_quest_state, 87260901);
ezs::transition corhyn_q9_transition(&corhyn_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q10, 10, 87261000, esd_compare_inventory(8182, 1));
OPEN_GENERIC_DIALOG_MSG(8726010, corhyn_q10_state, &corhyn_quest_state, 87261001);
ezs::transition corhyn_q10_transition(&corhyn_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(corhyn_q99, 50, 87269900, esd_get_flag(4203));
OPEN_GENERIC_DIALOG_MSG(872650, corhyn_q99_state, &corhyn_quest_state, 87269901);
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
    .id = 87260,
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
    .id = 872600,
    .transitions = corhyn_quest_list_transitions,
};

/*
 * Latenna's quest submenu
 */

extern ezs::state latenna_quest_state;
extern ezs::state latenna_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(latenna_quest, 27, 87270000, esd_get_flag(1035429209));
ezs::transition latenna_quest_transition(&latenna_quest_state, evals::get_talk_list[27]);

ADD_TALK_LIST_DATA_ARGS(latenna_q1, 1, 87270100);
OPEN_GENERIC_DIALOG_MSG(872701, latenna_q1_state, &latenna_quest_state, 87270101);
ezs::transition latenna_q1_transition(&latenna_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(latenna_q2, 2, 87270200, esd_get_flag(1036419207));
OPEN_GENERIC_DIALOG_MSG(872702, latenna_q2_state, &latenna_quest_state, 87270201);
ezs::transition latenna_q2_transition(&latenna_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(latenna_q3, 3, 87270300, esd_or(esd_get_flag(1051569301), esd_get_flag(1051562720)));
OPEN_GENERIC_DIALOG_MSG(872703, latenna_q3_state, &latenna_quest_state, 87270301);
ezs::transition latenna_q3_transition(&latenna_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(latenna_q4, 4, 87270400, esd_get_flag(1047589206));
OPEN_GENERIC_DIALOG_MSG(872704, latenna_q4_state, &latenna_quest_state, 87270401);
ezs::transition latenna_q4_transition(&latenna_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(latenna_q99, 50, 87279900, esd_get_flag(4103));
OPEN_GENERIC_DIALOG_MSG(872750, latenna_q99_state, &latenna_quest_state, 87279901);
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
    .id = 87270,
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
    .id = 872700,
    .transitions = latenna_quest_list_transitions,
};

/*
 * Bernahl's quest submenu
 */

extern ezs::state bernahl_quest_state;
extern ezs::state bernahl_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_quest, 28, 87280000, esd_or(esd_get_flag(1042382713), esd_or(esd_get_flag(16009455), esd_get_flag(16009456))));
ezs::transition bernahl_quest_transition(&bernahl_quest_state, evals::get_talk_list[28]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q1, 1, 87280100, esd_get_flag(1042382713));
OPEN_GENERIC_DIALOG_MSG(872801, bernahl_q1_state, &bernahl_quest_state, 87280101);
ezs::transition bernahl_q1_transition(&bernahl_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q2, 2, 87280200, esd_or(esd_get_flag(16009455), esd_get_flag(16009456)));
OPEN_GENERIC_DIALOG_MSG(872802, bernahl_q2_state, &bernahl_quest_state, 87280201);
ezs::transition bernahl_q2_transition(&bernahl_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q3, 3, 87280300, esd_get_flag(16009457));
OPEN_GENERIC_DIALOG_MSG(872803, bernahl_q3_state, &bernahl_quest_state, 87280301);
ezs::transition bernahl_q3_transition(&bernahl_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q4, 4, 87280400, esd_get_flag(16009458));
OPEN_GENERIC_DIALOG_MSG(872804, bernahl_q4_state, &bernahl_quest_state, 87280401);
ezs::transition bernahl_q4_transition(&bernahl_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q5, 5, 87280500, esd_get_flag(7605));
OPEN_GENERIC_DIALOG_MSG(872805, bernahl_q5_state, &bernahl_quest_state, 87280501);
ezs::transition bernahl_q5_transition(&bernahl_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q6, 6, 87280600, esd_get_flag(16009461));
OPEN_GENERIC_DIALOG_MSG(872806, bernahl_q6_state, &bernahl_quest_state, 87280601);
ezs::transition bernahl_q6_transition(&bernahl_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q7, 7, 87280700, esd_get_flag(16009460));
OPEN_GENERIC_DIALOG_MSG(872807, bernahl_q7_state, &bernahl_quest_state, 87280701);
ezs::transition bernahl_q7_transition(&bernahl_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q8, 8, 87280800, esd_and(esd_get_flag(3883), esd_compare_inventory(2080, 1)));
OPEN_GENERIC_DIALOG_MSG(872808, bernahl_q8_state, &bernahl_quest_state, 87280801);
ezs::transition bernahl_q8_transition(&bernahl_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(bernahl_q99, 50, 87289900, esd_get_flag(3883));
OPEN_GENERIC_DIALOG_MSG(872850, bernahl_q99_state, &bernahl_quest_state, 87289901);
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
    .id = 87280,
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
    .id = 872800,
    .transitions = bernahl_quest_list_transitions,
};

/*
 * Ansbach's quest submenu
 */

extern ezs::state ansbach_quest_state;
extern ezs::state ansbach_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_quest, 29, 87290000, esd_or(esd_get_flag(2046429355), esd_get_flag(2045429206)));
ezs::transition ansbach_quest_transition(&ansbach_quest_state, evals::get_talk_list[29]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q1, 1, 87290100, esd_get_flag(2046429355));
OPEN_GENERIC_DIALOG_MSG(872901, ansbach_q1_state, &ansbach_quest_state, 87290101);
ezs::transition ansbach_q1_transition(&ansbach_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q2, 2, 87290200, esd_get_flag(2045429206));
OPEN_GENERIC_DIALOG_MSG(872902, ansbach_q2_state, &ansbach_quest_state, 87290201);
ezs::transition ansbach_q2_transition(&ansbach_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q3, 3, 87290300, esd_get_flag(2046429365));
OPEN_GENERIC_DIALOG_MSG(872903, ansbach_q3_state, &ansbach_quest_state, 87290301);
ezs::transition ansbach_q3_transition(&ansbach_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q4, 4, 87290400, esd_get_flag(2045429213));
OPEN_GENERIC_DIALOG_MSG(872904, ansbach_q4_state, &ansbach_quest_state, 87290401);
ezs::transition ansbach_q4_transition(&ansbach_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q5, 5, 87290500, esd_get_flag(21019305));
OPEN_GENERIC_DIALOG_MSG(872905, ansbach_q5_state, &ansbach_quest_state, 87290501);
ezs::transition ansbach_q5_transition(&ansbach_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q6, 6, 87290600, esd_get_flag(21019316));
OPEN_GENERIC_DIALOG_MSG(872906, ansbach_q6_state, &ansbach_quest_state, 87290601);
ezs::transition ansbach_q6_transition(&ansbach_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q7, 7, 87290700, esd_get_flag(21019360));
OPEN_GENERIC_DIALOG_MSG(872907, ansbach_q7_state, &ansbach_quest_state, 87290701);
ezs::transition ansbach_q7_transition(&ansbach_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q8, 8, 87290800, esd_or(esd_compare_inventory(2008014, 1), esd_get_flag(21019310)));
OPEN_GENERIC_DIALOG_MSG(872908, ansbach_q8_state, &ansbach_quest_state, 87290801);
ezs::transition ansbach_q8_transition(&ansbach_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q9, 9, 87290900, esd_get_flag(21019310));
OPEN_GENERIC_DIALOG_MSG(872909, ansbach_q9_state, &ansbach_quest_state, 87290901);
ezs::transition ansbach_q9_transition(&ansbach_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q10, 10, 87291000, esd_get_flag(21019323));
OPEN_GENERIC_DIALOG_MSG(8729010, ansbach_q10_state, &ansbach_quest_state, 87291001);
ezs::transition ansbach_q10_transition(&ansbach_q10_state, evals::get_talk_list[10]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q11, 11, 87291100, esd_get_flag(21019363));
OPEN_GENERIC_DIALOG_MSG(872911, ansbach_q11_state, &ansbach_quest_state, 87291101);
ezs::transition ansbach_q11_transition(&ansbach_q11_state, evals::get_talk_list[11]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q12, 12, 87291200, esd_get_flag(21019321));
OPEN_GENERIC_DIALOG_MSG(872912, ansbach_q12_state, &ansbach_quest_state, 87291201);
ezs::transition ansbach_q12_transition(&ansbach_q12_state, evals::get_talk_list[12]);

ADD_TALK_LIST_IF_DATA_ARGS(ansbach_q13, 13, 87291300, esd_get_flag(20019211));
OPEN_GENERIC_DIALOG_MSG(872913, ansbach_q13_state, &ansbach_quest_state, 87291301);
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
    .id = 87290,
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
    .id = 872900,
    .transitions = ansbach_quest_list_transitions,
};

/*
 * Hornsent's quest submenu
 */

extern ezs::state hornsent_quest_state;
extern ezs::state hornsent_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_quest, 31, 87310000, esd_or(esd_get_flag(2048459278), esd_and(esd_get_flag(2046429210), esd_and(esd_not(esd_get_flag(2048459278)), esd_not(esd_get_flag(21019205))))));
ezs::transition hornsent_quest_transition(&hornsent_quest_state, evals::get_talk_list[31]);

ADD_TALK_LIST_DATA_ARGS(hornsent_q1, 1, 87310100);
OPEN_GENERIC_DIALOG_MSG(873101, hornsent_q1_state, &hornsent_quest_state, 87310101);
ezs::transition hornsent_q1_transition(&hornsent_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_q2, 2, 87310200, esd_get_flag(2048459278));
OPEN_GENERIC_DIALOG_MSG(873102, hornsent_q2_state, &hornsent_quest_state, 87310201);
ezs::transition hornsent_q2_transition(&hornsent_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_q3, 3, 87310300, esd_get_flag(2048459261));
OPEN_GENERIC_DIALOG_MSG(873103, hornsent_q3_state, &hornsent_quest_state, 87310301);
ezs::transition hornsent_q3_transition(&hornsent_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_q4, 4, 87310400, esd_get_flag(21012703));
OPEN_GENERIC_DIALOG_MSG(873104, hornsent_q4_state, &hornsent_quest_state, 87310401);
ezs::transition hornsent_q4_transition(&hornsent_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(hornsent_q5, 5, 87310500, esd_get_flag(21019207));
OPEN_GENERIC_DIALOG_MSG(873105, hornsent_q5_state, &hornsent_quest_state, 87310501);
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
    .id = 87310,
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
    .id = 873100,
    .transitions = hornsent_quest_list_transitions,
};

/*
 * Queelign's quest submenu
 */

extern ezs::state queelign_quest_state;
extern ezs::state queelign_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(queelign_quest, 32, 87320000, esd_get_flag(21009212));
ezs::transition queelign_quest_transition(&queelign_quest_state, evals::get_talk_list[32]);

ADD_TALK_LIST_DATA_ARGS(queelign_q1, 1, 87320100);
OPEN_GENERIC_DIALOG_MSG(873201, queelign_q1_state, &queelign_quest_state, 87320101);
ezs::transition queelign_q1_transition(&queelign_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(queelign_q2, 2, 87320200, esd_get_flag(21009210));
OPEN_GENERIC_DIALOG_MSG(873202, queelign_q2_state, &queelign_quest_state, 87320201);
ezs::transition queelign_q2_transition(&queelign_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(queelign_q3, 3, 87320300, esd_get_flag(21009211));
OPEN_GENERIC_DIALOG_MSG(873203, queelign_q3_state, &queelign_quest_state, 87320301);
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
    .id = 87320,
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
    .id = 873200,
    .transitions = queelign_quest_list_transitions,
};

/*
 * Ymir's quest submenu
 */

extern ezs::state ymir_quest_state;
extern ezs::state ymir_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(ymir_quest, 33, 87330000, esd_get_flag(2051459220));
ezs::transition ymir_quest_transition(&ymir_quest_state, evals::get_talk_list[33]);

ADD_TALK_LIST_DATA_ARGS(ymir_q1, 1, 87330100);
OPEN_GENERIC_DIALOG_MSG(873301, ymir_q1_state, &ymir_quest_state, 87330101);
ezs::transition ymir_q1_transition(&ymir_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q2, 2, 87330200, esd_get_flag(2050400600));
OPEN_GENERIC_DIALOG_MSG(873302, ymir_q2_state, &ymir_quest_state, 87330201);
ezs::transition ymir_q2_transition(&ymir_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q3, 3, 87330300, esd_or(esd_get_flag(2051459235), esd_get_flag(2051459237)));
OPEN_GENERIC_DIALOG_MSG(873303, ymir_q3_state, &ymir_quest_state, 87330301);
ezs::transition ymir_q3_transition(&ymir_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q4, 4, 87330400, esd_get_flag(2053460600));
OPEN_GENERIC_DIALOG_MSG(873304, ymir_q4_state, &ymir_quest_state, 87330401);
ezs::transition ymir_q4_transition(&ymir_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q5, 5, 87330500, esd_or(esd_get_flag(2051459208), esd_get_flag(2051459247)));
OPEN_GENERIC_DIALOG_MSG(873305, ymir_q5_state, &ymir_quest_state, 87330501);
ezs::transition ymir_q5_transition(&ymir_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q6, 6, 87330600, esd_or(esd_get_flag(4326), esd_get_flag(2051459234)));
OPEN_GENERIC_DIALOG_MSG(873306, ymir_q6_state, &ymir_quest_state, 87330601);
ezs::transition ymir_q6_transition(&ymir_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q7, 7, 87330700, esd_get_flag(2051459743));
OPEN_GENERIC_DIALOG_MSG(873307, ymir_q7_state, &ymir_quest_state, 87330701);
ezs::transition ymir_q7_transition(&ymir_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(ymir_q8, 8, 87330800, esd_get_flag(2051459744));
OPEN_GENERIC_DIALOG_MSG(873308, ymir_q8_state, &ymir_quest_state, 87330801);
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
    .id = 87330,
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
    .id = 873300,
    .transitions = ymir_quest_list_transitions,
};

/*
 * Igon's quest submenu
 */

extern ezs::state igon_quest_state;
extern ezs::state igon_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(igon_quest, 34, 87340000, esd_get_flag(2048429208));
ezs::transition igon_quest_transition(&igon_quest_state, evals::get_talk_list[34]);

ADD_TALK_LIST_DATA_ARGS(igon_q1, 1, 87340100);
OPEN_GENERIC_DIALOG_MSG(873401, igon_q1_state, &igon_quest_state, 87340101);
ezs::transition igon_q1_transition(&igon_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(igon_q2, 2, 87340200, esd_get_flag(2049399706));
OPEN_GENERIC_DIALOG_MSG(873402, igon_q2_state, &igon_quest_state, 87340201);
ezs::transition igon_q2_transition(&igon_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(igon_q3, 3, 87340300, esd_get_flag(2052409207));
OPEN_GENERIC_DIALOG_MSG(873403, igon_q3_state, &igon_quest_state, 87340301);
ezs::transition igon_q3_transition(&igon_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(igon_q4, 4, 87340400, esd_get_flag(2054399208));
OPEN_GENERIC_DIALOG_MSG(873404, igon_q4_state, &igon_quest_state, 87340401);
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
    .id = 87340,
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
    .id = 873400,
    .transitions = igon_quest_list_transitions,
};

/*
 * St. Trina's quest submenu
 */

extern ezs::state trina_quest_state;
extern ezs::state trina_quest_list_state;

ADD_TALK_LIST_IF_DATA_ARGS(trina_quest, 35, 87350000, esd_get_flag(22009255));
ezs::transition trina_quest_transition(&trina_quest_state, evals::get_talk_list[35]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q1, 1, 87350100, esd_get_flag(2048439223));
OPEN_GENERIC_DIALOG_MSG(873501, trina_q1_state, &trina_quest_state, 87350101);
ezs::transition trina_q1_transition(&trina_q1_state, evals::get_talk_list[1]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q2, 2, 87350200, esd_get_flag(22009255));
OPEN_GENERIC_DIALOG_MSG(873502, trina_q2_state, &trina_quest_state, 87350201);
ezs::transition trina_q2_transition(&trina_q2_state, evals::get_talk_list[2]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q3, 3, 87350300, esd_get_flag(2048439228));
OPEN_GENERIC_DIALOG_MSG(873503, trina_q3_state, &trina_quest_state, 87350301);
ezs::transition trina_q3_transition(&trina_q3_state, evals::get_talk_list[3]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q4, 4, 87350400, esd_get_flag(22009218));
OPEN_GENERIC_DIALOG_MSG(873504, trina_q4_state, &trina_quest_state, 87350401);
ezs::transition trina_q4_transition(&trina_q4_state, evals::get_talk_list[4]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q5, 5, 87350500, esd_get_flag(22000710));
OPEN_GENERIC_DIALOG_MSG(873505, trina_q5_state, &trina_quest_state, 87350501);
ezs::transition trina_q5_transition(&trina_q5_state, evals::get_talk_list[5]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q6, 6, 87350600, esd_get_flag(22009221));
OPEN_GENERIC_DIALOG_MSG(873506, trina_q6_state, &trina_quest_state, 87350601);
ezs::transition trina_q6_transition(&trina_q6_state, evals::get_talk_list[6]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q7, 7, 87350700, esd_get_flag(22009222));
OPEN_GENERIC_DIALOG_MSG(873507, trina_q7_state, &trina_quest_state, 87350701);
ezs::transition trina_q7_transition(&trina_q7_state, evals::get_talk_list[7]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q8, 8, 87350800, esd_get_flag(22009231));
OPEN_GENERIC_DIALOG_MSG(873508, trina_q8_state, &trina_quest_state, 87350801);
ezs::transition trina_q8_transition(&trina_q8_state, evals::get_talk_list[8]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q9, 9, 87350900, esd_get_flag(22009235));
OPEN_GENERIC_DIALOG_MSG(873509, trina_q9_state, &trina_quest_state, 87350901);
ezs::transition trina_q9_transition(&trina_q9_state, evals::get_talk_list[9]);

ADD_TALK_LIST_IF_DATA_ARGS(trina_q10, 10, 87351000, esd_get_flag(22009239));
OPEN_GENERIC_DIALOG_MSG(8735010, trina_q10_state, &trina_quest_state, 87351001);
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
    .id = 87350,
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
    .id = 873500,
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
