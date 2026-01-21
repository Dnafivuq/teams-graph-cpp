#pragma once
#include <teams_lib/client/ClientResponse.hpp>
#include <teams_lib/request_builders/TeamsRequestBuilder.hpp>
#include <teams_lib/request_builders/UsersRequestBuilder.hpp>

namespace teams::priv {

template <typename ClientType, typename SessionManager>
class ServiceClient {
    using derived_t = ClientType;
    using base_t = ServiceClient<derived_t, SessionManager>;

public:
    explicit ServiceClient(SessionManager&& session_manager, URL base_url)
        : session_manager_{std::move(session_manager)},
          base_url_{std::move(base_url)} {}

    const URL& baseUrl() const { return base_url_; }
    const SessionManager& sessionManager() const { return session_manager_; }

    auto teams() const { return TeamsRequestBuilder<base_t>{this, "/teams"}; }
    auto me() const { return UsersItemRequestBuilder<base_t>{this, "/me"}; }
    auto users() const { return UsersRequestBuilder<base_t>{this, "/users"}; }
    auto chats() const { return ChatsRequestBuilder<base_t>{this, "/chats"}; }

    template <typename T>
    ClientResponse<T> get(const URL& url) const {
        return static_cast<const derived_t*>(this)->template getImpl<T>(url);
    }

    template <typename T, typename U>
    ClientResponse<U> post(const URL& url, const T& body) const {
        return static_cast<const derived_t*>(this)->template postImpl<T, U>(
            url, body);
    }

    template <typename T, typename U>
        requires std::is_void_v<T>
    ClientResponse<U> post(const URL& url) const {
        return static_cast<const derived_t*>(this)->template postImpl<T, U>(
            url);
    }

    template <typename T, typename U>
    ClientResponse<U> patch(const URL& url, const T& body) const {
        return static_cast<const derived_t*>(this)->template patchImpl<T, U>(
            url, body);
    }

    template <typename T, typename U>
        requires std::is_void_v<T>
    ClientResponse<U> patch(const URL& url, const T& body) const {
        return static_cast<const derived_t*>(this)->template patchImpl<T, U>(
            url, body);
    }

    template <typename T>
    ClientResponse<void> remove(const URL& url) const {
        return static_cast<const derived_t*>(this)->template removeImpl<T>(url);
    }

private:
    SessionManager session_manager_;
    URL base_url_;
};
}  // namespace teams::priv