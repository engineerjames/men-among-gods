cmake_minimum_required(VERSION 3.14)

project(men-among-gods C CXX ASM)

# Tested with Visual Studio Community 2017 Release - amd64_x86
if (WIN32)
  set(Boost_DIR C:/Boost/boost_1_77_0/stage/lib/cmake/Boost-1.77.0)
endif()
find_package(Boost COMPONENTS serialization REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
  set(PROJECT_CXX_FLAGS /W3 /WX)
  set(PROJECT_CXX_DEFINITIONS -D_CRT_SECURE_NO_WARNINGS)
else()
  set( PROJECT_CXX_FLAGS -Wall -Wextra -Wshadow -Werror -Wpedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wfloat-equal)
endif()

add_subdirectory(src/new_client)

if (NOT WIN32)
  add_subdirectory(src/server)
endif()