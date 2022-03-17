find_package(Drogon)
find_package(jsoncpp CONFIG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/server)

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
target_link_libraries(${target} PRIVATE Drogon::Drogon JsonCpp::JsonCpp common)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})

# This is horrible, but the only option until I break out the targets more for the server
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../server/)