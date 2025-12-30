#include <teams_lib/models/ChannelIdentity.hpp>

#include "Optional.hpp"  // IWYU pragma: keep

namespace teams::priv {

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const ChannelIdentity& channel_identity) {
    json = nlohmann::json{{"channelId", channel_identity.channel_id},
                          {"teamId", channel_identity.team_id}};
}

void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, ChannelIdentity& channel_identity) {
    json.at("channelId").get_to(channel_identity.channel_id);
    json.at("teamId").get_to(channel_identity.team_id);
}

}  // namespace teams::priv