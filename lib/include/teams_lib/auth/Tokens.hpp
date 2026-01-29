#pragma once
#include <optional>
#include <teams_lib/common.hpp>

namespace teams::priv {

struct Tokens {
    AccessToken access_token;
    std::optional<RefreshToken> refresh_token;
};

}  // namespace teams::priv
