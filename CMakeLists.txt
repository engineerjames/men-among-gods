cmake_minimum_required(VERSION 3.14)

project(men-among-gods C CXX)

enable_testing()

find_package(Boost COMPONENTS unit_test_framework serialization REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
  set(PROJECT_CXX_FLAGS /W3 /WX)
  set(PROJECT_CXX_DEFINITIONS -D_CRT_SECURE_NO_WARNINGS)
else()
  set( PROJECT_CXX_FLAGS -g3 -Wall -Wextra -Wshadow -Werror -Wpedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wfloat-equal)
endif()

add_subdirectory(src/new_client)
add_subdirectory(src/test)

if (NOT WIN32)
  add_subdirectory(src/server)
endif()