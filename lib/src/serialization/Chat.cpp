#include <teams_lib/models/Chat.hpp>

#include "Optional.hpp"  // IWYU pragma: keep

namespace teams::priv {

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const Chat& chat) {
    if (chat.id && !chat.id.value().empty()) {
        json["id"] = chat.id;
    }
    if (chat.type && !chat.type.value().empty()) {
        json["chatType"] = chat.type.value();
    }
    if (chat.topic && !chat.topic.value().empty()) {
        json["topic"] = chat.topic.value();
    }
    if (chat.members && !chat.members.value().empty()) {
        json["members"] = chat.members.value();
    }
}

void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, Chat& chat) {
    if (json.contains("id")) {
        json.at("id").get_to(chat.id);
    }
    if (json.contains("chatType")) {
        json.at("chatType").get_to(chat.type);
    }
    if (json.contains("topic")) {
        json.at("topic").get_to(chat.topic);
    }
    if (json.contains("members")) {
        json.at("members").get_to(chat.members);
    }
}

}  // namespace teams::priv