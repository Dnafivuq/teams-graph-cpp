#include "teams_lib/models/Chat.hpp"

#include <iostream>
#include <vector>

#include "subcommands/Chat.hpp"
#include "teams_lib/client/GraphServiceClient.hpp"
#include "teams_lib/models/ConversationMember.hpp"

namespace callbacks::chat {
void add(sub::chat::AddOptions const& options,
         teams::GraphServiceClient const& client) {
    std::vector<teams::ConversationMember> members;
    std::vector<std::string> roles{"owner"};
    auto const user_profile = client.me().get();
    if (!user_profile.has_value()) {
        std::cerr << "Failed to get me";
        return;
    }
    members.push_back({.id = user_profile->id, .roles = roles});
    for (auto const& email : options.emails) {
        auto const user = client.users().byEmail(email).get();
        if (!user.has_value()) {
            std::cerr << "Failed to get find " << email;
            return;
        }
        members.push_back({.id = user->id, .roles = roles});
    }
    std::string const type = (members.size() > 2) ? "group" : "oneOnOne";

    teams::Chat const chat{.type = type, .members = members};

    auto const result = client.chats().post(chat);

    if (!result) {
        std::visit([](const auto& err) { std::cout << err.message << '\n'; },
                   result.error());
        return;
    }
}

void list(sub::chat::ListOptions const& options,
          teams::GraphServiceClient const& client) {}
}  // namespace callbacks::chat
