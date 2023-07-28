set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/server)

set(target server)

set( sources
    area.cpp
    build.cpp
    ccp_driver.cpp
    cityattack.cpp
    driver.cpp
    driver_etc.cpp
    driver_generic.cpp
    helper.cpp
    lab9.cpp
    look_driver.cpp
    npc_malte.cpp
    path.cpp
    populate.cpp
    server.cpp
    skill_driver.cpp
    stunrun.cpp
    svr_act.cpp
    svr_disk.cpp
    svr_do.cpp
    svr_effect.cpp
    svr_glob.cpp
    svr_god.cpp
    svr_tick.cpp
    talk.cpp
    use_driver.cpp
)

set( headers
    client.h
    data.h
    driver.h
    funcs.h
    gendefs.h
    globals.h
    lab9.h
    macros.h
    npc.h
    numbers.h
    server.h
)

# TODO: Add respawn / password executables?
add_executable(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE -m32 z m crypt common32 njson)
target_compile_options(${target} PRIVATE -Wall -Wextra -m32 -w -fno-strict-aliasing)

# Need the .dat files accessible / copied out to the server build directory
add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory  $<TARGET_FILE_DIR:${target}>/.dat
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/.dat/*.dat $<TARGET_FILE_DIR:${target}>/.dat)