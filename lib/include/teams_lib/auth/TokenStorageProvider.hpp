#pragma once

#include <optional>
#include <teams_lib/common.hpp>

namespace teams::priv {

template <typename DerivedProvider>
class TokenStorageProvider {
public:
    TokenStorageProvider() = default;

    std::optional<RefreshToken> loadRefreshToken() const {
        return static_cast<const DerivedProvider*>(this)
            ->loadRefreshTokenImpl();
    };

    void storeRefreshToken(const RefreshToken& token) const {
        static_cast<const DerivedProvider*>(this)->storeRefreshTokenImpl(token);
    };
};
}  // namespace teams::priv
