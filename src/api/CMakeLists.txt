find_package(Drogon REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/server)

set(target model)
set(sources 
  models/character.cpp
  models/item.cpp
  models/skilltab.cpp
)

set(headers 
  models/character.h
  models/item.h
  models/skilltab.h
)

add_library(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE JsonCpp::JsonCpp)
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})


set(target api)
set(sources 
  main.cpp
  CharacterTemplateApi.cpp
  ItemTemplateApi.cpp
)

set(headers
  CharacterTemplateApi.h
  ItemTemplateApi.h
)

add_executable(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE Drogon::Drogon JsonCpp::JsonCpp model)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})

# This is horrible, but the only option until I break out the targets more for the server
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../server/)