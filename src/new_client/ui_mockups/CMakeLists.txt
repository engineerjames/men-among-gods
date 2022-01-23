
# Test Application For GUI
set(target ui-text-box)
add_executable(${target} TextBox.h
                         TextBox.cpp
                         TextInput.h
                         TextInput.cpp
                         ui-text-box.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

# Test Application For Loading Legacy Sprites
set(target gfx-load-test)
add_executable(${target} gfx-load-test.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )