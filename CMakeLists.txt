cmake_minimum_required(VERSION 3.28.1)

set(CMAKE_GENERATOR_PLATFORM x64)

project(EldenRingQuestLogMod
  VERSION   "1.0.0"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include(FetchContent)

FetchContent_Declare(minhook
  GIT_REPOSITORY        https://github.com/TsudaKageyu/minhook.git
  GIT_TAG               f5485b8454544c2f034c78f8f127c1d03dea3636)

FetchContent_Declare(pattern16
  GIT_REPOSITORY        https://github.com/Dasaav-dsv/Pattern16.git
  GIT_TAG               728eac543cee7e7bf6fda445d7db06e3dc8a61d0
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         "")

FetchContent_Declare(mini
  GIT_REPOSITORY        https://github.com/metayeti/mINI.git
  GIT_TAG               0.9.15
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         "")

set(SPDLOG_DISABLE_DEFAULT_LOGGER ON)
set(SPDLOG_USE_STD_FORMAT ON)
FetchContent_Declare(spdlog
  GIT_REPOSITORY        https://github.com/gabime/spdlog.git
  GIT_TAG               v1.14.1)

# # Set iterator debug level to 0 for ELDEN RING ABI compatibility
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

FetchContent_MakeAvailable(minhook pattern16 mini spdlog)

add_library(pattern16 INTERFACE)
target_include_directories(pattern16 INTERFACE ${pattern16_SOURCE_DIR}/include)

add_library(mini INTERFACE)
target_include_directories(mini INTERFACE ${mini_SOURCE_DIR}/src)

add_library(steamapi STATIC IMPORTED GLOBAL)
set_property(TARGET steamapi APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(steamapi PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG CXX
        IMPORTED_LOCATION_DEBUG steam_api64.lib)

add_library(EldenRingQuestLogMod SHARED
  src/from/talk_commands.hpp
  src/from/param_lookup.hpp
  src/from/messages.hpp
  src/from/game_data.hpp
  src/from/ezstate.hpp
  src/from/params.hpp
  src/from/params.cpp
  src/modutils.hpp
  src/modutils.cpp
  src/erquestlog_config.hpp
  src/erquestlog_config.cpp
  src/erquestlog_evaluators.cpp
  src/erquestlog_talkscript.hpp
  src/erquestlog_talkscript.cpp
  src/erquestlog_talkscript_utils.hpp
  src/erquestlog_quests.hpp
  src/erquestlog_messages.hpp
  src/erquestlog_messages.cpp
  src/dllmain.cpp)

set_target_properties(EldenRingQuestLogMod PROPERTIES OUTPUT_NAME "erquestlog")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_definitions(-DPROJECT_VERSION="${CMAKE_PROJECT_VERSION}")

add_custom_command(TARGET EldenRingQuestLogMod POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:EldenRingQuestLogMod>
  ${CMAKE_SOURCE_DIR}/LICENSE.txt
  ${CMAKE_SOURCE_DIR}/erquestlog.ini
  COMMAND_EXPAND_LISTS)

add_custom_command(TARGET EldenRingQuestLogMod POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/questlog_lang
  $<TARGET_FILE_DIR:EldenRingQuestLogMod>/questlog_lang)

target_link_libraries(EldenRingQuestLogMod
  minhook
  pattern16
  mini
  spdlog
  ${CMAKE_SOURCE_DIR}/steam_api64.lib)
