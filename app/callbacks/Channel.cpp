#include "Channel.hpp"

// #include <print>
#include <future>
#include <iostream>

#include "subcommands/Channel.hpp"
#include "teams_lib/models/Channel.hpp"
#include "utils.hpp"

namespace callbacks::channel {
void add(sub::channel::AddOptions const& options,
         teams::GraphServiceClient const& client) {
    std::vector<std::future<void>> futures;

    auto team_id = utils::getTeamId(options.team, client);
    if (!team_id.has_value()) {
        std::cerr << "Team does not exist\n";
        return;
    }
    std::string const visibility = options.isPublic ? "standard" : "private";
    for (auto name : options.name) {
        futures.emplace_back(std::async(std::launch::async, [&, name]() {
            auto channel = teams::Channel{.display_name = name,
                                          .membership_type = visibility};
            auto result =
                client.teams().byId(team_id.value()).channels().post(channel);

            if (!result) {
                std::visit(
                    [](const auto& e) { std::cout << e.message << '\n'; },
                    result.error());
                return;
            }
        }));
    }
    for (auto& f : futures) {
        f.get();
    }
}

void remove(sub::channel::RemoveOptions const& options,
            teams::GraphServiceClient const& client) {
    std::vector<std::future<void>> futures;

    auto team_id = utils::getTeamId(options.team, client);
    if (!team_id.has_value()) {
        std::cerr << "Team does not exist\n";
        return;
    }
    for (const auto& name : options.name) {
        futures.emplace_back(std::async(std::launch::async, [&, name]() {
            auto channel_id =
                utils::getChannelId(team_id.value(), client, name);
            if (!channel_id.has_value()) {
                std::cerr << "Team does not exist\n";
                return;
            }

            auto result = client.teams()
                              .byId(team_id.value())
                              .channels()
                              .byId(channel_id.value())
                              .remove();

            if (!result) {
                std::visit(
                    [](const auto& e) { std::cout << e.message << '\n'; },
                    result.error());
                return;
            }
        }));
    }

    for (auto& f : futures) {
        f.get();
    }
}

void list(sub::channel::ListOptions const& options,
          teams::GraphServiceClient const& client) {
    auto team_id = utils::getTeamId(options.team, client);
    if (team_id.has_value()) {
        auto const channels =
            client.teams().byId(team_id.value()).channels().get();

        // std::println("List of channels:");
        std::cout << "List of channels:\n";
        if (channels) {
            for (auto const [idx, channel] :
                 std::views::enumerate(channels.value())) {
                // std::println("{}. {}", idx,
                // channel.display_name.value());
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
