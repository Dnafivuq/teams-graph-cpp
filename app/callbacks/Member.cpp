#include "Member.hpp"

#include <algorithm>
#include <future>
#include <iostream>
#include <optional>

#include "teams_lib/client/ClientResponse.hpp"
#include "teams_lib/models/ConversationMember.hpp"
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

    futures.reserve(options.email.size());
    for (const auto& email : options.email) {
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
                    [](const auto& err) { std::cout << err.message << '\n'; },
                    result.error());
                return;
            }
        }));
    }
    for (auto& fut : futures) {
        fut.get();
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
        std::visit([](const auto& err) { std::cout << err.message << '\n'; },
                   result.error());
        return;
    }

    std::vector<std::string> membership_ids;
    for (const auto& mem : *result) {
        if (std::ranges::contains(options.email, mem.email)) {
            membership_ids.push_back(*mem.membership_id);
        }
    }

    if (!result) {
        std::visit([](const auto& err) { std::cout << err.message << '\n'; },
                   result.error());
        return;
    }
    futures.reserve(membership_ids.size());
    for (const auto& m_id : membership_ids) {
        futures.emplace_back(std::async(std::launch::async, [&, m_id]() {
            teams::ClientResponse<void> result;

            if (options.channel == "") {
                result = client.teams().byId(*team_id).members().remove(
                    {.membership_id = m_id});
            } else {
                auto const result = client.teams()
                                        .byId(*team_id)
                                        .channels()
                                        .byId(*channel_id)
                                        .members()
                                        .remove({.membership_id = m_id});
            };

            if (!result) {
                std::visit(
                    [](const auto& err) { std::cout << err.message << '\n'; },
                    result.error());
                return;
            }
        }));
    }
    for (auto& fut : futures) {
        fut.get();
    }
}

void list(sub::member::ListOptions const& options,
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
        std::visit([](const auto& err) { std::cout << err.message << '\n'; },
                   result.error());
        return;
    }

    std::cout << "List of members\n";
    for (auto const [idx, member] : std::views::enumerate(result.value())) {
        if (member.display_name) {
            std::cout << idx << ". " << member.display_name.value() << "\n";
        }
    }
}
}  // namespace callbacks::member
