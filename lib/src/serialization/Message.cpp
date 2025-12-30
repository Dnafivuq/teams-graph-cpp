#include <teams_lib/models/Message.hpp>

#include "Optional.hpp"  // IWYU pragma: keep

namespace teams::priv {

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const Message& message) {
    json = nlohmann::json{{"body", message.body}};

    if (message.id && !message.id.value().empty()) {
        json["id"] = message.id;
    }

    if (message.channel_identity) {
        json["channelIdentity"] = message.channel_identity.value();
    }

    if (message.chat_id && !message.chat_id.value().empty()) {
        json["chatId"] = message.chat_id.value();
    }
    // TODO: change in the future
    if (message.from) {
        json["from"] = {"user", message.from};
    }
}

void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, Message& message) {
    json.at("body").get_to(message.body);

    if (json.contains("id")) {
        json.at("id").get_to(message.id);
    }

    if (json.contains("channelIdentity")) {
        json.at("channelIdentity").get_to(message.channel_identity);
    }

    if (json.contains("chatId")) {
        json.at("chatId").get_to(message.chat_id);
    }

    if (json.contains("from")) {
        json.at("from").get_to(message.from);
    }
}

}  // namespace teams::priv