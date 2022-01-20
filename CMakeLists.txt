cmake_minimum_required(VERSION 3.14)

project(men-among-gods C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set( PROJECT_CXX_FLAGS -Wall -Wextra -Wshadow -Werror -Wpedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wfloat-equal)

add_subdirectory(src/new_client)
add_subdirectory(src/server)

# TODO: Add instructions to install SFML development libraries
# libx11-dev libxrandr-dev libopengl-dev libgl-dev libfreetype-dev libopenal-dev libvorbis-dev libflac-dev gdb
