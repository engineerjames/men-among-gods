set(target common)

set(sources 
  RankNames.cpp
  SkillTab.cpp
)

set(headers
  RankNames.h
  SkillTab.h
)

add_library(${target} ${sources} ${headers})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})