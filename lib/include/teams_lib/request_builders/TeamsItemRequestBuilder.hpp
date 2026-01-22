#pragma once

#include <teams_lib/models/Team.hpp>
#include <teams_lib/request_builders/ChannelsRequestBuilder.hpp>

namespace teams::priv {

template <typename ClientType>
class TeamsItemRequestBuilder : public RequestBuilder<ClientType, Team> {
    using base_t = RequestBuilder<ClientType, Team>;

    using base_t::baseUrl;
    using base_t::client;

public:
    explicit TeamsItemRequestBuilder(const ClientType* client, URL base_url,
                                     ID team_id)
        : base_t{client, std::move(base_url)}, team_id_{std::move(team_id)} {}

    ChannelsRequestBuilder<ClientType> channels() {
        return ChannelsRequestBuilder<ClientType>{client(),
                                                  baseUrl() + "/channels"};
    }

    ConversationMembersRequestBuilder<ClientType> members() {
        return ConversationMembersRequestBuilder<ClientType>{
            client(), baseUrl() + "/members"};
    }

    ClientResponse<void> remove() const noexcept {
        return client()->template remove<void>(
            std::format("groups/{}", team_id_));
    }

private:
    ID team_id_;
};
}  // namespace teams::priv