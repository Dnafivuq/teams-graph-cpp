add_library(teams_lib STATIC
    src/Test.cpp
)

target_include_directories( teams_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(ENABLE_COVERAGE "Enable coverage" OFF)

if(ENABLE_COVERAGE)
    target_compile_options(teams_lib PRIVATE -O0 -g --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(teams_lib PRIVATE --coverage -O0 -g)
endif()
