# GUI Library
set(target MenAmongGodsGraphics)
add_library(${target}
                ColorPalette.h
                GraphicsCache.h
                GraphicsCache.cpp
                GraphicsIndex.h
                GraphicsIndex.cpp
                LifeDisplay.h
                LifeDisplay.cpp
                MainUi.h
                MainUi.cpp
                MapDisplay.h
                MapDisplay.cpp
                PlayerInventoryDisplay.h
                PlayerInventoryDisplay.cpp
                SkillsAndAttributes.h
                SkillsAndAttributes.cpp
                PlayerLogDisplay.h
                PlayerLogDisplay.cpp
                PlayerTextInputDisplay.h
                PlayerTextInputDisplay.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics Boost::serialization )
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_include_directories(${target} SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../zlib)
target_link_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../zlib)
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

if(NOT WIN32)
target_link_libraries(${target} PUBLIC pthread zip)
else()
target_link_libraries(${target} PUBLIC )
endif()

# Test Application For GUI
set(target ui-gui-demo)
add_executable(${target} ui-gui-demo.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics MenAmongGodsGraphics Boost::serialization client)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application For Loading Legacy Sprites
set(target gfx-load-test)
add_executable(${target} gfx-load-test.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics MenAmongGodsGraphics)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application for reading the graphics-related .idx file
set(target gfx-idx-load)
add_executable(${target} gfx-idx-load.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Need the gfx files accessible / copied out to the server build directory so I can start using
# relative directories instead of the hard coded ones.

if (WIN32)

add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory  $<TARGET_FILE_DIR:${target}>/gfx
            COMMAND ${CMAKE_COMMAND} -E make_directory  $<TARGET_FILE_DIR:${target}>/fonts
            COMMAND ${CMAKE_COMMAND} -E make_directory  $<TARGET_FILE_DIR:${target}>/test

            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../gfx $<TARGET_FILE_DIR:${target}>/gfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/gx00.idx $<TARGET_FILE_DIR:${target}>/gfx

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../fonts/onuava.ttf $<TARGET_FILE_DIR:${target}>/fonts

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/mapfile.archive $<TARGET_FILE_DIR:${target}>/test
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/player.archive $<TARGET_FILE_DIR:${target}>/test
            )
else()

add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory  $<TARGET_FILE_DIR:${target}>/gfx
            COMMAND ${CMAKE_COMMAND} -E make_directory  $<TARGET_FILE_DIR:${target}>/fonts
            COMMAND ${CMAKE_COMMAND} -E make_directory  $<TARGET_FILE_DIR:${target}>/test

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../gfx/gfx.zip $<TARGET_FILE_DIR:${target}>/gfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/gx00.idx $<TARGET_FILE_DIR:${target}>/gfx

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../fonts/onuava.ttf $<TARGET_FILE_DIR:${target}>/fonts

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/mapfile.archive $<TARGET_FILE_DIR:${target}>/test
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/player.archive $<TARGET_FILE_DIR:${target}>/test
            )
endif()

if (WIN32)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/player.archive $<TARGET_FILE_DIR:${target}>/test
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/openal32.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-audio-2.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-audio-d-2.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-graphics-2.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-graphics-d-2.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-network-2.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-network-d-2.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-system-2.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-system-d-2.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-window-2.dll $<TARGET_FILE_DIR:${target}>
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sfml-window-d-2.dll $<TARGET_FILE_DIR:${target}>
        )
endif()