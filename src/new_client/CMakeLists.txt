
if(WIN32)
  set(SFML_DIR C:/SFML/lib/cmake/SFML)
endif()

set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5 COMPONENTS graphics network REQUIRED)

set(target client)
set( sources
    ClientConnection.cpp
    ClientMessage.cpp
    ClientNetworkActivity.cpp
    Compressor.cpp
    PlayerData.cpp
    ServerMessage.cpp
    TickBuffer.cpp
    Encoder.cpp
)
set( headers
    ConstantIdentifiers.h
    ClientConnection.h
    ClientMessage.h
    ClientNetworkActivity.h
    ClientTypes.h
    Compressor.h
    Encoder.h
    PlayerData.h
    ServerMessage.h
    TickBuffer.h
)
add_library(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE sfml-graphics sfml-network pthread z)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

set(target MenAmongGods)
add_executable(${target} main.cpp)
target_link_libraries(${target} PRIVATE client sfml-graphics sfml-network pthread z)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

add_subdirectory(ui_mockups)