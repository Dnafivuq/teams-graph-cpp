cmake_minimum_required(VERSION 4.2)
add_library(teams_lib STATIC
    src/Test.cpp
)

target_include_directories( teams_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)