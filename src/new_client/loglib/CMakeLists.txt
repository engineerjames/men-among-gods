# Find JsonCPP
find_library(jsoncpp jsoncpp)

if (jsoncpp)
  message(STATUS "JsonCpp found: ${jsoncpp}")
  set(jsoncpp_includes /usr/include/jsoncpp)
endif()


set(target logging)

set(sources 
  test.cpp
)

set(headers 
)

add_library(${target} ${sources} ${headers})
target_link_libraries(${target} PRIVATE ${jsoncpp})
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS})
target_include_directories(${target} PUBLIC ${jsoncpp_includes})