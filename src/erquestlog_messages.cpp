/**
 * erquestlog_messages.cpp
 *
 * New messages. This determines the message strings uses by the mod, and hooks the message lookup
 * function to return them.
 */
#include "erquestlog_messages.hpp"

#include <chrono>
#include <map>
#include <spdlog/spdlog.h>
#include <string>
#include <thread>

#include "from/messages.hpp"
#include "modutils.hpp"

struct ISteamApps;
extern "C" __declspec(dllimport) ISteamApps *__cdecl SteamAPI_SteamApps_v008();
extern "C" __declspec(dllimport) const
    char *__cdecl SteamAPI_ISteamApps_GetCurrentGameLanguage(ISteamApps *);

/**
 * Return the player's selected language using the Steamworks SDK
 *
 * https://partner.steamgames.com/doc/api/ISteamApps#GetCurrentGameLanguage
 */
static std::string get_steam_language()
{
    auto steam_api = SteamAPI_SteamApps_v008();
    auto steam_language = SteamAPI_ISteamApps_GetCurrentGameLanguage(steam_api);
    return steam_language != nullptr ? steam_language : "";
}

static const std::map<int, const std::wstring> *mod_event_text_for_talk;

static from::CS::MsgRepositoryImp *msg_repository = nullptr;

static const wchar_t *(*msg_repository_lookup_entry)(from::CS::MsgRepositoryImp *, unsigned int,
                                                     from::msgbnd, int);

/**
 * Hook for MsgRepositoryImp::LookupEntry()
 *
 * Return menu text for the talkscript to open various shops added by the mod, or fall back to
 * the default vanilla messages.
 */
static const wchar_t *msg_repository_lookup_entry_detour(from::CS::MsgRepositoryImp *msg_repository,
                                                         unsigned int unknown, from::msgbnd bnd_id,
                                                         int msg_id)
{
    if (bnd_id == from::msgbnd::event_text_for_talk)
    {
        auto result = mod_event_text_for_talk->find(msg_id);
        if (result != mod_event_text_for_talk->end())
        {
            return result->second.c_str();
        }
    }

    return msg_repository_lookup_entry(msg_repository, unknown, bnd_id, msg_id);
}

void erquestlog::setup_messages()
{
    // Pick the messages to use based on the player's selected language for the game in Steam
    auto language = get_steam_language();
    auto localized_messages = event_text_for_talk_by_lang.find(language);
    if (localized_messages != event_text_for_talk_by_lang.end())
    {
        spdlog::info("Detected language \"{}\"", language);
        mod_event_text_for_talk = &localized_messages->second;
    }
    else
    {
        spdlog::warn("Unknown language \"{}\", defaulting to English", language);
        mod_event_text_for_talk = &event_text_for_talk_by_lang.at("english");
    }

    auto msg_repository_address = modutils::scan<from::CS::MsgRepositoryImp *>({
        .aob = "48 8B 3D ?? ?? ?? ?? 44 0F B6 30 48 85 FF 75",
        .relative_offsets = {{3, 7}},
    });

    while (!(msg_repository = *msg_repository_address))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Hook MsgRepositoryImp::LookupEntry() to return messages added by the mod
    modutils::hook(
        {
            .aob = "8b da"        // mov ebx, edx
                   "44 8b ca"     // mov r9d, edx
                   "33 d2"        // xor edx, edx
                   "48 8b f9"     // mov rdi, rcx
                   "44 8d 42 6f", // lea r8d, [rdx+0x6f]
            .offset = 14,
            .relative_offsets = {{1, 5}},
        },
        msg_repository_lookup_entry_detour, msg_repository_lookup_entry);
}

const std::wstring_view erquestlog::get_message(from::msgbnd bnd_id, int msg_id)
{
    auto result = msg_repository_lookup_entry(msg_repository, 0, bnd_id, msg_id);
    return result ? std::wstring_view(result) : std::wstring_view();
}