#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <teams_lib/models/ConversationMember.hpp>

namespace teams {
namespace priv {

struct Chat {
    std::optional<std::string> id;
    std::optional<std::string> type;
    std::optional<std::string> topic;
    std::optional<std::vector<ConversationMember>> members;
};

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const Chat& chat);
void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, Chat& chat);

}  // namespace priv
using Chat = priv::Chat;
}  // namespace teams