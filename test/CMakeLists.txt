include(FetchContent)

FetchContent_Declare(
   catch2
   GIT_REPOSITORY https://github.com/catchorg/Catch2
   GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(catch2)

enable_testing()
add_executable( unit_test
    Unit_tests.cpp )

target_link_libraries(unit_test
    PRIVATE Catch2::Catch2WithMain
    PRIVATE teams_lib)

target_include_directories( unit_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/src
        ${CMAKE_SOURCE_DIR}/lib/include)

add_executable( acceptance_test
    Acceptance_tests.cpp )

target_link_libraries( acceptance_test
    PRIVATE Catch2::Catch2WithMain
    PRIVATE teams_lib)

target_include_directories( acceptance_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/src
        ${CMAKE_SOURCE_DIR}/lib/include)

include(Catch)
catch_discover_tests(unit_test
    TEST_PREFIX "unit."
    DISCOVERY_TIMEOUT 10)
catch_discover_tests(acceptance_test
    TEST_PREFIX "accept."
    DISCOVERY_TIMEOUT 10)