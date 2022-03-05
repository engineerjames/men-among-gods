find_package(Drogon REQUIRED)

set(target api)

set(sources 
  main.cpp
  ItemTemplateApi.cpp
)

set(headers
  ItemTemplateApi.h
  apiTypes.h
)

add_executable(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE Drogon::Drogon ${jsoncpp_lib})
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})

# This is horrible, but the only option until I break out the targets more for the server
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../server/)
target_include_directories(${target} SYSTEM PRIVATE ${jsoncpp_includes})