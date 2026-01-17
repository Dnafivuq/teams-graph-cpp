#include <optional>
#include <string>
#include <teams_lib/client/GraphServiceClient.hpp>

std::optional<std::string> getTeamId(const std::string& team_name,
                                     teams::GraphServiceClient& client) {
    auto const teams = client.teams().get();
    for (auto const& team : teams.value()) {
        if (team.display_name.value() == team_name) {
            return team.id;
        }
    }
    return {};
}
