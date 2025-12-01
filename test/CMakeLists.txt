include(FetchContent)
FetchContent_Declare(
   catch2
   GIT_REPOSITORY https://github.com/catchorg/Catch2
   GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(catch2)
enable_testing()


add_executable(
    lib_unit_test
    Unit_tests.cpp
)
target_link_libraries(
    lib_unit_test
    PRIVATE Catch2::Catch2WithMain
    PRIVATE teams_lib
)
target_include_directories(
    lib_unit_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/src
        ${CMAKE_SOURCE_DIR}/lib/include
)

add_executable(
    app_unit_test
    Unit_tests.cpp
)
target_link_libraries(
    app_unit_test
    PRIVATE Catch2::Catch2WithMain
    PRIVATE teams_lib
)
target_include_directories(
    app_unit_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/app
)


add_executable(
    acceptance_test
    Acceptance_tests.cpp
)
target_link_libraries(
    acceptance_test
    PRIVATE Catch2::Catch2WithMain
    PRIVATE teams_lib
)
target_include_directories(
    acceptance_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/app
        ${CMAKE_SOURCE_DIR}/lib/src
        ${CMAKE_SOURCE_DIR}/lib/include
)


option(ENABLE_COVERAGE "Enable coverage" OFF)

if(ENABLE_COVERAGE)
    target_compile_options(lib_unit_test PRIVATE -O0 -g --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(lib_unit_test PRIVATE --coverage -O0 -g)
    
    target_compile_options(app_unit_test PRIVATE -O0 -g --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(app_unit_test PRIVATE --coverage -O0 -g)
    
    target_compile_options(acceptance_test PRIVATE -O0 -g --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(acceptance_test PRIVATE --coverage -O0 -g)
endif()

add_test(
    NAME lib_unit_test
    COMMAND lib_unit_test [lib]
)
add_test(
    NAME app_unit_test
    COMMAND app_unit_test [app]
)
add_test(
    NAME acceptance_test
    COMMAND acceptance_test [accept]
)
