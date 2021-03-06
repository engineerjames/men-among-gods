set(SFML_STATIC_LIBRARIES OFF)
find_package(SFML 2.5 COMPONENTS audio network graphics window system CONFIG REQUIRED)
find_package(jsoncpp CONFIG)
find_package(ZLIB)

add_subdirectory(clientlib)

set(target MenAmongGods)
add_executable(${target} main.cpp)
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_link_libraries(${target} PRIVATE client sfml-graphics sfml-network sfml-audio common
                                        MenAmongGodsGraphics logging)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})

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
if (CMAKE_BUILD_TYPE MATCHES Debug)
  message(STATUS "[Debug Mode] Creating custom target to create release directory...")
  add_custom_target( create_release
              COMMAND ${CMAKE_COMMAND} -E make_directory  ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/brotlicommon.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/brotlidec.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/bz2d.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/FLAC.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/freetyped.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/libpng16d.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/ogg.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/OpenAL32.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-audio-d-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-graphics-d-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-network-d-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-system-d-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-window-d-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/vorbis.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/vorbisenc.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/vorbisfile.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/zlibd1.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MenAmongGods> ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MenAmongGods> ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_OUTPUT_DIRECTORY} ${install_directory}/res
              COMMENT "Copying dependencies to ${install_directory}..."
              )
else()
  message(STATUS "[Release Mode] Creating custom target to create release directory...")
  add_custom_target( create_release
              COMMAND ${CMAKE_COMMAND} -E make_directory  ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/brotlicommon.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/brotlidec.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/bz2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/FLAC.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/freetype.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/libpng16.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/ogg.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/OpenAL32.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-audio-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-graphics-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-network-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-system-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/sfml-window-2.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/vorbis.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/vorbisenc.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/vorbisfile.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/zlib1.dll ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MenAmongGods> ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MenAmongGods> ${install_directory}
              COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_OUTPUT_DIRECTORY} ${install_directory}/res
              COMMENT "Copying dependencies to ${install_directory}..."
              )
endif()

# Need to ensure that electron-packager and electron-builder has been installed globally
add_custom_target( package_release
            COMMAND npm install
            COMMAND npx electron-packager . --extra-resource=${install_directory} --out=${PROJECT_SOURCE_DIR}/electron_app/men-among-gods/out
            COMMAND electron-builder.cmd --prepackaged ${PROJECT_SOURCE_DIR}/electron_app/men-among-gods/out/men-among-gods-win32-x64
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/electron_app/men-among-gods
            COMMENT "Creating release..."
)

if (ENABLE_CLANG_TIDY)
  set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY clang-tidy-11)
endif()

add_subdirectory(interfacelib)
add_subdirectory(loglib)