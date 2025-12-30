#include <teams_lib/models/Team.hpp>

#include "Optional.hpp"  // IWYU pragma: keep

namespace teams::priv {

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const Team& team) {
    // json = nlohmann::json{{"displayName", team.display_name},
    //                       {"description", team.description}};

    if (team.id && !team.id.value().empty()) {
        json["id"] = team.id;
    }
    if (team.display_name && !team.display_name.value().empty()) {
        json["displayName"] = team.display_name.value();
    }
    if (team.description && !team.description.value().empty()) {
        json["description"] = team.description.value();
    }
    if (team.first_channel_name && !team.first_channel_name.value().empty()) {
        json["firstChannelName"] = team.first_channel_name;
    }
    if (team.additional_data) {
        for (const auto& [key, value] : team.additional_data.value()) {
            json[key] = value;
        }
    }
}

void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, Team& team) {
    if (json.contains("id")) {
        json.at("id").get_to(team.id);
    }
    if (json.contains("displayName")) {
        json.at("displayName").get_to(team.display_name);
    }
    if (json.contains("description")) {
        json.at("description").get_to(team.description);
    }
    if (json.contains("first_channel_name")) {
        json.at("first_channel_name").get_to(team.first_channel_name);
    }
}

}  // namespace teams::priv