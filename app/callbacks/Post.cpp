#include "Post.hpp"

#include <optional>
#include <variant>

#include "utils.hpp"

namespace callbacks::post {
void add(sub::post::AddOptions const& options,
         teams::GraphServiceClient& client) {
    // TODO!
    // Channel and team is currently hardcoded by id

    auto msg =
        teams::Message{.body = teams::priv::ItemBody{.content = options.text,
                                                     .content_type = "text"}};
    auto result =
        client.teams()
            .byId("948a9a8c-04f9-4e1c-9423-60b68f29b7dc")
            .channels()
            .byId("19%3A3d5b1a7b3530488da59fd2df72ace3f8%40thread.tacv2")
            .messages()
            .post(msg);
}
void list(sub::post::ListOptions const& options,
          teams::GraphServiceClient& client) {
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
