#pragma once

#include <filesystem>

namespace erquestlog
{
/**
 * Load user preferences from an .ini file
 */
void load_config(const std::filesystem::path &ini_path);

namespace config
{
/**
 * Detects overriding language to use for the mod
 */
extern std::string lang;

};
};
