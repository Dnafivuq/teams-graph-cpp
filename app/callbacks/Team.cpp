#include "Team.hpp"

#include <print>

namespace callbacks::team {
void add(sub::team::AddOptions const& options,
         teams::GraphServiceClient& client) {}

void list(sub::team::ListOptions const& options,
          teams::GraphServiceClient& client) {
    auto const teams = client.teams().get();
    std::println("List of teams:");
    if (teams) {
        for (auto const [idx, team] : std::views::enumerate(teams.value())) {
            std::println("{}. {}", idx, team.display_name.value());
        }
    }
}
}  // namespace callbacks::team
