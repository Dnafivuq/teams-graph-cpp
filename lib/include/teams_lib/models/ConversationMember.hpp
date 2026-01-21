#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <chrono>

namespace teams {
namespace priv {

struct ConversationMember {
    std::optional<std::string> id;
    std::optional<std::string> membership_id;
    std::optional<std::string> display_name;
    std::optional<std::string> email;
    std::optional<std::chrono::system_clock::time_point> history_visibility_start;
    std::optional<std::vector<std::string>> roles;
};

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const ConversationMember& member);
void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, ConversationMember& member);

}  // namespace priv
using ConversationMember = priv::ConversationMember;
}  // namespace teams