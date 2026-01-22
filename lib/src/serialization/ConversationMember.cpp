#include <format>
#include <teams_lib/models/ConversationMember.hpp>

#include "Optional.hpp"  // IWYU pragma: keep

namespace teams::priv {

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const ConversationMember& member) {
    if (member.id && !member.id.value().empty()) {
        json["userId"] = member.id.value();
    }
    if (member.membership_id && !member.membership_id.value().empty()) {
        json["id"] = member.id.value();
    }
    if (member.display_name && !member.display_name.value().empty()) {
        json["displayName"] = member.display_name.value();
    }
    if (member.email && !member.email.value().empty()) {
        json["email"] = member.email.value();
    }

    // roles can be empty and are still meaningful for graph api
    if (member.roles) {
        json["roles"] = member.roles.value();
    }

    if (member.history_visibility_start) {
        json["visibleHistoryStartDateTime"] =
            std::format("{:%FT%T}.{:03}Z",
                        floor<std::chrono::seconds>(
                            member.history_visibility_start.value()),
                        .000);
    }
    // else {
    //     json["visibleHistoryStartDateTime"] = "0001-01-01T00:00:00Z";
    // }

    json["@odata.type"] = "#microsoft.graph.aadUserConversationMember";
    if (member.id && !member.id.value().empty()) {
        json["user@odata.bind"] = std::format(
            "https://graph.microsoft.com/v1.0/users('{}')", member.id.value());
    } else if (member.email && !member.email.value().empty()) {
        json["user@odata.bind"] =
            std::format("https://graph.microsoft.com/v1.0/users('{}')",
                        member.email.value());
    }
}

void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, ConversationMember& member) {
    if (json.contains("id")) {
        json.at("id").get_to(member.membership_id);
    }
    if (json.contains("userId")) {
        json.at("id").get_to(member.id);
    }
    if (json.contains("displayName")) {
        json.at("displayName").get_to(member.display_name);
    }
    if (json.contains("email")) {
        json.at("email").get_to(member.email);
    }
    if (json.contains("roles")) {
        json.at("roles").get_to(member.roles);
    }
}

}  // namespace teams::priv