#include "Post.hpp"

#include <ranges>
#include <string>
#include <variant>

#include "utils.hpp"

namespace callbacks::post {
void sendMessage(std::string channel_id, std::string team_id,  // NOLINT
                 const std::string& text,
                 teams::GraphServiceClient const& client) {
    auto msg = teams::Message{
        .body = teams::priv::ItemBody{.content = text, .content_type = "text"}};

    auto result = client.teams()
                      .byId(team_id)
                      .channels()
                      .byId(channel_id)
                      .messages()
                      .post(msg);

    if (!result) {
        std::visit([](const auto& err) { std::cout << err.message << '\n'; },
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

            sendMessage(channel_id.value(), team_id.value(), options.text,
                        client);
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

            sendMessage(channel_id.value(), team_id.value(), options.text,
                        client);
        }
    }
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
        std::visit([](const auto& err) { std::cout << err.message << '\n'; },
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
