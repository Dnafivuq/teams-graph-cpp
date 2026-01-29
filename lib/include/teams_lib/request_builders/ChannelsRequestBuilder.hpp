#pragma once

#include <teams_lib/request_builders/ChannelsItemRequestBuilder.hpp>

namespace teams::priv {

template <typename ClientType>
class ChannelsRequestBuilder
    : public RequestBuilder<ClientType, Collection<Channel>> {
    using base_t = RequestBuilder<ClientType, Collection<Channel>>;

    using base_t::baseUrl;
    using base_t::client;

public:
    explicit ChannelsRequestBuilder(const ClientType* client, URL url)
        : base_t{client, std::move(url)} {}

    ChannelsItemRequestBuilder<ClientType> byId(const ID& channel_id) {
        return ChannelsItemRequestBuilder<ClientType>{
            client(), baseUrl() + "/" + channel_id};
    }
};
}  // namespace teams::priv

