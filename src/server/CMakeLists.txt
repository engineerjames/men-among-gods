set(target server)

set( sources
    area.c
    build.c
    ccp_driver.c
    cgilib/cgi-lib.c
    cgilib/html-lib.c
    cgilib/list-lib.c
    cityattack.c
    driver.c
    driver_etc.c
    driver_generic.c
    helper.c
    lab9.c
    look_driver.c
    npc_malte.c
    path.c
    populate.c
    server.c
    skill.c
    skill_driver.c
    stunrun.c
    svr_act.c
    svr_disk.c
    svr_do.c
    svr_effect.c
    svr_glob.c
    svr_god.c
    svr_tick.c
    talk.c
    use_driver.c
)

set( headers
    cgilib/cgi-lib.h
    cgilib/cgi-priv.h
    cgilib/html-lib.h
    cgilib/list-lib.h
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
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cgilib)
target_link_libraries(${target} PRIVATE -m32 z m crypt)
target_compile_options(${target} PRIVATE -Wall -Wextra -m32 -w -fno-strict-aliasing)

# Need the .dat files accessible / copied out to the server build directory
add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory  $<TARGET_FILE_DIR:${target}>/.dat
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/.dat/*.dat $<TARGET_FILE_DIR:${target}>/.dat)

# CGI Output
set(target acct)
add_executable(${target} acct.c skill.c gendefs.h data.h)
target_compile_options(${target} PRIVATE -m32)
target_include_directories(${target} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cgilib)
target_link_libraries(${target} PRIVATE -m32 ${CMAKE_CURRENT_SOURCE_DIR}/cgilib/cgi-lib.a)
set_target_properties(${target} PROPERTIES SUFFIX ".cgi")

set(target info)
add_executable(${target} info.c gendefs.h data.h)
target_compile_options(${target} PRIVATE -m32)
target_link_libraries(${target} PRIVATE -m32)
set_target_properties(${target} PROPERTIES SUFFIX ".cgi")