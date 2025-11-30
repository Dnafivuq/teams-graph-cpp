add_executable( teams_cli
    main.cpp
)

target_link_libraries( teams_cli
    PRIVATE teams_lib
)