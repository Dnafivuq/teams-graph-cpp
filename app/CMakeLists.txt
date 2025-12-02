set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable( teams_cli
    main.cpp
)

target_link_libraries( teams_cli
    PRIVATE teams_lib
)

option(ENABLE_COVERAGE "Enable coverage" OFF)

if(ENABLE_COVERAGE)
    target_compile_options(teams_cli PRIVATE -O0 -g --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(teams_cli PRIVATE --coverage -O0 -g)
endif()
