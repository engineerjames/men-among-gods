# Enable ExternalProject CMake module
include(ExternalProject)

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/men_among_gods_rs)

# Add rust_example as a CMake target
ExternalProject_Add(
    men_among_gods
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND cargo build COMMAND cargo build --release
    BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
    INSTALL_COMMAND ""
    LOG_MERGED_STDOUTERR ON
    LOG_BUILD ON)



if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_custom_target( move_rs_debug ALL
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/target/debug/men_among_gods $<TARGET_FILE_DIR:MenAmongGods>
                    COMMENT "Copying rust front-end..." )
else()
    add_custom_target( move_rs_release ALL
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/target/release/men_among_gods $<TARGET_FILE_DIR:MenAmongGods>
                    COMMENT "Copying rust front-end..." )
endif()