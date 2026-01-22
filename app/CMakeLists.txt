set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable( teams_cli
    main.cpp
    utils.cpp
    utils.cpp

    callbacks/Team.cpp
    callbacks/Channel.cpp
    callbacks/Post.cpp
    callbacks/UserGroup.cpp
    callbacks/Template.cpp
    callbacks/Member.cpp

    subcommands/Team.cpp
    subcommands/Member.cpp
    subcommands/Member.cpp
    subcommands/Channel.cpp
    subcommands/Post.cpp
    subcommands/UserGroup.cpp
    subcommands/Template.cpp

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

option(ENABLE_COVERAGE "Enable coverage" OFF)

if(ENABLE_COVERAGE)
    target_compile_options(teams_cli PRIVATE -O0 -g --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(teams_cli PRIVATE --coverage -O0 -g)
endif()
