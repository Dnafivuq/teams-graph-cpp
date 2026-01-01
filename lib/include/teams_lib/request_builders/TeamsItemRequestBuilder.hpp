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
    explicit TeamsItemRequestBuilder(const ClientType* client, URL base_url)
        : base_t{client, std::move(base_url)} {}

    ChannelsRequestBuilder<ClientType> channels() {
        return ChannelsRequestBuilder<ClientType>{client(),
                                                  baseUrl() + "/channels"};
    }
};
}  // namespace teams::priv