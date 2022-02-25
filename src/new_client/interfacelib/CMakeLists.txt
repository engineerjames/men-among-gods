# GUI Library
set(target MenAmongGodsGraphics)

set( sources 
    CommandHistory.cpp
    Component.cpp
    FontCache.cpp
    GraphicsCache.cpp
    GraphicsIndex.cpp
    JustifiableText.cpp
    LoadButtonDisplay.cpp
    LoginUi.cpp
    MainUi.cpp
    MapDisplay.cpp
    PasswordTextInputDisplay.cpp
    PlayerEquipmentDisplay.cpp
    PlayerInventoryDisplay.cpp
    PlayerLogDisplay.cpp
    PlayerShopDisplay.cpp
    PlayerTextInputDisplay.cpp
    ProgressBarDisplay.cpp
    RadioButtonDisplay.cpp
    RankDisplay.cpp
    SkillsAndAttributesDisplay.cpp
    SaveButtonDisplay.cpp
    SubmitButtonDisplay.cpp
    TextInputDisplay.cpp
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
    LoginUi.h
    MainUi.h
    MapDisplay.h
    PasswordTextInputDisplay.h
    PlayerEquipmentDisplay.h
    PlayerInventoryDisplay.h
    PlayerLogDisplay.h
    PlayerShopDisplay.h
    PlayerTextInputDisplay.h
    ProgressBarDisplay.h
    RadioButtonDisplay.h
    RankDisplay.h
    SaveButtonDisplay.h
    SkillsAndAttributesDisplay.h
    SubmitButtonDisplay.h
    TextInputDisplay.h
    UiPositions.h
    UserOptionPanelDisplay.h
    UtilityFunctions.h
)

set( test_application_libs
    sfml-graphics 
    Boost::serialization 
    ${zlib_library}
    ${libzip_library}
    client 
    commands 
    logging
)

add_library(${target} ${sources} ${headers})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${target} PRIVATE ${test_application_libs})
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

# Test Application for login-related ui demos only
set(target gfx-login-ui)
add_executable(${target} test_applications/gfx-login-ui.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics ${test_application_libs})
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

# Test Application for login-related ui demos only
set(target gfx-progress-bar)
add_executable(${target} test_applications/gfx-progress-bar.cpp)
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

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../gfx/gfx.zip ${RESOURCE_OUTPUT_DIRECTORY}/gfx
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_files/gx00.idx ${RESOURCE_OUTPUT_DIRECTORY}/gfx

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../fonts/onuava.ttf ${RESOURCE_OUTPUT_DIRECTORY}/fonts

            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_files/mapfile.archive ${RESOURCE_OUTPUT_DIRECTORY}/test
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_files/player.archive ${RESOURCE_OUTPUT_DIRECTORY}/test
            )