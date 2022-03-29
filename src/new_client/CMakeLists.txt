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

install(
  TARGETS MenAmongGods
  JsonCpp::JsonCpp
  Drogon::Drogon
  ZLIB::ZLIB
  libzip::zip
  sfml-system
  DESTINATION ${install_directory}
)

# Just install these files the ol' fashioned way via the post-build command
install(
  IMPORTED_RUNTIME_ARTIFACTS
  JsonCpp::JsonCpp
  Drogon::Drogon
  ZLIB::ZLIB
  libzip::zip
  sfml-system
  DESTINATION ${install_directory}
)

install(
  FILES  $<TARGET_RUNTIME_DLLS:MenAmongGods>
  DESTINATION ${install_directory}
)

# install(CODE [[
#     file(GET_RUNTIME_DEPENDENCIES
#         RESOLVED_DEPENDENCIES_VAR RES
#         UNRESOLVED_DEPENDENCIES_VAR UNRES
#         CONFLICTING_DEPENDENCIES_PREFIX CONFLICTING_DEPENDENCIES
#         EXECUTABLES $<TARGET_FILE:MenAmongGods>
#     )

#     message("\n\nFound dependencies :")
#     foreach(DEP ${RES})
#         message("RESOLVED: ${DEP}")
#     endforeach()
#     message("\n\nNot found dependencies :")
#     foreach(DEP ${UNRES})
#         message("UNRESOLVED: ${DEP}")
#     endforeach()
# ]])

add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory  ${RESOURCE_OUTPUT_DIRECTORY}/config
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config/config.json ${RESOURCE_OUTPUT_DIRECTORY}/config
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/interfacelib/config/gfxConfig.json ${RESOURCE_OUTPUT_DIRECTORY}/config
            )

if (ENABLE_CLANG_TIDY)
  set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY clang-tidy-11)
endif()

add_subdirectory(interfacelib)
add_subdirectory(loglib)