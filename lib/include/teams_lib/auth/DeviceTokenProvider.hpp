#pragma once

#include <httplib.h>

#include <nlohmann/json.hpp>
#include <optional>
#include <teams_lib/auth/TokenProvider.hpp>

namespace teams {
namespace priv {

class DeviceTokenProvider : public TokenProvider<DeviceTokenProvider> {
    friend TokenProvider;

public:
    DeviceTokenProvider(DeviceCodeCredential device_code_credential,
                        Scopes scopes = "https://graph.microsoft.com/.default")
        : TokenProvider{std::move(device_code_credential), std::move(scopes)} {}

private:
    std::optional<Tokens> acquireImpl() const {
        httplib::Client cli("https://login.microsoftonline.com");

        const auto device_code_path = std::string("/" + credentials().tenant() +
                                                  "/oauth2/v2.0/devicecode");

        const auto device_params = httplib::Params{
            {"client_id", credentials().client()}, {"scope", scopes()}};

        const auto device_res = cli.Post(device_code_path, device_params);

        // TODO: add better error handling
        if (!device_res) {
            return std::nullopt;
        }

        const auto device_code_resp = nlohmann::json::parse(device_res->body);

        const auto message = device_code_resp["message"].get<std::string>();
        const auto device_code =
            device_code_resp["device_code"].get<std::string>();
        const auto interval = device_code_resp["interval"].get<int>();

        // Print out auth message
        std::cout << message << "\n\n";

        const auto token_path =
            std::string("/" + credentials().tenant() + "/oauth2/v2.0/token");

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(interval));
            const httplib::Params token_params = {
                {"grant_type", "device_code"},
                {"client_id", credentials().client()},
                {"device_code", device_code}};

            const auto token_res = cli.Post(token_path, token_params);

            // TODO: Add checking if url is ok
            if (!token_res) {
                continue;
            }

            const auto token_json = nlohmann::json::parse(token_res->body);

            if (token_json.contains("error")) {
                continue;
            }

            return Tokens{
                .access_token = token_json["access_token"].get<Token>(),
                .refresh_token = token_json["refresh_token"].get<Token>()};
        }
    }

    std::optional<Tokens> acquireSilentlyImpl(const RefreshToken& token) const {
        httplib::Client cli("https://login.microsoftonline.com");

        const auto refresh_path =
            std::string("/" + credentials().tenant() + "/oauth2/v2.0/token");
        const auto refresh_header = httplib::Headers{
            {"Content-Type", "application/x-www-form-urlencoded"}};

        const auto refresh_params =
            httplib::Params{{"client_id", credentials().client()},
                            {"scope", scopes()},
                            {"refresh_token", token},
                            {"grant_type", "refresh_token"}};

        const auto refresh_res =
            cli.Post(refresh_path, refresh_header, refresh_params);

        // TODO: add better error handling
        if (!refresh_res) {
            return std::nullopt;
        }

        const auto refresh_resp = nlohmann::json::parse(refresh_res->body);
        // TODO: add error
        if (!refresh_resp.contains("access_token")) {
            return std::nullopt;
        }

        auto tokens = Tokens{
            .access_token = refresh_resp["access_token"].get<AccessToken>()};

        if (refresh_resp.contains("refresh_token")) {
            tokens.refresh_token =
                refresh_resp["refresh_token"].get<RefreshToken>();
        }
        return tokens;
    }
};
}  // namespace priv
using DeviceTokenProvider = priv::DeviceTokenProvider;
}  // namespace teams
