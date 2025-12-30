#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <string>

namespace teams::priv {
enum class BodyType : std::uint8_t { HTML, TEXT };

struct ItemBody {
    std::string content;
    std::string content_type;
};

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const ItemBody& body);
void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, ItemBody& body);

}  // namespace teams::priv
