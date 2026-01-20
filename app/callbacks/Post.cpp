#include "Post.hpp"

#include <optional>
#include <ranges>
#include <variant>

#include "utils.hpp"

namespace callbacks::post {
void sendMessage(auto channel_id, auto team_id, const auto& text,
                 const auto& client) {
    auto msg = teams::Message{
        .body = teams::priv::ItemBody{.content = text, .content_type = "text"}};

    auto result = client.teams()
                      .byId(team_id.value())
                      .channels()
                      .byId(channel_id.value())
                      .messages()
                      .post(msg);

    if (!result) {
        std::visit([](const auto& e) { std::cout << e.message << '\n'; },
                   result.error());
        return;
    }
}

void add(sub::post::AddOptions const& options,
         teams::GraphServiceClient const& client) {
    if (options.team.size() == 1) {
        auto team_id = utils::getTeamId(options.team[0], client);
        if (!team_id.has_value()) {
            std::cerr << "Team does not exist\n";
            return;
        }

        for (const auto& channel : options.channel) {
            auto channel_id =
                utils::getChannelId(team_id.value(), client, channel);
            if (!channel_id.has_value()) {
                std::cerr << "Channel does not exist\n";
                return;
            }

            sendMessage(channel_id, team_id, options.text, client);
        }
    } else {
        if (options.team.size() != options.channel.size()) {
            std::cerr
                << "Error: the number of teams and channels must be equal.\n";
            return;
        }

        for (auto const [idx, team] : std::views::enumerate(options.team)) {
            const auto& channel = options.channel[idx];

            auto team_id = utils::getTeamId(team, client);
            if (!team_id.has_value()) {
                std::cerr << "Team does not exist\n";
                return;
            }

            auto channel_id =
                utils::getChannelId(team_id.value(), client, channel);
            if (!channel_id.has_value()) {
                std::cerr << "Channel does not exist\n";
                return;
            }

            sendMessage(channel_id, team_id, options.text, client);
        }
    }
    // auto team_id = utils::getTeamId(options.team, client);
    // if (!team_id.has_value()) {
    //     std::cerr << "Team does not exist\n";
    //     return;
    // }
    // auto channel_id =
    //     utils::getChannelId(team_id.value(), client, options.channel);
    // if (!channel_id.has_value()) {
    //     std::cerr << "Channel does not exist\n";
    //     return;
    // }

    // auto msg =
    //     teams::Message{.body = teams::priv::ItemBody{.content =
    //     options.text,
    //                                                  .content_type =
    //                                                  "text"}};
    // auto result = client.teams()
    //                   .byId(team_id.value())
    //                   .channels()
    //                   .byId(channel_id.value())
    //                   .messages()
    //                   .post(msg);

    // if (!result) {
    //     std::visit([](const auto& e) { std::cout << e.message << '\n'; },
    //                result.error());
    //     return;
    // }
}
void list(sub::post::ListOptions const& options,
          teams::GraphServiceClient const& client) {
    auto team_id = utils::getTeamId(options.team, client);
    if (!team_id.has_value()) {
        std::cerr << "Team does not exist\n";
        return;
    }
    auto channel_id =
        utils::getChannelId(team_id.value(), client, options.channel);
    if (!channel_id.has_value()) {
        std::cerr << "Channel does not exist\n";
        return;
    }

    auto posts = client.teams()
                     .byId(team_id.value())
                     .channels()
                     .byId(channel_id.value())
                     .messages()
                     .get();

    if (!posts) {
        std::visit([](const auto& e) { std::cout << e.message << '\n'; },
                   posts.error());
        return;
    }

    std::cout << "List of posts:\n";
    if (posts.has_value()) {
        for (auto const [idx, post] : std::views::enumerate(posts.value())) {
            // std::println("{}. {}", idx, channel.display_name.value());
            if (post.from.has_value()) {
                std::cout << idx << ". " << post.from->display_name << "\n";
            }
            if (post.body.has_value()) {
                std::cout << post.body->content << "\n";
            }
        }
    }
}
}  // namespace callbacks::post
