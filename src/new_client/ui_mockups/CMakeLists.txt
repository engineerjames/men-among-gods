# GUI Library
set(target MenAmongGodsGraphics)
add_library(${target}
                ColorPalette.h
                GraphicsCache.h
                GraphicsCache.cpp
                GraphicsIndex.h
                GraphicsIndex.cpp
                JustifiableText.h
                JustifiableText.cpp
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
target_link_libraries(${target} PRIVATE sfml-graphics Boost::serialization z zip pthread )
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

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

# Test Application for text-related demos only
set(target gfx-text-test)
add_executable(${target} gfx-text-test.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Need the gfx files accessible / copied out to the server build directory so I can start using
# relative directories instead of the hard coded ones.
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