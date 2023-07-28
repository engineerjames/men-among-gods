set(target GuiFormatterTests)
add_executable(${target} GuiFormatterTests.cpp)
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_link_libraries(${target} PRIVATE MenAmongGodsGraphics)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})
target_compile_features(${target} PRIVATE cxx_std_17)

add_test (
    NAME ${target}
    COMMAND $<TARGET_FILE:${target}>
)

set(target ConversionTests)
add_executable(${target} ConversionTests.cpp)
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_link_libraries(${target} PRIVATE client logging)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})
target_compile_features(${target} PRIVATE cxx_std_17)

add_test (
    NAME ${target}
    COMMAND $<TARGET_FILE:${target}>
)

set(target CommandHistoryTests)
add_executable(${target} CommandHistoryTests.cpp)
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_link_libraries(${target} PRIVATE logging MenAmongGodsGraphics)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})
target_compile_features(${target} PRIVATE cxx_std_17)

add_test (
    NAME ${target}
    COMMAND $<TARGET_FILE:${target}>
)