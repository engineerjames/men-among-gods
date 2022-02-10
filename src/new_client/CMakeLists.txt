set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5 COMPONENTS graphics network REQUIRED)

add_subdirectory(clientlib)

set(target MenAmongGods)
add_executable(${target} main.cpp)
target_link_libraries(${target} PRIVATE client sfml-graphics sfml-network 
                                        Boost::serialization MenAmongGodsGraphics)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

if (ENABLE_CLANG_TIDY)
  set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY clang-tidy-11)
endif()

add_subdirectory(interfacelib)
add_subdirectory(loglib)