#pragma once

#include <optional>
#include <teams_lib/auth/DeviceCodeCredential.hpp>
#include <teams_lib/auth/Tokens.hpp>
#include <teams_lib/common.hpp>

namespace teams::priv {

template <typename DerivedProvider>
class TokenProvider {
public:
    explicit TokenProvider(DeviceCodeCredential credentials, Scopes scopes)
        : device_code_credential_{std::move(credentials)},
          scopes_{std::move(scopes)} {};

    // TODO: change to std::expected on c++ version bump
    std::optional<Tokens> acquire() const {
        return static_cast<const DerivedProvider*>(this)->acquireImpl();
    };

    // TODO: change to std::expected on c++ version bump
    std::optional<Tokens> acquireSilently(const RefreshToken& token) const {
        return static_cast<const DerivedProvider*>(this)->acquireSilentlyImpl(
            token);
    }

    const DeviceCodeCredential& credentials() const {
        return device_code_credential_;
    }

    const Scopes& scopes() const { return scopes_; }

private:
    DeviceCodeCredential device_code_credential_;
    Scopes scopes_;
};

}  // namespace teams::priv
