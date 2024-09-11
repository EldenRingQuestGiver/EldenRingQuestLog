/**
 * erquestlog_talkscript.cpp
 *
 * Talkscript patching hook. This inserts the questlog menu in the grace dialogue menu
 */
#include "erquestlog_talkscript.hpp"

#include <spdlog/spdlog.h>

#include "erquestlog_quests.hpp"
#include "modutils.hpp"

static constexpr unsigned char get_talk_list_entry_result_function = 23;

static std::array<from::EzState::transition *, 100> patched_transition_array;
static std::array<from::EzState::event, 100> patched_events;
static std::array<from::EzState::transition *, 100> patched_transitions;
static std::array<from::EzState::transition *, 100> test_tr;

static bool is_sort_chest_transition(const from::EzState::transition *transition)
{
    auto target_state = transition->target_state;
    return target_state != nullptr && !target_state->entry_events.empty() &&
           target_state->entry_events[0].command == from::talk_command::open_repository;
}

std::string to_hex_string(std::span<const unsigned char> data) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned char byte : data) {
        if (ss.tellp() > 0) ss << "\\x";  // Add space between bytes
        ss << std::setw(2) << static_cast<int>(byte);
    }
    return "\\x" + ss.str();
}

/**
 * Check if the given state group is the main menu for the grace, and patch it to contain the
 * modded menu options
 */
static bool patch_states(from::EzState::state_group *state_group)
{
    from::EzState::state *add_menu_state = nullptr;
    from::EzState::state *menu_transition_state = nullptr;

    int event_index = -1;
    int transition_index = -1;

    for (auto &state : state_group->states)
    {
        for (int i = 0; i < state.entry_events.size(); i++)
        {
            auto &event = state.entry_events[i];

            /*spdlog::debug("Event id: {0}, bank: {1}", 
                    event.command.id,
                    event.command.bank
                );*/

            if (event.command == from::talk_command::add_talk_list_data)
            {
                auto message_id = get_int_value(event.args[1]);
                if (message_id == 15000395)         // Sort chest
                {
                    spdlog::info("Found sort chest message...");
                    add_menu_state = &state;
                    event_index = i;
                }
                else if (message_id == 87000000)    // Quest Log
                {
                    spdlog::debug("Not patching state group x{}, already patched",
                                  0x7fffffff - state_group->id);
                    return true;
                }
            }
        }

        // Look for the state where we check the chosen menu item and transition to a new state.
        for (int i = 0; i < state.transitions.size(); i++)
        {
            auto &transition = state.transitions[i];
            if (is_sort_chest_transition(transition))
            {
                spdlog::info("Found transition state, id: {}...", 0x7fffffff - state_group->id);
                menu_transition_state = &state;
                transition_index = i;

                /*for (auto &tr : menu_transition_state->transitions)
                {
                    spdlog::debug("Identikit saved transitions [0]: x{0}, evaluator: {1}",
                            tr->target_state->id, 
                            to_hex_string(tr->evaluator)
                        );
                }*/
            }
        }
    }

    if (event_index == -1 || transition_index == -1)
    {
        return false;
    }
    spdlog::info("Patching state group x{}", 0x7fffffff - state_group->id);

    // Add "Ongoing Quests" menu option
    auto &events = add_menu_state->entry_events;

    std::copy(events.begin(), events.end(), patched_events.begin());
    patched_events[events.size()] = quest_log;

    events = {patched_events.data(), events.size() + 1};

    // Add a transition to the "Ongoing Quests" menu
    auto &tr = menu_transition_state->transitions;
    
    std::copy(tr.begin(), tr.begin() + transition_index, patched_transitions.begin());
    std::copy(tr.begin() + transition_index, tr.end(),
              patched_transitions.begin() + transition_index + 1);
    patched_transitions[transition_index] = &quest_log_transition;

    tr = {patched_transitions.data(), tr.size() + 1};
    
    /*spdlog::debug("AFTER PATCH:");
    for (auto &t : tr)
    {
        spdlog::debug("Identikit transition: x{0}, evaluator: {1}",
                t->target_state->id, 
                to_hex_string(t->evaluator)
            );
    }*/

    return true;
}

static void (*ezstate_enter_state)(from::EzState::state *,
                                   from::EzState::detail::EzStateMachineImpl *, void *);

/**
 * Hook for EzState::state::Enter()
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
