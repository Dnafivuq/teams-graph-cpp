include(FetchContent)

FetchContent_Declare(
   catch2
   GIT_REPOSITORY https://github.com/catchorg/Catch2
   GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(catch2)

add_executable( test
    Test.cpp )

target_link_libraries(test
    PRIVATE Catch2::Catch2WithMain
    PRIVATE teams_lib)

target_include_directories( test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/src
        ${CMAKE_SOURCE_DIR}/lib/include)
