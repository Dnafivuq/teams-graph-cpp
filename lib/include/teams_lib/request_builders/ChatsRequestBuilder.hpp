#pragma once

#include <teams_lib/request_builders/ChatsItemRequestBuilder.hpp>

namespace teams::priv {

template <typename ClientType>
class ChatsRequestBuilder
    : public RequestBuilder<ClientType, Collection<Chat>> {
    using base_t = RequestBuilder<ClientType, Collection<Chat>>;

    using base_t::baseUrl;
    using base_t::client;

public:
    explicit ChatsRequestBuilder(const ClientType* client, URL url)
        : base_t(client, std::move(url)) {}

    ChatsItemRequestBuilder<ClientType> byId(const ID& chat_id) {
        return ChatsItemRequestBuilder<ClientType>{client(),
                                                   baseUrl() + "/" + chat_id};
    }
};
}  // namespace teams::priv