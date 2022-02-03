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
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})