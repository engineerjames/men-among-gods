cmake_minimum_required(VERSION 3.14)

project(men-among-gods C CXX)

option(ENABLE_CLANG_TIDY "Enable static analysis via clang-tidy" ON)
option(ENABLE_LOGGING "Enable logging output from new client application" ON)

if (MSVC)
  set(ENABLE_CLANG_TIDY OFF)
endif()

if (ENABLE_CLANG_TIDY)
  message(STATUS "Enabling clang-tidy support")
endif()

if (ENABLE_LOGGING)
  message(STATUS "Enabling logging support")
  list(APPEND PROJECT_CXX_DEFINITIONS ENABLE_LOGGING=1)
endif()

enable_testing()

set(Boost_USE_STATIC_LIBS OFF)
set(BUILD_SHARED_LIBS OFF)
find_package(Boost COMPONENTS unit_test_framework serialization REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RESOURCE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/res)

# Get git revision
execute_process(COMMAND git rev-parse HEAD
                OUTPUT_VARIABLE GIT_REVISION
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_STRIP_TRAILING_WHITESPACE
                )

message(STATUS "Generating ResourceLocations.h...")
message(STATUS "Git revision: ${GIT_REVISION}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ResourceLocations.h.in  ${CMAKE_BINARY_DIR}/res/ResourceLocations.h @ONLY)
include_directories(${CMAKE_BINARY_DIR}/res)

if (MSVC)
  list( APPEND PROJECT_CXX_FLAGS /W3 /WX)
  list( APPEND PROJECT_CXX_DEFINITIONS _CRT_SECURE_NO_WARNINGS _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
else()
  list( APPEND PROJECT_CXX_FLAGS -g3 -Wall -Wextra -Wshadow -Werror -Wpedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wfloat-equal)
endif()

add_subdirectory(src/new_client)

# Currently the unit tests won't link with MinGW for some reason
if (NOT MINGW)
  add_subdirectory(src/test)
endif()

if (NOT WIN32)
  add_subdirectory(src/server)
endif()
