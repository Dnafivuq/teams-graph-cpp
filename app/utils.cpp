#include "utils.hpp"

namespace utils {
std::optional<std::string> getTeamId(const std::string& team_name,
                                     teams::GraphServiceClient const& client) {
    auto const teams = client.teams().get();
    for (auto const& team : teams.value()) {
        if (team.display_name.value() == team_name) {
            return team.id;
        }
    }
    return {};
}

std::optional<std::string> getChannelId(const std::string& team_id,
                                        teams::GraphServiceClient const& client,
                                        const std::string& channel_name) {
    auto const channels = client.teams().byId(team_id).channels().get();

    for (auto const& channel : channels.value()) {
        if (channel.display_name.value() == channel_name) {
            return channel.id;
        }
    }
    return {};
}
}  // namespace utils