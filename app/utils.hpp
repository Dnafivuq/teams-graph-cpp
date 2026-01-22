#pragma once
#include <optional>
#include <string>
#include <teams_lib/client/GraphServiceClient.hpp>
namespace fs = std::filesystem;

namespace utils {
fs::path find_repo_root(fs::path start);
std::optional<std::string> getTeamId(const std::string& team_name,
                                     teams::GraphServiceClient const& client);

std::optional<std::string> getChannelId(const std::string& team_id,
                                        teams::GraphServiceClient const& client,
                                        const std::string& channel_name);

}  // namespace utils
