#pragma once

#include <optional>
#include <teams_lib/auth/DeviceCodeCredential.hpp>
#include <teams_lib/auth/Tokens.hpp>
#include <teams_lib/common.hpp>

namespace teams::priv {

template <typename DerivedProvider>
class TokenProvider {
public:
    explicit TokenProvider(DeviceCodeCredential device_code_credential,
                           std::string scopes)
        : device_code_credential_{std::move(device_code_credential)},
          scopes_{std::move(scopes)} {};

    // TODO: change to std::expected on c++ version bump
    std::optional<Tokens> acquireTokens() const {
        return static_cast<const DerivedProvider*>(this)->acquireTokensImpl();
    };

    // TODO: change to std::expected on c++ version bump
    std::optional<Tokens> acquireTokensSilently(
        const RefreshToken& refresh_token) const {
        return static_cast<const DerivedProvider*>(this)
            ->acquireTokensSilentlyImpl(refresh_token);
    }

    const DeviceCodeCredential& credentials() const {
        return device_code_credential_;
    }

    const std::string& scopes() const { return scopes_; }

private:
    DeviceCodeCredential device_code_credential_;
    std::string scopes_;
};

}  // namespace teams::priv
