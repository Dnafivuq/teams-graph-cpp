#include "Channel.hpp"

// #include <print>

#include <iostream>

#include "utils.hpp"

namespace callbacks::channel {
void add(sub::channel::AddOptions const& options,
         teams::GraphServiceClient& client) {}

void list(sub::channel::ListOptions const& options,
          teams::GraphServiceClient& client) {
    auto team_id = utils::getTeamId(options.team, client);
    if (team_id.has_value()) {
        auto const channels =
            client.teams().byId(team_id.value()).channels().get();

        // std::println("List of channels:");
        std::cout << "List of channels:\n";
        if (channels) {
            for (auto const [idx, channel] :
                 std::views::enumerate(channels.value())) {
                // std::println("{}. {}", idx, channel.display_name.value());
                std::cout << idx << ". " << channel.display_name.value()
                          << "\n";
            }
        }
    } else {
        // std::println("There is no team with the given name.");
        std::cout << "There is no team with the given name.\n";
    }
}
}  // namespace callbacks::channel
