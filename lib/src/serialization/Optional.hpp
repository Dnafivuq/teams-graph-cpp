#pragma once
#include <nlohmann/json.hpp>
#include <optional>

namespace nlohmann {
template <typename T>
struct adl_serializer<std::optional<T>> {
    static void to_json(  // NOLINT(readability-identifier-naming)
        json& json, const std::optional<T>& opt) {
        if (opt) {
            json = *opt;
        } else {
            json = nullptr;
        }
    }
    static void from_json(  // NOLINT(readability-identifier-naming)
        const json& json, std::optional<T>& opt) {
        if (json.is_null()) {
            opt = std::nullopt;
        } else {
            opt = json.get<T>();
        }
    }
};
}  // namespace nlohmann
