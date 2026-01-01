#include "Channel.hpp"

#include <print>

namespace callbacks::channel {
void add(sub::channel::AddOptions const& options,
         teams::GraphServiceClient& client) {}

void list(sub::channel::ListOptions const& options,
          teams::GraphServiceClient& client) {
    // TODO!
    // Channel and team is currently hardoded by id
    auto channels = client.teams()
                        .byId("948a9a8c-04f9-4e1c-9423-60b68f29b7dc")
                        .channels()
                        .get();

    std::println("List of channels:");
    if (channels) {
        for (auto idx = 0; const auto& channel : channels.value()) {
            std::println("{}. {}", ++idx, channel.display_name.value());
        }
    }
}
}  // namespace callbacks::channel
