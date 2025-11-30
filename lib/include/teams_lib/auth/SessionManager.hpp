#pragma once

#include "teams_lib/common.hpp"

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
    void tryStoreRefreshToken(const RefreshToken& refresh_token) {
        storage_provider_.storeRefreshToken(refresh_token);
    }

    bool tryAcquireTokensSilently() {
        if (auto refresh_token = storage_provider_.loadRefreshToken()) {
            if (auto tokens =
                    provider_.acquireTokensSilently(refresh_token.value())) {
                cached_token_ = tokens.value().access_token;

                // try to store refresh token
                if (tokens.value().refresh_token) {
                    tryStoreRefreshToken(tokens.value().refresh_token.value());
                }
                return true;
            }
        }
        return false;
    }
    bool tryAcquireTokens() {
        if (auto tokens = provider_.acquireTokens()) {
            cached_token_ = tokens.value().access_token;
            if (!tokens.value().refresh_token) {
                std::cout << "[WARNING] NO REFRESH TOKEN\n";
            }
            tryStoreRefreshToken(tokens.value().refresh_token.value());
            return true;
        }
        return false;
    }

    void acquireTokens() {
        if (tryAcquireTokensSilently()) {
            return;
        }
        if (tryAcquireTokens()) {
            return;
        }
        throw;
    }

    TokenProvider provider_;
    TokenStorageProvider storage_provider_;
    AccessToken cached_token_;
};
}  // namespace teams::priv
