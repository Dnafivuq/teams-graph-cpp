cmake_minimum_required(VERSION 3.22)
project(teams_cli VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(test)

