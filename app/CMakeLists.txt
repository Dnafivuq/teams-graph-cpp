option(ENABLE_COVERAGE "Enable coverage" OFF)

if(ENABLE_COVERAGE)
    add_compile_options(-g -O0 --coverage -fprofile-arcs -ftest-coverage)
    add_link_options(-O0 -g --coverage -fprofile-arcs -ftest-coverage)
endif()

add_executable( teams_cli
    main.cpp
)

target_link_libraries( teams_cli
    PRIVATE teams_lib
)


