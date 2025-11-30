add_executable( teams_cli
    main.cpp
)

target_link_libraries( teams_cli
    PRIVATE teams_lib
)

option(ENABLE_COVERAGE "Enable coverage" OFF)

if(ENABLE_COVERAGE)
    add_compile_options(-g -O0 --coverage)
    add_link_options(--coverage)
endif()
