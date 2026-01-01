#pragma once
#include <nlohmann/json.hpp>
#include <teams_lib/common.hpp>
#include <teams_lib/models/ChannelIdentity.hpp>
#include <teams_lib/models/ItemBody.hpp>
#include <teams_lib/models/UserIdentity.hpp>

namespace teams {
namespace priv {

struct Message {
    std::optional<ID> id;
    std::optional<ID> chat_id;
    std::optional<ChannelIdentity> channel_identity;
    std::optional<ItemBody> body;
    std::optional<UserIdentity> from;
};

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const Message& message);
void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, Message& message);

}  // namespace priv
using Message = priv::Message;
}  // namespace teams