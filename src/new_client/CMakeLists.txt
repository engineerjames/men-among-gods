set(SFML_STATIC_LIBRARIES OFF)
find_package(SFML 2.6.1 COMPONENTS audio network graphics window system CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

add_subdirectory(clientlib)

set(target MenAmongGods)
add_executable(${target} main.cpp)
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_link_libraries(${target} PRIVATE client sfml-graphics sfml-network sfml-audio common
                                        MenAmongGodsGraphics logging)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})

#https://cmake.org/cmake/help/latest/command/file.html#get-runtime-dependencies
#file(GET_RUNTIME_DEPENDENCIES EXECUTABLES $<TARGET_FILE:MenAmongGods>)
add_custom_command( TARGET MenAmongGods POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                        $<TARGET_RUNTIME_DLLS:MenAmongGods>
                        $<TARGET_FILE_DIR:MenAmongGods>
                    COMMAND_EXPAND_LISTS)
add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory  ${RESOURCE_OUTPUT_DIRECTORY}/config
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config/config.json ${RESOURCE_OUTPUT_DIRECTORY}/config
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/interfacelib/config/gfxConfig.json ${RESOURCE_OUTPUT_DIRECTORY}/config
            COMMENT "Copying confiuration files to resource directory..."
            )

# Doing 'install' a different way--we'll collect all build artifacts ${install_directory}; this is really quite
# horrible, but I haven't been able to figure out an alternative with CMake just yet that works reliably.
if (CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "[Debug Mode] Creating custom target to create release directory...")
  add_custom_target( create_release
              COMMAND ${CMAKE_COMMAND} -E make_directory  ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_OUTPUT_DIRECTORY} ${install_directory}/res
              COMMENT "Copying dependencies to ${install_directory}..."
              )
else()
  message(STATUS "[Release Mode] Creating custom target to create release directory...")
  add_custom_target( create_release
              COMMAND ${CMAKE_COMMAND} -E make_directory  ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_OUTPUT_DIRECTORY} ${install_directory}/res
              COMMENT "Copying dependencies to ${install_directory}..."
              )
endif()

if (ENABLE_CLANG_TIDY)
  set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY clang-tidy-11)
endif()

add_subdirectory(interfacelib)
add_subdirectory(loglib)