cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_library(ZSTD_LIBRARY zstd)
find_package(zstd QUIET)

if(ZSTD_LIBRARY AND NOT TARGET zstd::libzstd)
    add_library(zstd::libzstd UNKNOWN IMPORTED)
    set_target_properties(zstd::libzstd PROPERTIES
        IMPORTED_LOCATION "${ZSTD_LIBRARY}"
    )
endif()

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
    src/serialization/UserIdentity.cpp
    src/serialization/ItemBody.cpp
    src/serialization/ChannelIdentity.cpp
    src/serialization/Message.cpp
    src/serialization/Channel.cpp
    src/serialization/Team.cpp
)

target_include_directories( teams_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(OpenSSL REQUIRED)

target_compile_definitions(teams_lib
    PUBLIC CPPHTTPLIB_OPENSSL_SUPPORT
)

target_link_libraries(teams_lib
    PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
        httplib::httplib
        nlohmann_json::nlohmann_json
)
