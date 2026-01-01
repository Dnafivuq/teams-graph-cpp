#pragma once

#include <httplib.h>

#include <nlohmann/json.hpp>
#include <teams_lib/auth/DeviceCodeCredential.hpp>
#include <teams_lib/auth/DeviceTokenProvider.hpp>
#include <teams_lib/auth/PlainTextTokenStorage.hpp>
#include <teams_lib/auth/SessionManager.hpp>
#include <teams_lib/client/ResponseParser.hpp>
#include <teams_lib/client/ServiceClient.hpp>
#include <teams_lib/common.hpp>

namespace teams {
namespace priv {
// TODO: change optional to expected and add error codes
template <typename TokenProvider, typename StorageProvider>
class GraphServiceClient
    : public ServiceClient<GraphServiceClient<TokenProvider, StorageProvider>,
                           SessionManager<TokenProvider, StorageProvider>> {
    using provider_t = TokenProvider;
    using storage_t = StorageProvider;

    using manager_t = SessionManager<provider_t, storage_t>;

    using base_t =
        ServiceClient<GraphServiceClient<provider_t, storage_t>, manager_t>;

    using base_t::baseUrl;
    using base_t::sessionManager;

    friend base_t;

public:
    explicit GraphServiceClient(manager_t&& session_manager)
        : base_t{std::move(session_manager), "https://graph.microsoft.com"},
          client_{baseUrl()} {
        sessionManager().authorizeClient(client_);
    }

    GraphServiceClient(TokenProvider&& provider, StorageProvider&& storage)
        : base_t{manager_t{std::move(provider), std::move(storage)},
                 "https://graph.microsoft.com"},
          client_{baseUrl()} {
        sessionManager().authorizeClient(client_);
    }

    template <typename... StorageProviderArgs>
        requires std::constructible_from<TokenProvider, DeviceCodeCredential,
                                         Scopes> &&
                     std::constructible_from<StorageProvider,
                                             StorageProviderArgs...>
    GraphServiceClient(DeviceCodeCredential credentials,
                       Scopes scopes = "https://graph.microsoft.com/.default",
                       StorageProviderArgs&... args)
        : base_t{{TokenProvider{std::move(credentials), std::move(scopes)},
                  StorageProvider{std::forward<StorageProviderArgs>(args)...}},
                 "https://graph.microsoft.com"},
          client_{baseUrl()} {
        sessionManager().authorizeClient(client_);
    }

private:
    template <typename T>
    ClientResponse<T> getImpl(const URL& url) const {
        const auto path = URL{"/v1.0" + url};

        const auto result = client_.Get(path);

        return ResponseParser::parse<T>(result);
    }

    template <typename T, typename U>
    ClientResponse<U> postImpl(const URL& url, const T& body) const {
        const auto path = URL{"/v1.0" + url};
        const auto header =
            httplib::Headers{{"Content-Type", "application/json"}};
        const auto json = nlohmann::json(body);
        // std::cout << json.dump(2) << "\n";
        const auto result =
            client_.Post(path, header, json.dump(), "application/json");

        return ResponseParser::parse<U>(result);
    }

    template <typename T, typename U>
        requires std::is_void_v<T>
    ClientResponse<U> postImpl(const URL& url) const {
        const auto path = URL{"/v1.0" + url};
        const auto result = client_.Post(path);

        return ResponseParser::parse<U>(result);
    }

    template <typename T, typename U>
    ClientResponse<U> patchImpl(const URL& url, const T& body) const {
        const auto path = URL{"/v1.0" + url};
        const auto header =
            httplib::Headers{{"Content-Type", "application/json"}};
        const auto json = nlohmann::json(body);

        const auto result =
            client_.Patch(path, header, json.dump(), "application/json");

        return ResponseParser::parse<U>(result);
    }

    template <typename T>
        requires IsRemovable<T>
    ClientResponse<void> removeImpl(const URL& url) const {
        const auto path = URL{"/v1.0" + url};

        const auto result = client_.Delete(path);
        return ResponseParser::parse<void>(result);
    }

    mutable httplib::Client client_;
};
}  // namespace priv
using GraphServiceClient =
    priv::GraphServiceClient<DeviceTokenProvider, PlainTextTokenStorage>;
}  // namespace teams
