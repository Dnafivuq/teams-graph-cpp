#include <format>
#include <teams_lib/models/User.hpp>

#include "Optional.hpp"  // IWYU pragma: keep

namespace teams::priv {

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const User& user) {
    if (user.id && !user.id.value().empty()) {
        json["id"] = user.id.value();
    }
    if (user.display_name && !user.display_name.value().empty()) {
        json["displayName"] = user.display_name.value();
    }
    if (user.email && !user.email.value().empty()) {
        json["email"] = user.email.value();
    }
}

void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, User& user) {
    if (json.contains("id")) {
        json.at("id").get_to(user.id);
    }
    if (json.contains("displayName")) {
        json.at("displayName").get_to(user.display_name);
    }
    if (json.contains("email")) {
        json.at("email").get_to(user.email);
    }
}

}  // namespace teams::priv