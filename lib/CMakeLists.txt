option(ENABLE_COVERAGE "Enable coverage" OFF)

if(ENABLE_COVERAGE)
    add_compile_options(-g -O0 --coverage -fprofile-arcs -ftest-coverage)
    add_link_options(-O0 -g --coverage -fprofile-arcs -ftest-coverage)
endif()

add_library(teams_lib STATIC
    src/Test.cpp
)

target_include_directories( teams_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
