#include "erquestlog_config.hpp"

#include <mini/ini.h>
#include <spdlog/spdlog.h>

extern bool erquestlog::config::auto_upgrade_weapons = true;

void erquestlog::load_config(const std::filesystem::path &ini_path)
{
    spdlog::info("Loading config from {}", ini_path.string());

    mINI::INIFile file(ini_path.string());
    mINI::INIStructure ini;
    if (file.read(ini) && ini.has("erquestlog"))
    {
        auto &config = ini["erquestlog"];

        if (config.has("auto_upgrade_weapons"))
            config::auto_upgrade_weapons = config["auto_upgrade_weapons"] != "false";

        spdlog::info("auto_upgrade_weapons = {}", config::auto_upgrade_weapons);
    }
}
