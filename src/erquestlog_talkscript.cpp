/**
 * erquestlog_talkscript.cpp
 *
 * Talkscript patching hook. This intercepts the start of Kalé's dialogue tree, and patches it to
 * include more options for modded shops.
 */
#include "erquestlog_talkscript.hpp"
#include "gamestrings.cpp"

#include <algorithm>
#include <array>
#include <span>
#include <spdlog/spdlog.h>

#include "erquestlog_messages.hpp"
#include "erquestlog_shops.hpp"
#include "erquestlog_talkscript_utils.hpp"
#include "from/ezstate.hpp"
#include "from/talk_commands.hpp"
#include "modutils.hpp"

static constexpr unsigned char get_talk_list_entry_result_function = 23;

static std::array<from::EzState::transition *, 100> patched_transition_array;

static std::array<from::EzState::event, 100> patched_events;
static std::array<from::EzState::transition *, 100> patched_transitions;
static std::array<from::EzState::transition *, 100> test_tr;

unsigned char tr;

/**
 * Check if the given state group is the main menu for a merchant, and patch it to contain the
 * modded menu options
 */
static bool patch_states(from::EzState::state_group *state_group)
{
    from::EzState::state *add_menu_state = nullptr;
    from::EzState::event *add_menu_event = nullptr;
    from::EzState::event *add_menu1_event = nullptr;
    from::EzState::state *menu_transition_state = nullptr;

    bool bani = false;

    for (auto &state : state_group->states)
    {
        if(0x7fffffff - state_group->id == 31 ||
            0x7fffffff - state_group->id == 33)
        {
            for (auto &event : state.entry_events)
            {
                spdlog::debug("Event id: {0}, bank: {1}", 
                                event.command.id,
                                event.command.bank
                            );
                
                if (event.command == from::talk_command::add_talk_list_data ||
                    event.command == from::talk_command::add_talk_list_data_if
                )
                {
                    
                    if (event.command == from::talk_command::add_talk_list_data)
                    {
                        spdlog::debug("Event add_talk_list_data: state group {0}, index {1}, message {2}",
                                    0x7fffffff - state_group->id, 
                                    get_int_value(event.args[0]),
                                    get_int_value(event.args[1]) //strees.at(get_int_value(event.args[1]))
                                );
                    } else {
                        spdlog::debug("Event add_talk_list_data_if: state group {0}, index {1}, message {2}",
                                    0x7fffffff - state_group->id, 
                                    get_int_value(event.args[1]),
                                    get_int_value(event.args[2]) //strees.at(get_int_value(event.args[1]))
                                );
                    }

                    auto message_id = get_int_value(event.args[1]);
                    if (message_id == erquestlog::event_text_for_talk::sortchest)
                    {
                        add_menu_event = &event;
                        add_menu_state = &state;
                    }
                    else if (message_id == erquestlog::event_text_for_talk::quest_log)
                    {
                        spdlog::debug("Not patching state group x{}, already patched",
                                    0x7fffffff - state_group->id);
                        bani=true;
                        //return true;
                    }
                }
            }

            // Look for the state where we check the chosen menu item and transition to a new state.
            for (auto &transition : state.transitions)
            {   
                spdlog::debug("Parsing state group x{0}, evaluator.size: {1}, evaluator (pure): {2}",
                                        0x7fffffff - state_group->id, 
                                        transition->evaluator.size(), 
                                        transition->evaluator[0]
                                    );

                if (transition->evaluator.size() > 1 &&
                    transition->evaluator[0] - 64 == get_talk_list_entry_result_function)
                {
                    spdlog::debug("Found evaluator!");
                    spdlog::debug("Transition target state: {}", //, pass_events.command: , pass_events.msg: ", 
                                        /*0x7fffffff - state_group->id, 
                                        transition->evaluator.size(), 
                                        transition->evaluator[0],*/
                                        transition->target_state->id
                                        //transition->pass_events[0].command.id,
                                        //get_int_value(transition->pass_events[0].args[1])
                                    );

                    menu_transition_state = &state;
                    break;
                }
            }
        }
    }


    if (!add_menu_event || !menu_transition_state || bani)
    {
        return false;
    }

    spdlog::info("Patching state group x{}", 0x7fffffff - state_group->id);

    // Change the "Purchase"/"Sell" menu options to "Browse Inventory"/"Browse Cut Content"
    /*add_menu1_event->args[0] = browse_inventory_index_value;
    add_menu1_event->args[1] = browse_inventory_message_id_value;*/

    auto &events = add_menu_state->entry_events;

    std::copy(events.begin(), events.end(), patched_events.begin());
    auto new_ev_size = events.size() + 1;
    //patched_events[new_ev_size] = &browse_inventory_event;
    patched_events[new_ev_size - 1] = quest_log;

    spdlog::debug("new_ev_size: {}", new_ev_size);

    events = {patched_events.data(), new_ev_size};

    /*std::copy(transitions.begin(), transitions.end(), patched_transitions.begin());
    auto new_tr_size = transitions.size() + 1;
    patched_transitions[new_tr_size - 1] = &quest_log_transition;

    spdlog::debug("new_tr_size: {}", new_tr_size);

    transitions = {patched_transitions.data(), new_tr_size};*/

    // Add transitions to handle the new menu options.
    auto &transitions = menu_transition_state->transitions;
    auto &tr = transitions[0]->sub_transitions;

    spdlog::debug("Identikit saved transitions [0]: x{0}, evaluator.size: {1}, evaluator (pure): {2}",
                                        0x7fffffff - state_group->id, 
                                        transitions[0]->evaluator.size(), 
                                        transitions[0]->evaluator[0]
                                    );

    spdlog::debug("Identikit saved transitions [1]: x{0}, evaluator.size: {1}, evaluator (pure): {2}",
                                        0x7fffffff - state_group->id, 
                                        transitions[1]->evaluator.size(), 
                                        transitions[1]->evaluator[0]
                                    );

    spdlog::debug("Stats tr: size {0}", tr.size());
    
    std::copy(tr.begin(), tr.end(), patched_transitions.begin());
    auto new_tr_size = tr.size() + 1;
    patched_transitions[new_tr_size - 1] = &quest_log_transition;

    spdlog::debug("new_tr_size: {}", new_tr_size);

    tr = {patched_transitions.data(), new_tr_size};

    return true;
}

static void (*ezstate_enter_state)(from::EzState::state *,
                                   from::EzState::detail::EzStateMachineImpl *, void *);

/**
 * Hook for EzState::state::Enter()
 *
 * Patches merchant dialogue trees to open the shops added by this mod
 */
static void ezstate_enter_state_detour(from::EzState::state *state,
                                       from::EzState::detail::EzStateMachineImpl *machine,
                                       void *unk)
{
    if (state == machine->state_group->initial_state)
    {
        if (patch_states(machine->state_group))
        {
            main_menu_return_transition.target_state = state;
        }
    }

    ezstate_enter_state(state, machine, unk);
}

void erquestlog::setup_talkscript()
{
    modutils::hook(
        {
            .aob = "80 7e 18 00"     // cmp byte ptr [rsi+0x18], 0
                   "74 15"           // je 27
                   "4c 8d 44 24 40"  // lea r8, [rsp+0x40]
                   "48 8b d6"        // mov rdx, rsi
                   "48 8b 4e 20"     // mov rcx, qword ptr [rsi+0x20]
                   "e8 ?? ?? ?? ??", // call EzState::state::Enter
            .offset = 18,
            .relative_offsets = {{1, 5}},
        },
        ezstate_enter_state_detour, ezstate_enter_state);
}
