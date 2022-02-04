set(target GuiFormatterTests)
add_executable(${target} GuiFormatterTests.cpp)
target_link_libraries(${target} PRIVATE Boost::unit_test_framework MenAmongGodsGraphics)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_features(${target} PRIVATE cxx_std_17)

add_test (
    NAME ${target} 
    COMMAND $<TARGET_FILE:${target}>
)