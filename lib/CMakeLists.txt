include(FetchContent)
FetchContent_Declare(
   httplib
   GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
   GIT_TAG v0.28.0
)
FetchContent_MakeAvailable(httplib)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

add_library(teams_lib STATIC
    src/Test.cpp
)

target_include_directories( teams_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(ENABLE_COVERAGE "Enable coverage" OFF)

if(ENABLE_COVERAGE)
    target_compile_options(teams_lib PRIVATE -O0 -g --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(teams_lib PRIVATE --coverage -O0 -g)
endif()
find_package(OpenSSL REQUIRED)

target_link_libraries(teams_lib
    PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
        httplib
        nlohmann_json::nlohmann_json
)
