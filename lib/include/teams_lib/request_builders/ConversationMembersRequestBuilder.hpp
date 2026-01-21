#pragma once

#include <teams_lib/request_builders/RequestBuilder.hpp>

#include "teams_lib/models/ConversationMember.hpp"

namespace teams::priv {

template <typename ClientType>
class ConversationMembersRequestBuilder
    : public RequestBuilder<ClientType, Collection<ConversationMember>> {
    using base_t = RequestBuilder<ClientType, Collection<ConversationMember>>;

    using base_t::baseUrl;
    using base_t::client;

public:
    explicit ConversationMembersRequestBuilder(const ClientType* client,
                                               URL url)
        : base_t(client, std::move(url)) {}

    ClientResponse<ConversationMember> post(const ConversationMember& body) const noexcept {
        return client()->template post<ConversationMember, ConversationMember>(
            baseUrl(), body);
    }

    ClientResponse<void> remove(const ConversationMember& body) const noexcept {
        return client()
            ->template remove<void>(
                baseUrl() + "/" + body.membership_id.value());
    }
};
}  // namespace teams::priv