#include "erquestlog_config.hpp"

#include <mini/ini.h>
#include <spdlog/spdlog.h>

extern std::string erquestlog::config::lang = "none";

void erquestlog::load_config(const std::filesystem::path &ini_path)
{
    spdlog::info("Loading config from {}", ini_path.string());

    mINI::INIFile file(ini_path.string());
    mINI::INIStructure ini;
    if (file.read(ini) && ini.has("erquestlog"))
    {
        auto &config = ini["erquestlog"];

        if (config.has("lang"))
            config::lang = config["lang"];

        spdlog::info("Overriding language = {}", config::lang);
    }
}
