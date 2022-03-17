set(target client)
set( sources
    ClientConfiguration.cpp
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
    ClientConfiguration.h
    ClientConnection.h
    ClientMessage.h
    ClientNetworkActivity.h
    ClientTypes.h
    Compressor.h
    Encoder.h
    Map.h
    PlayerData.h
    ServerMessage.h
    TickBuffer.h
)
add_library(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_link_libraries(${target} PRIVATE sfml-graphics sfml-network logging ZLIB::ZLIB common
                                        MenAmongGodsGraphics commands)

if (NOT MSVC)
target_link_libraries(${target} PRIVATE pthread GL)
endif()

target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (ENABLE_CLANG_TIDY)
  set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY clang-tidy-11)
endif()

set(target clientInterface)
add_library(${target} INTERFACE)
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set(target commands)
set( sources
    commands/AttackCommand.cpp
    commands/AutoLookCommand.cpp
    commands/ChallengeCommand.cpp
    commands/DropCommand.cpp
    commands/ExitCommand.cpp
    commands/GiveCommand.cpp
    commands/InventoryCommand.cpp
    commands/InventoryLookCommand.cpp
    commands/LoginCommand.cpp
    commands/LookCommand.cpp
    commands/LookItemCommand.cpp
    commands/ModeCommand.cpp
    commands/MoveCommand.cpp
    commands/NewLoginCommand.cpp
    commands/PasswordCommand.cpp
    commands/PickupCommand.cpp
    commands/ResetCommand.cpp
    commands/SetUserCommand.cpp
    commands/ShopCommand.cpp
    commands/SkillCommand.cpp
    commands/StatCommand.cpp
    commands/TickCommand.cpp
    commands/SayCommand.cpp
    commands/TurnCommand.cpp
    commands/UniqueCommand.cpp
    commands/UseCommand.cpp
)
set( headers
    commands/AttackCommand.h
    commands/AutoLookCommand.h
    commands/ClientCommand.h
    commands/ChallengeCommand.h
    commands/DropCommand.h
    commands/ExitCommand.h
    commands/GiveCommand.h
    commands/InventoryCommand.h
    commands/InventoryLookCommand.h
    commands/LoginCommand.h
    commands/LookCommand.h
    commands/LookItemCommand.h
    commands/ModeCommand.h
    commands/MoveCommand.h
    commands/NewLoginCommand.h
    commands/PasswordCommand.h
    commands/PickupCommand.h
    commands/ResetCommand.h
    commands/SetUserCommand.h
    commands/ShopCommand.h
    commands/SkillCommand.h
    commands/StatCommand.h
    commands/TickCommand.h
    commands/SayCommand.h
    commands/TurnCommand.h
    commands/UniqueCommand.h
    commands/UseCommand.h
)
add_library(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE sfml-network MenAmongGodsGraphics clientInterface logging client)
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/commands)

if (ENABLE_CLANG_TIDY)
  set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY clang-tidy-11)
endif()