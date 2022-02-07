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

    commands/AttackCommand.cpp
    commands/AttackCommand.h
    commands/AutoLookCommand.cpp
    commands/AutoLookCommand.h
    commands/ClientCommand.h
    commands/ChallengeCommand.h
    commands/ChallengeCommand.cpp
    commands/DropCommand.cpp
    commands/DropCommand.h
    commands/ExitCommand.cpp
    commands/ExitCommand.h
    commands/GiveCommand.cpp
    commands/GiveCommand.h
    commands/InventoryCommand.cpp
    commands/InventoryCommand.h
    commands/InventoryLookCommand.cpp
    commands/InventoryLookCommand.h
    commands/LookCommand.cpp
    commands/LookCommand.h
    commands/LookItemCommand.cpp
    commands/LookItemCommand.h
    commands/ModeCommand.cpp
    commands/ModeCommand.h
    commands/MoveCommand.cpp
    commands/MoveCommand.h
    commands/PickupCommand.cpp
    commands/PickupCommand.h
    commands/ResetCommand.cpp
    commands/ResetCommand.h
    commands/ShopCommand.cpp
    commands/ShopCommand.h
    commands/SkillCommand.cpp
    commands/SkillCommand.h
    commands/StatCommand.cpp
    commands/StatCommand.h
    commands/TickCommand.cpp
    commands/TickCommand.h
    commands/SayCommand.cpp
    commands/SayCommand.h
    commands/TurnCommand.cpp
    commands/TurnCommand.h
    commands/UniqueCommand.h
    commands/UniqueCommand.cpp
    commands/UseCommand.cpp
    commands/UseCommand.h
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
target_link_libraries(${target} PRIVATE sfml-graphics sfml-network z zip pthread 
                                        Boost::serialization MenAmongGodsGraphics)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                            ${CMAKE_CURRENT_SOURCE_DIR}/commands)