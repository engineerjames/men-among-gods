# Do nothing for now

set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5 COMPONENTS graphics network REQUIRED)
add_executable(SFMLTest main.cpp)
target_link_libraries(SFMLTest sfml-graphics sfml-network)