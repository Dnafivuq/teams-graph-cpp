#include "Team.hpp"

// #include <print>
#include <future>
#include <iostream>

#include "teams_lib/models/Team.hpp"
#include "utils.hpp"

namespace callbacks::team {
void add(sub::team::AddOptions const& options,
         teams::GraphServiceClient const& client) {
    std::vector<std::future<void>> futures;

    futures.reserve(options.names.size());
    for (const auto& name : options.names) {
        futures.emplace_back(std::async(std::launch::async, [&, name]() {
            auto team = teams::Team{
                .display_name = name,
                .additional_data = std::unordered_map<std::string, std::string>{
                    {"template@odata.bind",
                     "https://graph.microsoft.com/v1.0/"
                     "teamsTemplates('standard')"}}};

            auto result = client.teams().post(team);

            if (!result) {
                std::visit(
                    [](const auto& err) { std::cout << err.message << '\n'; },
                    result.error());
            }
        }));
    }

    for (auto& fut : futures) {
        fut.get();
    }
}

void remove(sub::team::RemoveOptions const& options,
            teams::GraphServiceClient const& client) {
    std::vector<std::future<void>> futures;

    futures.reserve(options.names.size());
    for (auto const& name : options.names) {
        futures.emplace_back(std::async(std::launch::async, [&, name]() {
            auto team_id = utils::getTeamId(name, client);
            if (!team_id.has_value()) {
                std::cerr << "Team does not exist\n";
                return;
            }

            auto result = client.teams().byId(team_id.value()).remove();

            if (!result) {
                std::visit(
                    [](const auto& err) { std::cout << err.message << '\n'; },
                    result.error());
            }
        }));
    }

    for (auto& fut : futures) {
        fut.get();
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
