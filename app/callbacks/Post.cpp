#include "Post.hpp"

namespace callbacks::post {
void add(sub::post::AddOptions const& options,
         teams::GraphServiceClient& client) {
    // TODO!
    // Channel and team is currently hardcoded by id

    auto msg = teams::Message{
        .channel_identity =
            teams::priv::ChannelIdentity{
                .channel_id =
                    "19%3A3d5b1a7b3530488da59fd2df72ace3f8%40thread.tacv2",
                .team_id = "948a9a8c-04f9-4e1c-9423-60b68f29b7dc"},
        .body = teams::priv::ItemBody{.content = options.text,
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
          teams::GraphServiceClient& client) {}
}  // namespace callbacks::post
