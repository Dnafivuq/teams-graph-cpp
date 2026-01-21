#pragma once

#include <teams_lib/request_builders/UsersItemRequestBuilder.hpp>

namespace teams::priv {

template <typename ClientType>
class UsersRequestBuilder
    : public RequestBuilder<ClientType, Collection<User>> {
    using base_t = RequestBuilder<ClientType, Collection<User>>;

    using base_t::baseUrl;
    using base_t::client;

public:
    explicit UsersRequestBuilder(const ClientType* client, URL url)
        : base_t(client, std::move(url)) {}

    UsersItemRequestBuilder<ClientType> byId(const ID& user_id) {
        return UsersItemRequestBuilder<ClientType>{client(),
                                                  baseUrl() + "/" + user_id};
    }
    UsersItemRequestBuilder<ClientType> byEmail(const std::string& user_email) {
        return UsersItemRequestBuilder<ClientType>{client(),
                                                  baseUrl() + "/" + user_email};
    }
};
}  // namespace teams::priv