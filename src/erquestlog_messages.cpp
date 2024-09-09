/**
 * erquestlog_messages.cpp
 *
 * New messages. This determines the message strings uses by the mod, and hooks the message lookup
 * function to return them.
 */
#include "erquestlog_messages.hpp"
#include "erquestlog_config.hpp"
#include "erquestlog_talkscript_utils.hpp"

#include <chrono>
#include <map>
#include <spdlog/spdlog.h>
#include <string>
#include <codecvt>
#include <locale>
#include <thread>

#include "from/messages.hpp"
#include "modutils.hpp"

#include <fstream>
#include <filesystem>

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

std::map<std::string, std::wstring> questlog_strings;

static from::CS::MsgRepositoryImp *msg_repository = nullptr;

static const wchar_t *(*msg_repository_lookup_entry)(from::CS::MsgRepositoryImp *, unsigned int,
                                                     from::msgbnd, int);

std::string wstringToString(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

/**
 * Hook for MsgRepositoryImp::LookupEntry()
 */
static const wchar_t *msg_repository_lookup_entry_detour(from::CS::MsgRepositoryImp *msg_repository,
                                                         unsigned int unknown, from::msgbnd bnd_id,
                                                         int msg_id)
{
    if (bnd_id == from::msgbnd::event_text_for_talk)
    {
        auto result = questlog_strings.find(std::to_string(msg_id));
        if (result != questlog_strings.end())
        {
            //return questlog_strings[std::to_string(msg_id)].c_str();
            return result->second.data();
            //return L"test\ntest&egrave;ù";
        }
    }

    return msg_repository_lookup_entry(msg_repository, unknown, bnd_id, msg_id);
}

// Replace any substring
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

/**
* Read lines from a language file and populates a corresponding map
*/
std::map<std::string, std::wstring> readFileToMap(std::filesystem::path folder, std::string lang) {
    std::map<std::string, std::wstring> dataMap;

    std::string path = (folder / "questlog_lang" / (lang + ".lang")).string();
    std::string default_path = (folder / "questlog_lang" / "english.lang").string();

    std::ifstream file(path);
    //std::wifstream file(path);

    if (!file.is_open()) {
        spdlog::warn("Language \"{}\" not found, using english...", lang);
        file.close();
        file.open(default_path);

        if (!file.is_open()) {
            spdlog::warn("Error opening default english version.");
            return dataMap;
        }
    }

    //std::wstring line;
    std::string line;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    while (std::getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            /*std::string key = wstringToString(line.substr(1, colonPos - 2)); // Remove quotes
            std::wstring value = line.substr(colonPos + 3, line.length() - colonPos - 4); // Remove quotes and space
            dataMap[key] = value;*/
            std::string key = line.substr(1, colonPos - 2); // Remove quotes
            std::string value = line.substr(colonPos + 3, line.length() - colonPos - 4); // Remove quotes and space
            value = ReplaceAll(value, "\\n", "\n");
            dataMap[key] = converter.from_bytes(value);
            //spdlog::info("Found value \"{1}\" for key \"{0}\"", key, wstringToString(value));
        }
    }

    file.close();
    return dataMap;
}

void erquestlog::setup_messages(std::filesystem::path folder)
{
    // Pick the messages to use based on the player's selected language for the game in Steam
    auto language = get_steam_language();

    if(config::lang != "none")
    {
        language = config::lang;
    }
    
    questlog_strings = readFileToMap(folder, language);

    //spdlog::info("Checking string 82350900: \"{}\"", wstringToString(questlog_strings["82350900"]));
    
    /*auto bani = esd_get_flag_value(1044399206, 9, 1);
    spdlog::info("esd_get_flag_value:");

    for(unsigned char b : bani){
        spdlog::info("{}", b+0);
        if(b==0xa1) break;
    }
    auto bani2 = esd_get_flag(4700);
    spdlog::info("esd_get_flag:");

    for(unsigned char b : bani2){
        spdlog::info("{}", b+0);
        if(b==0xa1) break;
    }

    auto bani3 = esd_and(esd_get_flag(4700), esd_compare_inventory(2962, 1));
    spdlog::info("esd_and:");

    for(unsigned char b : bani3){
        spdlog::info("{}", b+0);
        if(b==0xa1) break;
    }

    /*spdlog::info("Check esd_get_talk_list: {}",
            esd_get_talk_list(1).data
        );*/
        

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