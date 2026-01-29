#pragma once

#include <teams_lib/request_builders/MessagesItemRequestBuilder.hpp>
namespace teams::priv {

template <typename ClientType>
class MessagesRequestBuilder
    : public RequestBuilder<ClientType, Collection<Message>> {
    using base_t = RequestBuilder<ClientType, Collection<Message>>;

    using base_t::baseUrl;
    using base_t::client;

public:
    explicit MessagesRequestBuilder(const ClientType* client, URL url)
        : base_t(client, std::move(url)) {}

    MessagesItemRequestBuilder<ClientType> byId(const ID& message_id) {
        return MessagesItemRequestBuilder<ClientType>{
            client(), baseUrl() + "/" + message_id};
    }
};
}  // namespace teams::priv
