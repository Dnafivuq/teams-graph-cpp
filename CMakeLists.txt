cmake_minimum_required(VERSION 3.22)
project(teams_cli VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_COVERAGE "Enable coverage" OFF)

if(ENABLE_COVERAGE)
    add_compile_options(-g -O0 --coverage -fprofile-arcs -ftest-coverage)
    add_link_options(-O0 -g --coverage -fprofile-arcs -ftest-coverage)
endif()

enable_testing()

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(test)

