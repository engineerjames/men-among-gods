# GUI Library
set(target MenAmongGodsGraphics)
add_library(${target}
                ColorPalette.h
                GraphicsCache.h
                GraphicsCache.cpp
                GraphicsIndex.h
                GraphicsIndex.cpp
                MainUi.h
                MainUi.cpp
                Map.h
                Map.cpp
                SkillsAndAttributes.h
                SkillsAndAttributes.cpp
                TextBox.h
                TextBox.cpp
                TextInput.h
                TextInput.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread Boost::serialization zip)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})

# Test Application For GUI
set(target ui-gui-demo)
add_executable(${target} ui-gui-demo.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread MenAmongGodsGraphics Boost::serialization client)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application For Loading Legacy Sprites
set(target gfx-load-test)
add_executable(${target} gfx-load-test.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread MenAmongGodsGraphics)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application for reading the graphics-related .idx file
set(target gfx-idx-load)
add_executable(${target} gfx-idx-load.cpp)
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
