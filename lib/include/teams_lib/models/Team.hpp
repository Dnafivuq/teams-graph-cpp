#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <teams_lib/models/Channel.hpp>
#include <teams_lib/models/ConversationMember.hpp>
#include <unordered_map>

namespace teams {
namespace priv {

struct Team {
    std::optional<std::string> id;
    std::optional<std::string> display_name;
    std::optional<std::string> description;
    std::optional<std::string> first_channel_name;
    std::optional<std::vector<Channel>> channels;
    std::optional<std::vector<ConversationMember>> members;
    std::optional<std::unordered_map<std::string, std::string>> additional_data;
};

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const Team& team);
void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, Team& team);

}  // namespace priv
using Team = priv::Team;
}  // namespace teams
