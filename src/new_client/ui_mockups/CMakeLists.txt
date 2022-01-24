# GUI Library
set(target MenAmongGodsGraphics)
add_library(${target}
                ColorPalette.h
                MainUi.h
                MainUi.cpp
                SkillsAndAttributes.h
                SkillsAndAttributes.cpp
                TextBox.h
                TextBox.cpp
                TextInput.h
                TextInput.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})

# Test Application For GUI
set(target ui-text-box)
add_executable(${target} ui-text-box.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread MenAmongGodsGraphics)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application For Loading Legacy Sprites
set(target gfx-load-test)
add_executable(${target} gfx-load-test.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )