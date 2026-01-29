#include <teams_lib/models/UserIdentity.hpp>

#include "Optional.hpp"  // IWYU pragma: keep

namespace teams::priv {

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const UserIdentity& user) {
    json = nlohmann::json{{"displayName", user.display_name}, {"id", user.id}};
}

void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, UserIdentity& user) {
    const auto& user_json = json.at("user");
    user_json.at("displayName").get_to(user.display_name);
    user_json.at("id").get_to(user.id);
}

}  // namespace teams::priv
