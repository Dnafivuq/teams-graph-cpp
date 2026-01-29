#pragma once

#include <teams_lib/models/Message.hpp>
#include <teams_lib/request_builders/RequestBuilder.hpp>

namespace teams::priv {

template <typename ClientType>
class MessagesItemRequestBuilder : public RequestBuilder<ClientType, Message> {
    using base_t = RequestBuilder<ClientType, Message>;
    using base_t::baseUrl;
    using base_t::client;

public:
    explicit MessagesItemRequestBuilder(const ClientType* client,
                                        URL base_url) noexcept
        : base_t{client, std::move(base_url)} {}

    ClientResponse<void> remove() const noexcept {
        return client()->template post<void, void>({baseUrl() + "/softDelete"});
    }
    ClientResponse<void> undoRemove() const noexcept {
        return client()->template post<void, void>(
            {baseUrl() + "/undoSoftDelete"});
    }
};
}  // namespace teams::priv
