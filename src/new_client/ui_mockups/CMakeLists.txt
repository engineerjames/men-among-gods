
# Test Application For Loading Legacy Sprites
set(target ui-text-box)
add_executable(${target} TextInput.h TextInput.cpp ui-text-box.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )