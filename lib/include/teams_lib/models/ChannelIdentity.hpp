#pragma once
#include <nlohmann/json.hpp>
#include <teams_lib/common.hpp>

namespace teams::priv {

struct ChannelIdentity {
    ID channel_id;
    ID team_id;
};

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const ChannelIdentity& channel_identity);
void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, ChannelIdentity& channel_identity);
}  // namespace teams::priv
