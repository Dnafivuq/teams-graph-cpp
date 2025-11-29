#include <catch2/catch_test_macros.hpp>

TEST_CASE("TEST CATCH2 LIB", "[lib]") { REQUIRE(1 == 1); }

TEST_CASE("TEST CATCH2 APP", "[app]") { REQUIRE(0 != 1); }
