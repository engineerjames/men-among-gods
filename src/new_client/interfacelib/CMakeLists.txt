# GUI Library
set(target MenAmongGodsGraphics)

set( sources 
    Component.cpp
    FontCache.cpp
    GraphicsCache.cpp
    GraphicsIndex.cpp
    JustifiableText.cpp
    LifeDisplay.cpp
    LoginUi.cpp
    MainUi.cpp
    MapDisplay.cpp
    PasswordTextInputDisplay.cpp
    PlayerInventoryDisplay.cpp
    PlayerLogDisplay.cpp
    PlayerTextInputDisplay.cpp
    ProgressBarDisplay.cpp
    RadioButtonDisplay.cpp
    SkillsAndAttributesDisplay.cpp
    SubmitButtonDisplay.cpp
    TextInputDisplay.cpp
)

set( headers 
    ColorPalette.h
    Component.h
    FontCache.h
    GraphicsCache.h
    GraphicsIndex.h
    GuiFormatters.h
    JustifiableText.h
    LifeDisplay.h
    LoginUi.h
    MainUi.h
    MapDisplay.h
    PasswordTextInputDisplay.h
    PlayerInventoryDisplay.h
    PlayerLogDisplay.h
    PlayerTextInputDisplay.h
    ProgressBarDisplay.h
    RadioButtonDisplay.h
    SkillsAndAttributesDisplay.h
    SubmitButtonDisplay.h
    TextInputDisplay.h
    UiPositions.h
    UtilityFunctions.h
)

add_library(${target} ${sources} ${headers})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${target} PRIVATE sfml-graphics Boost::serialization z zip pthread client)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

# Test Application For GUI
set(target ui-gui-demo)
add_executable(${target} test_applications/ui-gui-demo.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics MenAmongGodsGraphics Boost::serialization client)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application For Loading Legacy Sprites
set(target gfx-load-test)
add_executable(${target} test_applications/gfx-load-test.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics MenAmongGodsGraphics client)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application for reading the graphics-related .idx file
set(target gfx-idx-load)
add_executable(${target} test_applications/gfx-idx-load.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics client)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application for text-related demos only
set(target gfx-text-test)
add_executable(${target} test_applications/gfx-text-test.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics client)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application for login-related ui demos only
set(target gfx-login-ui)
add_executable(${target} test_applications/gfx-login-ui.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics client)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application for login-related ui demos only
set(target gfx-progress-bar)
add_executable(${target} test_applications/gfx-progress-bar.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics client)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

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