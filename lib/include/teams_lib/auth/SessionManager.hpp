#pragma once

#include <optional>
#include <teams_lib/auth/Tokens.hpp>
#include <teams_lib/common.hpp>

namespace teams::priv {

template <typename TokenProvider, typename TokenStorageProvider>
class SessionManager {
public:
    SessionManager(TokenProvider&& provider,
                   TokenStorageProvider&& storage_provider)
        : provider_{std::move(provider)},
          storage_provider_{std::move(storage_provider)} {
        acquireTokens();
    }

    constexpr void authorizeRequestHeader(HttpHeader& header) const {
        header.emplace("Authorization", "Bearer " + cached_token_);
    }

    void authorizeClient(HttpClient& client) const {
        client.set_bearer_token_auth(cached_token_);
    }

private:
    void tryToStore(const std::optional<RefreshToken>& token) {
        if (token) {
            storage_provider_.store(token.value());
        }
    }

    // TODO: change to std::expected
    std::optional<Tokens> tryToAcquireSilently() {
        if (auto refresh_token = storage_provider_.load()) {
            return provider_.acquireSilently(refresh_token.value());
        }
        return std::nullopt;
    }

    void acquireTokens() {
        if (auto tokens = tryToAcquireSilently()) {
            cached_token_ = tokens.value().access_token;
            tryToStore(tokens.value().refresh_token);
            return;  // tokens acquired
        }
        if (auto tokens = provider_.acquire()) {
            cached_token_ = tokens.value().access_token;
            tryToStore(tokens.value().refresh_token);
            return;  // tokens acquired
        }
        throw;
    }

    TokenProvider provider_;
    TokenStorageProvider storage_provider_;
    AccessToken cached_token_;
};
}  // namespace teams::priv
