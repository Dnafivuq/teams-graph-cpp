include(FetchContent)

FetchContent_Declare(
   catch2
   GIT_REPOSITORY https://github.com/catchorg/Catch2
   GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(catch2)

enable_testing()
add_executable( unit_test
    Test.cpp )

target_link_libraries(unit_test
    PRIVATE Catch2::Catch2WithMain
    PRIVATE teams_lib)

target_include_directories( unit_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/src
        ${CMAKE_SOURCE_DIR}/lib/include)

include(Catch)
catch_discover_tests(unit_test
DISCOVERY_TIMEOUT 10)