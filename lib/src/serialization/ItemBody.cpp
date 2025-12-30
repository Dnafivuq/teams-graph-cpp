#include <teams_lib/models/ItemBody.hpp>

#include "Optional.hpp"  // IWYU pragma: keep

namespace teams::priv {

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const ItemBody& body) {
    json = nlohmann::json{{"content", body.content},
                          {"contentType", body.content_type}};
}

void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, ItemBody& body) {
    json.at("content").get_to(body.content);
    json.at("contentType").get_to(body.content_type);
}

}  // namespace teams::priv