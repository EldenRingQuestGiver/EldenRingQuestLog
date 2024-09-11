#pragma once

#include <map>
#include <filesystem>

#include "from/messages.hpp"

namespace erquestlog
{

void setup_messages(std::filesystem::path folder);
const std::wstring_view get_message(from::msgbnd, int);

}
