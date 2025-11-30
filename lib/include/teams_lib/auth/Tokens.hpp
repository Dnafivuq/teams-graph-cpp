#pragma once
#include <optional>
#include <teams_lib/common.hpp>

namespace teams::priv {

struct Tokens {
    Token access_token;
    std::optional<Token> refresh_token;
};

}  // namespace teams::priv