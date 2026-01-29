#pragma once

#include <optional>
#include <teams_lib/client/GraphServiceClient.hpp>

class LazyGraphClient {
public:
    LazyGraphClient(teams::DeviceCodeCredential creds, teams::Scopes scopes)
        : credentials_(std::move(creds)), scopes_(std::move(scopes)) {}

    teams::GraphServiceClient const& get() {
        if (!client_) {
            client_.emplace(credentials_, scopes_);
        }
        return *client_;
    }
    teams::GraphServiceClient const& operator*() { return get(); }

    teams::GraphServiceClient const* operator->() { return &get(); }

private:
    teams::DeviceCodeCredential credentials_;
    teams::Scopes scopes_;
    std::optional<teams::GraphServiceClient> client_;
};
