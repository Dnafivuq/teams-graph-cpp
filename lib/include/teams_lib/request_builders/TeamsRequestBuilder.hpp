#pragma once

#include <teams_lib/request_builders/TeamsItemRequestBuilder.hpp>

namespace teams::priv {

template <typename ClientType>
class TeamsRequestBuilder
    : public RequestBuilder<ClientType, Collection<Team>> {
    using base_t = RequestBuilder<ClientType, Collection<Team>>;

    using base_t::baseUrl;
    using base_t::client;

public:
    explicit TeamsRequestBuilder(const ClientType* client, URL url)
        : base_t(client, std::move(url)) {}

    TeamsItemRequestBuilder<ClientType> byId(const ID& team_id) {
        return TeamsItemRequestBuilder<ClientType>{
            client(), baseUrl() + "/" + team_id, std::move(team_id)};
    }

    ClientResponse<void> post(const Team& body) const noexcept {
        return client()->template post<Team, void>(baseUrl(), body);
    }
};
}  // namespace teams::priv