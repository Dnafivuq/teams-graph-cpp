#pragma once
#include <optional>
#include <string>
#include <teams_lib/client/GraphServiceClient.hpp>

namespace utils {
std::optional<std::string> getTeamId(const std::string& team_name,
                                     teams::GraphServiceClient& client);

std::optional<std::string> getChannelId(const std::string& team_id,
                                        teams::GraphServiceClient& client,
                                        const std::string& channel_name);
}  // namespace utils