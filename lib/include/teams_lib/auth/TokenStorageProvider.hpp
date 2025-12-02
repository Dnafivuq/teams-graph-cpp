#pragma once

#include <optional>
#include <teams_lib/common.hpp>

namespace teams::priv {

template <typename DerivedProvider>
class TokenStorageProvider {
public:
    TokenStorageProvider() = default;

    std::optional<RefreshToken> load() const {
        return static_cast<const DerivedProvider*>(this)->loadImpl();
    };

    void store(const RefreshToken& token) const {
        static_cast<const DerivedProvider*>(this)->storeImpl(token);
    };
};
}  // namespace teams::priv
