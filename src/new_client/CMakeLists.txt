set(target SFMLTest)

if(WIN32)
  set(SFML_DIR C:/SFML/lib/cmake/SFML)
endif()

set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5 COMPONENTS graphics network REQUIRED)

add_executable(${target} main.cpp
                         ConstantIdentifiers.h
                         #server_message_processing.h
                         #server_message_processing.cpp
                         ClientConnection.h
                         ClientConnection.cpp
                         ClientMessage.h
                         ClientMessage.cpp
                         ClientNetworkActivity.h
                         ClientNetworkActivity.cpp
                         Compressor.h
                         Compressor.cpp
                         PlayerData.h
                         PlayerData.cpp
                         ServerMessage.h
                         ServerMessage.cpp
                         TickBuffer.h
                         TickBuffer.cpp
                         Encoder.h
                         Encoder.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics sfml-network pthread z)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE -Wall -Wextra -Wshadow -Werror -Wpedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wfloat-equal )

# Test Application For Loading Legacy Sprites
set(target gfx-load-test)
add_executable(${target} gfx-load-test.cpp)
target_link_libraries(${target} PRIVATE sfml-graphics pthread)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE -Wall -Wextra -Wshadow -Werror -Wpedantic -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wfloat-equal )
