#include "Channel.hpp"

#include <print>

#include "utils.hpp"

namespace callbacks::channel {
void add(sub::channel::AddOptions const& options,
         teams::GraphServiceClient& client) {}

void list(sub::channel::ListOptions const& options,
          teams::GraphServiceClient& client) {
    auto team_id = getTeamId(options.team, client);
    if (team_id.has_value()) {
        auto const channels =
            client.teams().byId(team_id.value()).channels().get();

        std::println("List of channels:");
        if (channels) {
            for (auto const [idx, channel] :
                 std::views::enumerate(channels.value())) {
                std::println("{}. {}", idx, channel.display_name.value());
            }
        }
    } else {
        std::println("There is no team with the given name.");
    }
}
}  // namespace callbacks::channel
