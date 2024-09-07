#define WIN32_LEAN_AND_MEAN
#include <filesystem>
#include <memory>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <thread>
#include <windows.h>

#include "erquestlog_config.hpp"
#include "erquestlog_messages.hpp"
#include "erquestlog_talkscript.hpp"
#include "from/params.hpp"
#include "modutils.hpp"

static std::thread mod_thread;

static void setup_logger(std::filesystem::path log_file)
{
    auto logger = std::make_shared<spdlog::logger>("questlog");
    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] %^[%l]%$ %v");
    logger->sinks().push_back(
        std::make_shared<spdlog::sinks::daily_file_sink_st>(log_file.string(), 0, 0, false, 5));
    logger->flush_on(spdlog::level::info);

/*#if _DEBUG
    AllocConsole();
    FILE *stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);
    freopen_s(&stream, "CONOUT$", "w", stderr);
    freopen_s(&stream, "CONIN$", "r", stdin);
    logger->sinks().push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
    logger->set_level(spdlog::level::trace);
#endif*/

    spdlog::set_default_logger(logger);
}

static void setup_mod(std::filesystem::path folder)
{
    modutils::initialize();
    from::params::initialize();

    spdlog::info("Sleeping an extra 10s to work potential compatibility issues...");
    std::this_thread::sleep_for(std::chrono::seconds(10));

    spdlog::info("Hooking messages and importing text...");
    erquestlog::setup_messages(folder);

    spdlog::info("Hooking talkscripts...");
    erquestlog::setup_talkscript();

    modutils::enable_hooks();
    spdlog::info("Initialized mod");
}

bool WINAPI DllMain(HINSTANCE dll_instance, unsigned int fdw_reason, void *lpv_reserved)
{
    if (fdw_reason == DLL_PROCESS_ATTACH)
    {
        wchar_t dll_filename[MAX_PATH] = {0};
        GetModuleFileNameW(dll_instance, dll_filename, MAX_PATH);
        auto folder = std::filesystem::path(dll_filename).parent_path();

        setup_logger(folder / "logs" / "erquestlog.log");

        #ifdef PROJECT_VERSION
            spdlog::info("Quest Log version {}", PROJECT_VERSION);
        #endif

        erquestlog::load_config(folder / "erquestlog.ini");

        mod_thread = std::thread([folder]() {
            try
            {
                setup_mod(folder);
            }
            catch (std::runtime_error const &e)
            {
                spdlog::error("Error initializing mod: {}", e.what());
                modutils::deinitialize();
            }
        });
    }
    else if (fdw_reason == DLL_PROCESS_DETACH && lpv_reserved != nullptr)
    {
        try
        {
            mod_thread.join();
            modutils::deinitialize();
            spdlog::info("Deinitialized mod");
        }
        catch (std::runtime_error const &e)
        {
            spdlog::error("Error deinitializing mod: {}", e.what());
            spdlog::shutdown();
            return false;
        }
        spdlog::shutdown();
    }
    return true;
}