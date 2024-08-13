/**
 * erquestlog_talkscript.cpp
 *
 * Talkscript patching hook. This intercepts the start of Kalé's dialogue tree, and patches it to
 * include more options for modded shops.
 */
#include "erquestlog_talkscript.hpp"

#include <algorithm>
#include <array>
#include <span>
#include <spdlog/spdlog.h>

#include "erquestlog_messages.hpp"
#include "erquestlog_talkscript_utils.hpp"
#include "from/ezstate.hpp"
#include "from/talk_commands.hpp"
#include "modutils.hpp"

static constexpr unsigned char get_talk_list_entry_result_function = 23;

static std::array<from::EzState::transition *, 100> patched_transition_array;

static std::array<from::EzState::event, 100> patched_events;
static std::array<from::EzState::transition *, 100> patched_transitions;
static std::array<from::EzState::transition *, 100> test_tr;

/**
 * Check if the given state group is the main menu for a merchant, and patch it to contain the
 * modded menu options
 */
static bool patch_states(from::EzState::state_group *state_group)
{
    from::EzState::state *add_menu_state = nullptr;
    from::EzState::event *add_menu_event = nullptr;
    from::EzState::state *menu_transition_state = nullptr;

    for (auto &state : state_group->states)
    {
        // Look for commands indicating Kalé's main menu state
        for (auto &event : state.entry_events)
        {
            if (event.command == from::talk_command::add_talk_list_data)
            {
                auto message_id = get_int_value(event.args[1]);
                if (message_id == erquestlog::event_text_for_talk::sortchest)
                {
                    add_menu_event = &event;
                    add_menu_state = &state;
                }
                else if (message_id == erquestlog::event_text_for_talk::questlog)
                {
                    spdlog::debug("Not patching state group x{}, already patched",
                                  0x7fffffff - state_group->id);
                    return true;
                }
            }
        }

        // Look for the state where we check the chosen menu item and transition to a new state.
        for (auto &transition : state.transitions)
        {
            if (transition->evaluator.size() > 1 &&
                transition->evaluator[0] - 64 == get_talk_list_entry_result_function)
            {
                menu_transition_state = &state;
                break;
            }
        }
    }

    if (!add_menu_event || !menu_transition_state)
    {
        return false;
    }

    spdlog::info("Patching state group x{}", 0x7fffffff - state_group->id);

    // Add quest log event to grace menu
    auto &events = add_menu_state->entry_events;

    std::copy(events.begin(), events.end(), patched_events.begin());
    auto new_ev_size = events.size() + 1;
    //patched_events[new_ev_size] = &browse_inventory_events;
    patched_events[new_ev_size - 1] = quest_log_event;

    events = {patched_events.data(), new_ev_size};

    // Add transitions to handle the new menu option.
    auto &transitions = menu_transition_state->transitions;
    auto &test_tr = menu_transition_state->transitions;

    std::copy(transitions.begin(), transitions.end(), patched_transitions.begin());
    auto new_tr_size = transitions.size() + 1;
    patched_transitions[new_tr_size - 1] = &quest_log_transition; //&open_quests_next_transition;

    transitions = {patched_transitions.data(), new_tr_size};

    spdlog::info("Patched state group x{}", 0x7fffffff - state_group->id);

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
