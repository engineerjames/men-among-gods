cmake_minimum_required(VERSION 3.14)

project(men-among-gods C CXX)

enable_testing()

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
  set(PROJECT_CXX_FLAGS /W3 /WX)
  set(PROJECT_CXX_DEFINITIONS -D_CRT_SECURE_NO_WARNINGS)
else()
  set( PROJECT_CXX_FLAGS -g3 -Wall -Wextra -Wshadow -Werror -Wpedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wfloat-equal)
endif()

add_subdirectory(src/new_client)

# Currently the unit tests won't link with MinGW for some reason
if (NOT MINGW)
  add_subdirectory(src/test)
endif()

if (NOT WIN32)
  add_subdirectory(src/server)
endif()