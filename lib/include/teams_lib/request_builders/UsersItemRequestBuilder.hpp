#pragma once

#include <teams_lib/models/User.hpp>
#include <teams_lib/request_builders/ChatsRequestBuilder.hpp>

namespace teams::priv {

template <typename ClientType>
class UsersItemRequestBuilder : public RequestBuilder<ClientType, User> {
    using base_t = RequestBuilder<ClientType, User>;

    using base_t::baseUrl;
    using base_t::client;

public:
    explicit UsersItemRequestBuilder(const ClientType* client, URL base_url)
        : base_t{client, std::move(base_url)} {}
    
    ChatsRequestBuilder<ClientType> chats() {
        return ChatsRequestBuilder<ClientType>{client(),
                                                  baseUrl() + "/chats"};
    }
};
}  // namespace teams::priv