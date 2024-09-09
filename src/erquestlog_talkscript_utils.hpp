/**
 * erquestlog_talkscript_utils.hpp
 *
 * Repetitive/tedious data structure setup for modded talkscript states used by
 * erquestlog_talkscript.cpp. This also setups functions to manage ESD bytes.
 */
#include <array>

#include "from/ezstate.hpp"
#include "from/talk_commands.hpp"

#include "erquestlog_messages.hpp"
#include "erquestlog_evaluators.cpp"

namespace
{

typedef std::array<unsigned char, 6> int_value_data;
typedef std::array<unsigned char, 256> esd_expression;

// Aliases
namespace evals = erquestlog::evaluators;
namespace ezs = from::EzState;
namespace talk_comm = from::talk_command;

constexpr char int_to_hex_byte(int value) {
    return static_cast<char>(value & 0xFF);
}

/**
 * Create an ESD expression representing a 4 byte integer
 */
constexpr int_value_data esd_int(int value)
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
 * Create an ESD expression for checking if a game flag is on (value = 1) or off (value = 0)
 */
constexpr esd_expression esd_get_flag(int flag, int value = 1)
{
    return {
        0x4f,
        0x82,
        static_cast<unsigned char>((flag & 0x000000ff)),
        static_cast<unsigned char>((flag & 0x0000ff00) >> 8),
        static_cast<unsigned char>((flag & 0x00ff0000) >> 16),
        static_cast<unsigned char>((flag & 0xff000000) >> 24),
        0x85,
        0x82,
        static_cast<unsigned char>((value & 0x000000ff)),
        static_cast<unsigned char>((value & 0x0000ff00) >> 8),
        static_cast<unsigned char>((value & 0x00ff0000) >> 16),
        static_cast<unsigned char>((value & 0xff000000) >> 24),
        0x95,
        0xa1,
    };
}

/**
 * Create an ESD expression for checking the game flag value
 */
constexpr esd_expression esd_get_flag_value(int flag, int value = 0, int comparison = 0)
{
    //-2: less than; -1: less than or equal to; 0: equal to; 1: greater than or equal to; 2: greater than
    unsigned char comp = 0x95;

    if(comparison == -2){
        //less than
        comp = 0x93;
    }else if(comparison == -1){
        //less than or equal
        comp = 0x91;
    }else if(comparison == 1){
        //greater than or equal
        comp = 0x92;
    }else if(comparison == 2){
        //greater than
        comp = 0x94;
    }

    return {
        0x82,
        0x65,
        0x00,
        0x00,
        0x00,
        0x82,
        static_cast<unsigned char>((flag & 0x000000ff)),
        static_cast<unsigned char>((flag & 0x0000ff00) >> 8),
        static_cast<unsigned char>((flag & 0x00ff0000) >> 16),
        static_cast<unsigned char>((flag & 0xff000000) >> 24),
        0x82,
        0x05,
        0x00,
        0x00,
        0x00,
        0x86,
        0x82,
        static_cast<unsigned char>((value & 0x000000ff)),
        static_cast<unsigned char>((value & 0x0000ff00) >> 8),
        static_cast<unsigned char>((value & 0x00ff0000) >> 16),
        static_cast<unsigned char>((value & 0xff000000) >> 24),
        comp,
        0xa1,
    };
}

/**
 * Create an ESD expression for checking item quantities against a given amount
 */
constexpr esd_expression esd_compare_inventory(int item_flag, int value = 0, int comparison = 0)
{
    //-2: less than; -1: less than or equal to; 0: equal to; 1: greater than or equal to; 2: greater than
    unsigned char comp = 0x95;

    if(comparison == -2){
        //less than
        comp = 0x93;
    }else if(comparison == -1){
        //less than or equal
        comp = 0x91;
    }else if(comparison == 1){
        //greater than or equal
        comp = 0x92;
    }else if(comparison == 2){
        //greater than
        comp = 0x94;
    }

    return {
        0x6f,
        0x82,
        0x03,
        0x00,
        0x00,
        0x00,
        0x82,
        static_cast<unsigned char>((item_flag & 0x000000ff)),
        static_cast<unsigned char>((item_flag & 0x0000ff00) >> 8),
        static_cast<unsigned char>((item_flag & 0x00ff0000) >> 16),
        static_cast<unsigned char>((item_flag & 0xff000000) >> 24),
        0x82,
        0x04,
        0x00,
        0x00,
        0x00,
        0x82,
        0x01,
        0x00,
        0x00,
        0x00,
        0x82,
        0x00,
        0x00,
        0x00,
        0x00,
        0x89,
        0x82,
        static_cast<unsigned char>((value & 0x000000ff)),
        static_cast<unsigned char>((value & 0x0000ff00) >> 8),
        static_cast<unsigned char>((value & 0x00ff0000) >> 16),
        static_cast<unsigned char>((value & 0xff000000) >> 24),
        comp,
        0xa1,
    };
}

/*constexpr std::string esd_get_talk_list(int pos)
{
    return {
        0x57,
        0x84,
        0x82,
        static_cast<unsigned char>((pos & 0x000000ff)),
        static_cast<unsigned char>((pos & 0x0000ff00) >> 8),
        static_cast<unsigned char>((pos & 0x00ff0000) >> 16),
        static_cast<unsigned char>((pos & 0xff000000) >> 24),
        0x95,
        0xa1,
        '\0',
    };
}*/

/*constexpr auto esd_get_talk_list(int pos)
{
    struct StringLiteral {
        char data[10];  // 9 characters + null terminator
        
        constexpr StringLiteral(int pos) : data{
            static_cast<char>(0x57),
            static_cast<char>(0x84),
            static_cast<char>(0x82),
            static_cast<char>(((pos+128) & 0x000000ff)),
            static_cast<char>(((pos+128) & 0x0000ff00) >> 8),
            static_cast<char>(((pos+128) & 0x00ff0000) >> 16),
            static_cast<char>(((pos+128) & 0xff000000) >> 24),
            static_cast<char>(0x95),
            static_cast<char>(0xa1),
            '\0',
        } {}
    };
    
    return StringLiteral(pos);
}*/

/**
 * Create an ESD expression for logic NOT on a given expression
 */
constexpr esd_expression esd_not(esd_expression expr)
{
    auto newExpr = expr;
    int expr_end = newExpr.rend() - std::find(newExpr.rbegin(), newExpr.rend(), 0xa1)-1;

    newExpr[expr_end] = 0x9a;
    newExpr[expr_end + 1] = 0xa1;

    return newExpr;
}

/**
 * Create an ESD expression for logic AND on a given expression
 */
constexpr esd_expression esd_and(esd_expression expr1, esd_expression expr2)
{
    auto newExpr = expr1;
    int expr1_end = expr1.rend() - std::find(expr1.rbegin(), expr1.rend(), 0xa1)-1;
    int expr2_end = expr2.rend() - std::find(expr2.rbegin(), expr2.rend(), 0xa1)-1;

    for (int i = 0; i < expr2_end; i++) {
        newExpr[expr1_end + i] = expr2[i];
    }

    newExpr[expr1_end + expr2_end] = 0x98;
    newExpr[expr1_end + expr2_end + 1] = 0xa1;

    return newExpr;
}

/**
 * Create an ESD expression for logic OR on a given expression
 */
constexpr esd_expression esd_or(esd_expression expr1, esd_expression expr2)
{
    auto newExpr = expr1;
    int expr1_end = expr1.rend() - std::find(expr1.rbegin(), expr1.rend(), 0xa1)-1;
    int expr2_end = expr2.rend() - std::find(expr2.rbegin(), expr2.rend(), 0xa1)-1;

    for (int i = 0; i < expr2_end; i++) {
        newExpr[expr1_end + i] = expr2[i];
    }

    newExpr[expr1_end + expr2_end] = 0x99;
    newExpr[expr1_end + expr2_end + 1] = 0xa1;

    return newExpr;
}

/**
 * Parse an ESD expression containing only a 1 or 4 byte integer
 */
int get_int_value(ezs::arg &arg)
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

/*
 *  Macros
 */

#define ADD_TALK_LIST_DATA_ARGS(name, index, message_id)                                            \
    int_value_data name##_index_value = esd_int(index);                                             \
    int_value_data name##_message_id_value = esd_int(message_id);                                   \
    int_value_data name##_unk_value = esd_int(-1);                                                  \
    std::array<ezs::arg, 3> name##_args = {name##_index_value, name##_message_id_value,   \
                                                     name##_unk_value}                          

#define ADD_TALK_LIST_IF_DATA_ARGS(name, index, message_id, condition)                              \
    int_value_data name##_index_value = esd_int(index);                                             \
    int_value_data name##_message_id_value = esd_int(message_id);                                   \
    int_value_data name##_unk_value = esd_int(-1);                                                  \
    esd_expression name##_condition = condition;                                                    \
    std::array<ezs::arg, 4> name##_args = {name##_condition, name##_index_value,          \
                                                     name##_message_id_value, name##_unk_value}           

#define OPEN_GENERIC_DIALOG_MSG(state_id, name, prev_state, msg)                                    \
    int_value_data name##_v01 = esd_int(7);                                                         \
    int_value_data name##_v02 = esd_int(1);                                                         \
    int_value_data name##_v03 = esd_int(0);                                                         \
    int_value_data name##_msg = esd_int(msg);                                                       \
                                                                                                    \
    std::array<ezs::arg, 5> name##_args = {name##_v01, name##_msg, name##_v02,            \
                                                     name##_v03, name##_v02, };                     \
    std::array<ezs::event, 1> name##_events = {                                           \
        ezs::event{talk_comm::open_generic_dialog, name##_args},                 \
    };                                                                                              \
    ezs::transition name##_transition(prev_state,                                         \
                                    evals::dialog_closed_evaluator);               \
    std::array<ezs::transition *, 1> name##_transitions = {                               \
        &name##_transition,                                                                         \
    };                                                                                              \
    ezs::state name## = {                                                                 \
        .id = state_id,                                                                             \
        .transitions = name##_transitions,                                                          \
        .entry_events = name##_events,                                                              \
    }



// "irina", 8201, 3, esd_get_flag(1045349207), [[nullptr], [esd_get_flag(1043319206)], [...]]
/*#define QUEST_BUILDER(quest_name, base_id, conditions)                                     \
                                                                                                            \
    
    ADD_TALK_LIST_IF_DATA_ARGS(roderika_q5, 5, 82020500, esd_get_flag(11109219));
    OPEN_GENERIC_DIALOG_MSG(820205, roderika_q5_state, &roderika_quest_state, 82020501);
    ezs::transition roderika_q5_transition(&roderika_q5_state, evals::get_talk_list[5]);
                    \
                                                  \
    int idx = 0;      \
    int counter = 0;      \
    std::string root = "";      \
            \
    for (esd_expression step : conditions){               \
        idx++;              \
        counter++;                                              \
        root = quest_name##idx_txt;                                              \
        if(step != nullptr){                 \
            ADD_TALK_LIST_IF_DATA_ARGS(quest_name##idx_txt, idx, base_id * 10000 + idx * 100, step);                                                    \
        } else {                \
            ADD_TALK_LIST_DATA_ARGS(quest_name##idx_txt, idx, base_id * 10000 + idx * 100);          \
        };               \
        OPEN_GENERIC_DIALOG_MSG((base_id * 100 + idx), q_state_root##idx_txt,             \
            &&quest_name##_quest_state, (base_id * 10000 + idx * 100 + 1));                                                    \
        ezs::transition q_trans_root##idx_txt(&q_state_root##idx_txt, evals::get_talk_list[idx]);      \
    }*/



};
