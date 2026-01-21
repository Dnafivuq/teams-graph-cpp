#include "Member.hpp"

// #include <print>
#include <algorithm>
#include <future>
#include <iostream>
#include <optional>

#include "subcommands/Channel.hpp"
#include "teams_lib/client/ClientResponse.hpp"
#include "teams_lib/models/Channel.hpp"
#include "teams_lib/models/ConversationMember.hpp"
#include "teams_lib/models/Message.hpp"
#include "utils.hpp"

namespace callbacks::member {
void add(sub::member::AddOptions const& options,
         teams::GraphServiceClient const& client) {
    std::vector<std::future<void>> futures;

    auto team_id = utils::getTeamId(options.team, client);
    if (!team_id.has_value()) {
        std::cerr << "Team does not exist\n";
        return;
    }
    std::optional<std::string> channel_id;
    if (options.channel != "") {
        channel_id = utils::getChannelId(*team_id, client, options.channel);
    }
    if (!team_id.has_value() && options.channel != "") {
        std::cerr << "Team does not exist\n";
        return;
    }

    for (auto email : options.email) {
        futures.emplace_back(std::async(std::launch::async, [&, email]() {
            teams::ClientResponse<teams::ConversationMember> result;

            if (options.channel == "") {
                result = client.teams().byId(*team_id).members().post(
                    {.email = email});
            } else {
                result = client.teams()
                             .byId(*team_id)
                             .channels()
                             .byId(*channel_id)
                             .members()
                             .post({.email = email});
            };

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

void remove(sub::member::RemoveOptions const& options,
            teams::GraphServiceClient const& client) {
    std::vector<std::future<void>> futures;

    auto team_id = utils::getTeamId(options.team, client);
    if (!team_id.has_value()) {
        std::cerr << "Team does not exist\n";
        return;
    }
    std::optional<std::string> channel_id;
    if (options.channel != "") {
        channel_id = utils::getChannelId(*team_id, client, options.channel);
    }
    if (!team_id.has_value() && options.channel != "") {
        std::cerr << "Team does not exist\n";
        return;
    }

    teams::ClientResponse<std::vector<teams::ConversationMember>> result;
    if (options.channel == "") {
        result = client.teams().byId(*team_id).members().get();
    } else {
        result = client.teams()
                     .byId(*team_id)
                     .channels()
                     .byId(*channel_id)
                     .members()
                     .get();
    };

    if (!result) {
        std::visit([](const auto& e) { std::cout << e.message << '\n'; },
                   result.error());
        return;
    }

    std::vector<std::string> membership_ids;
    for (const auto& m : *result) {
        if (std::ranges::contains(options.email, m.email)) {
            membership_ids.push_back(*m.membership_id);
        }
    }

    if (!result) {
        std::visit([](const auto& e) { std::cout << e.message << '\n'; },
                   result.error());
        return;
    }
    for (auto id : membership_ids) {
        futures.emplace_back(std::async(std::launch::async, [&, id]() {
            teams::ClientResponse<void> result;

            if (options.channel == "") {
                result = client.teams().byId(*team_id).members().remove(
                    {.membership_id = id});
            } else {
                auto const result = client.teams()
                                        .byId(*team_id)
                                        .channels()
                                        .byId(*channel_id)
                                        .members()
                                        .remove({.membership_id = id});
            };

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

void list(sub::member::ListOptions const& options,
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
}  // namespace callbacks::member