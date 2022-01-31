set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5 COMPONENTS graphics network REQUIRED)

set(target client)
set( sources
    ClientConnection.cpp
    ClientMessage.cpp
    ClientNetworkActivity.cpp
    Compressor.cpp
    Encoder.cpp
    Map.cpp
    PlayerData.cpp
    ServerMessage.cpp
    TickBuffer.cpp
)
set( headers
    ClientConnection.h
    ClientMessage.h
    ClientNetworkActivity.h
    ClientTypes.h
    Compressor.h
    ConstantIdentifiers.h
    Encoder.h
    Map.h
    PlayerData.h
    ServerMessage.h
    TickBuffer.h
)
add_library(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE sfml-graphics sfml-network z zip pthread Boost::serialization)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})

set(target MenAmongGods)
add_executable(${target} main.cpp)
target_link_libraries(${target} PRIVATE client sfml-graphics sfml-network Boost::serialization)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )

add_subdirectory(ui_mockups)