set(target logging)

set(sources 
  Logger.cpp
)

set(headers 
  Logger.h
)

add_library(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_link_libraries(${target} PUBLIC JsonCpp::JsonCpp)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_include_directories(${target} PUBLIC ${jsoncpp_includes} ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${target} PUBLIC ${PROJECT_CXX_DEFINITIONS})