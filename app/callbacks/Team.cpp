#include "Team.hpp"

#include <print>

namespace callbacks::team {
void add(sub::team::AddOptions const& options,
         teams::GraphServiceClient& client) {}

void list(sub::team::ListOptions const& options,
          teams::GraphServiceClient& client) {
    auto teams = client.teams().get();
    std::println("List of teams:");
    if (teams) {
        for (auto idx = 0; const auto& team : teams.value()) {
            std::println("{}. {}", ++idx, team.display_name.value());
        }
    }
}
}  // namespace callbacks::team
