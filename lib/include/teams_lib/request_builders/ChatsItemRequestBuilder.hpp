#pragma once

#include <teams_lib/models/Chat.hpp>
#include <teams_lib/request_builders/ConversationMembersRequestBuilder.hpp>
#include <teams_lib/request_builders/MessagesRequestBuilder.hpp>

namespace teams::priv {

template <typename ClientType>
class ChatsItemRequestBuilder : public RequestBuilder<ClientType, Chat> {
    using base_t = RequestBuilder<ClientType, Chat>;

    using base_t::baseUrl;
    using base_t::client;

public:
    explicit ChatsItemRequestBuilder(const ClientType* client, URL base_url)
        : base_t{client, std::move(base_url)} {}

    MessagesRequestBuilder<ClientType> messages() {
        return MessagesRequestBuilder<ClientType>{client(),
                                                  baseUrl() + "/messages"};
    }

    ConversationMembersRequestBuilder<ClientType> members() {
        return ConversationMembersRequestBuilder<ClientType>{
            client(), baseUrl() + "/members"};
    }
};
}  // namespace teams::priv