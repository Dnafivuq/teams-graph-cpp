#pragma once

#include <stdexcept>
#include <teams_lib/client/ClientResponse.hpp>
#include <teams_lib/common.hpp>
#include <teams_lib/concepts.hpp>

namespace teams::priv {

template <typename ClientType, typename ResourceType>
class RequestBuilder {
public:
    explicit RequestBuilder(const ClientType* client, URL url)
        : base_url_{std::move(url)}, client_{client} {
        if (client_ == nullptr) {
            throw std::invalid_argument("Client cannot be nullptr.");
        }
    }

    RequestBuilder() = delete;

    const URL& baseUrl() const noexcept { return base_url_; }
    const ClientType* client() const noexcept { return client_; }

    template <typename R = ResourceType>
        requires IsPostable<R>
    ClientResponse<typename R::value_type> post(
        const R::value_type& body) const noexcept {
        return client_
            ->template post<typename R::value_type, typename R::value_type>(
                base_url_, body);
    }

    ClientResponse<ResourceType> get() const noexcept {
        return client_->template get<ResourceType>(base_url_);
    }

    template <typename R = ResourceType>
        requires IsPatchable<R>
    ClientResponse<R> patch(const R& body) const noexcept {
        return client_->template patch<R, R>(base_url_, body);
    }

    template <typename R = ResourceType>
        requires IsRemovable<R>
    ClientResponse<void> remove() const noexcept {
        return client_->template remove<R>(base_url_);
    }

private:
    URL base_url_;
    const ClientType* client_;
};
}  // namespace teams::priv
