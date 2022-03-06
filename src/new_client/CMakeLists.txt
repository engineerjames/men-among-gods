set(SFML_STATIC_LIBRARIES OFF)
find_package(SFML 2.5 COMPONENTS audio network graphics window system CONFIG REQUIRED)
find_package(libzip CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

add_subdirectory(clientlib)

set(target MenAmongGods)
add_executable(${target} main.cpp)
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_link_libraries(${target} PRIVATE client sfml-graphics sfml-network sfml-audio
                                        Boost::serialization MenAmongGodsGraphics logging)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})

add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory  ${RESOURCE_OUTPUT_DIRECTORY}/config
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config/config.json ${RESOURCE_OUTPUT_DIRECTORY}/config
            )

if (ENABLE_CLANG_TIDY)
  set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY clang-tidy-11)
endif()

add_subdirectory(interfacelib)
add_subdirectory(loglib)