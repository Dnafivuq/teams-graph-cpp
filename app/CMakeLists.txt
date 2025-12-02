add_executable( teams_cli
    main.cpp

    callbacks/Team.cpp

    subcommands/Team.cpp

)

include(FetchContent)
FetchContent_Declare(
   CLI11
   GIT_REPOSITORY https://github.com/CLIUtils/CLI11
   GIT_TAG v2.6.1
)
FetchContent_MakeAvailable(CLI11)

target_link_libraries( teams_cli
    PRIVATE teams_lib
    PRIVATE CLI11::CLI11
)

target_include_directories( teams_cli
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/
)