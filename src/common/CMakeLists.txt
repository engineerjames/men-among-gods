set(target common)

set(sources
  Character.cpp
  Item.cpp
  RaceAndSex.cpp
  RankNames.cpp
  SkillTab.cpp
)

set(headers
  Character.h
  Item.h
  RaceAndSex.h
  RankNames.h
  SkillTab.h
  Constants.h
)

add_library(${target} ${sources} ${headers})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS} logging)
target_link_libraries(${target} PUBLIC njson)
target_compile_features(${target} PRIVATE cxx_std_17)
target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} )
target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})

if (CMAKE_COMPILER_IS_GNUCXX)
  message(STATUS "Adding 32-bit common library for linking to server executable")
  set(target ${target}32)
  add_library(${target} ${sources} ${headers})
  target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} /usr/include/jsoncpp)
  target_link_libraries(${target} PRIVATE ${PROJECT_CXX_LIBS})
  target_compile_features(${target} PRIVATE cxx_std_17)
  target_compile_options(${target} PRIVATE ${PROJECT_CXX_FLAGS} -m32)
  target_compile_definitions(${target} PRIVATE ${PROJECT_CXX_DEFINITIONS})
endif()