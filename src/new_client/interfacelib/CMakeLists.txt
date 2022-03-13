# GUI Library
set(target MenAmongGodsGraphics)

set( sources 
    CommandHistory.cpp
    Component.cpp
    FontCache.cpp
    GraphicsCache.cpp
    GraphicsIndex.cpp
    JustifiableText.cpp
    MainUi.cpp
    MapDisplay.cpp
    PlayerEquipmentDisplay.cpp
    PlayerInventoryDisplay.cpp
    PlayerLogDisplay.cpp
    PlayerShopDisplay.cpp
    PlayerTextInputDisplay.cpp
    RankDisplay.cpp
    SkillsAndAttributesDisplay.cpp
    SoundCache.cpp
    UserOptionPanelDisplay.cpp
)

set( headers 
    CommandHistory.h
    ColorPalette.h
    Component.h
    FontCache.h
    GraphicsCache.h
    GraphicsIndex.h
    GuiFormatters.h
    JustifiableText.h
    LoadButtonDisplay.h
    MainUi.h
    MapDisplay.h
    PlayerEquipmentDisplay.h
    PlayerInventoryDisplay.h
    PlayerLogDisplay.h
    PlayerShopDisplay.h
    PlayerTextInputDisplay.h
    RankDisplay.h
    SkillsAndAttributesDisplay.h
    SoundCache.h
    UiPositions.h
    UserOptionPanelDisplay.h
    UtilityFunctions.h
)

set( test_application_libs
    ${PROJECT_CXX_LIBS}
    sfml-graphics 
    sfml-audio
    Boost::serialization 
    ZLIB::ZLIB
    libzip::zip
    client 
    commands 
    logging
)

add_library(${target} ${sources} ${headers})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS} Boost::serialization sfml-graphics 
                                sfml-system sfml-audio clientInterface logging commands)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

# Test Application For GUI
set(target ui-gui-demo)
add_executable(${target} test_applications/ui-gui-demo.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics ${test_application_libs})
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

# Test Application For Loading Legacy Sprites
set(target gfx-load-test)
add_executable(${target} test_applications/gfx-load-test.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics ${test_application_libs})
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

# Test Application for reading the graphics-related .idx file
set(target gfx-idx-load)
add_executable(${target} test_applications/gfx-idx-load.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics ${test_application_libs})
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

# Test Application for text-related demos only
set(target gfx-text-test)
add_executable(${target} test_applications/gfx-text-test.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics ${test_application_libs})
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

# Need the gfx files accessible / copied out to the server build directory so I can start using
# relative directories instead of the hard coded ones.
add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory  ${RESOURCE_OUTPUT_DIRECTORY}/gfx
            COMMAND ${CMAKE_COMMAND} -E make_directory  ${RESOURCE_OUTPUT_DIRECTORY}/fonts
            COMMAND ${CMAKE_COMMAND} -E make_directory  ${RESOURCE_OUTPUT_DIRECTORY}/test
            COMMAND ${CMAKE_COMMAND} -E make_directory  ${RESOURCE_OUTPUT_DIRECTORY}/sfx

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../gfx/gfx.zip ${RESOURCE_OUTPUT_DIRECTORY}/gfx

            # Copy all sound files; TODO: Improve later once finalized (no need to list out every individual file)
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/1.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/2.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/3.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/4.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/5.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/6.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/7.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/8.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/9.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/10.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/11.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/12.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/13.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/14.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/15.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/16.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/17.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../sfx/18.wav ${RESOURCE_OUTPUT_DIRECTORY}/sfx
            
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_files/gx00.idx ${RESOURCE_OUTPUT_DIRECTORY}/gfx

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../fonts/onuava.ttf ${RESOURCE_OUTPUT_DIRECTORY}/fonts

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_files/mapfile.archive ${RESOURCE_OUTPUT_DIRECTORY}/test
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_files/player.archive ${RESOURCE_OUTPUT_DIRECTORY}/test

            COMMAND ${CMAKE_COMMAND} -E tar xzf ${RESOURCE_OUTPUT_DIRECTORY}/gfx/gfx.zip
            COMMENT "Running post build script..."
  )

  add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${RESOURCE_OUTPUT_DIRECTORY}/gfx/gfx.zip
            WORKING_DIRECTORY ${RESOURCE_OUTPUT_DIRECTORY}/gfx/
            COMMENT "Running post build script..."
            )