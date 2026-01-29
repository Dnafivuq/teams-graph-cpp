#include <teams_lib/models/Channel.hpp>

#include "Optional.hpp"  // IWYU pragma: keep

namespace teams::priv {

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const Channel& channel) {
    if (channel.id && !channel.id.value().empty()) {
        json["id"] = channel.id;
    }
    if (channel.display_name && !channel.display_name.value().empty()) {
        json["displayName"] = channel.display_name.value();
    }
    if (channel.description && !channel.description.value().empty()) {
        json["description"] = channel.description.value();
    }
    if (channel.membership_type && !channel.membership_type.value().empty()) {
        json["membershipType"] = channel.membership_type.value();
    }
}

void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, Channel& channel) {
    if (json.contains("id")) {
        json.at("id").get_to(channel.id);
    }
    if (json.contains("displayName")) {
        json.at("displayName").get_to(channel.display_name);
    }
    if (json.contains("description")) {
        json.at("description").get_to(channel.description);
    }
    if (json.contains("membershipType")) {
        json.at("membershipType").get_to(channel.membership_type);
    }
}

}  // namespace teams::priv
