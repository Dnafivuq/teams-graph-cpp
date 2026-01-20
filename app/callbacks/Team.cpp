#include "Team.hpp"

// #include <print>
#include <iostream>

#include "teams_lib/models/Team.hpp"

namespace callbacks::team {
void add(sub::team::AddOptions const& options,
         teams::GraphServiceClient const& client) {
    auto team = teams::Team{
        .display_name = options.name,
        .additional_data = std::unordered_map<std::string, std::string>{
            {"template@odata.bind",
             "https://graph.microsoft.com/v1.0/teamsTemplates('standard')"}}};

    auto result = client.teams().post(team);

    if (!result) {
        std::visit([](const auto& e) { std::cout << e.message << '\n'; },
                   result.error());
        return;
    }
}

void list(sub::team::ListOptions const& options,
          teams::GraphServiceClient const& client) {
    auto const teams = client.teams().get();
    // std::println("List of teams:");
    std::cout << "List of teams:\n";
    if (teams) {
        for (auto const [idx, team] : std::views::enumerate(teams.value())) {
            // std::println("{}. {}", idx, team.display_name.value());
            std::cout << idx << ". " << team.display_name.value() << '\n';
        }
    }
}
}  // namespace callbacks::team
