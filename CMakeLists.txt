cmake_minimum_required(VERSION 3.14)

project(men-among-gods C CXX)
set (CMAKE_CXX_STANDARD 17)

option(ENABLE_CLANG_TIDY "Enable static analysis via clang-tidy" OFF)
option(ENABLE_LOGGING "Enable logging output from new client application" ON)
option(ENABLE_UBSAN "Enable undefined behavior sanitizer" OFF)
option(ENABLE_ASAN "Enable address sanitizer" OFF)

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

# TODO: Update this to an INTERFACE target
include_directories(${CMAKE_BINARY_DIR}/res)

set(install_directory ${CMAKE_BINARY_DIR}/client_files)

if (MSVC)
  list( APPEND PROJECT_CXX_FLAGS /W3 /WX)
  list( APPEND PROJECT_CXX_DEFINITIONS _CRT_SECURE_NO_WARNINGS _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
else()
  list( APPEND PROJECT_CXX_FLAGS -g3 -Wall -Wextra -Wshadow -Werror -Wpedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wfloat-equal)
  if (ENABLE_ASAN)
    message(STATUS "Enabling flags for the address sanitizer.")
    list(APPEND PROJECT_CXX_FLAGS -fsanitize=address -fno-omit-frame-pointer -fno-common)
    list(APPEND PROJECT_CXX_LIBS asan)
  endif()

  if (ENABLE_UBSAN)
    message(STATUS "Enabling flags for the undefined behavior sanitizer.")
    list(APPEND PROJECT_CXX_FLAGS -fsanitize=undefined)
    list(APPEND PROJECT_CXX_LIBS ubsan)
  endif()
endif()

add_subdirectory(src/new_client)
add_subdirectory(src/common)
add_subdirectory(src/test)

add_subdirectory(src/MenAmongGods)

if (NOT WIN32)
  add_subdirectory(src/server)
endif()

add_subdirectory(src/api)
