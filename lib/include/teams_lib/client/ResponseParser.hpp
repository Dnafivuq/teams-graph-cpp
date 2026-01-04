#pragma once
#include <httplib.h>

#include <nlohmann/json.hpp>
#include <teams_lib/client/ClientResponse.hpp>
#include <teams_lib/common.hpp>
#include <teams_lib/concepts.hpp>

namespace teams::priv {

class ResponseParser {
public:
    template <typename ResourceType>
    static constexpr ClientResponse<ResourceType> parse(
        const HttpResult& result) noexcept {
        const auto client_error = checkForClientError(result);
        if (client_error) {
            return std::unexpected(client_error.value());
        }

        const auto& response = *result;

        return parseContent<ResourceType>(response);
    }

    template <typename ResourceType>
        requires std::is_void_v<ResourceType>
    static constexpr ClientResponse<ResourceType> parse(
        const HttpResult& result) noexcept {
        const auto client_error = checkForClientError(result);
        if (client_error) {
            return std::unexpected(client_error.value());
        }
        return {};
    }

private:
    static std::optional<ClientError> checkForClientError(
        const HttpResult& result) noexcept {
        if (!result) {
            return ClientError{parseTransportError(result.error())};
        }
        const auto& response = *result;

        if (response.status < HttpStatus::OK_200 ||
            response.status >= HttpStatus::BadRequest_400) {
            return ClientError{parseGraphError(response)};
        }

        return std::nullopt;
    }

    static constexpr TransportError parseTransportError(
        const HttpError& error) {
        return TransportError{.code = error,
                              .message = httplib::to_string(error)};
    }

    static GraphError parseGraphError(const HttpResponse& response) noexcept {
        GraphError err;
        err.status = static_cast<HttpStatus>(response.status);

        // parse without exceptions
        const auto json = nlohmann::json::parse(response.body, nullptr, false);
        if (!json.is_discarded()) {
            if (json.contains("error")) {
                const auto& error_json = json.at("error");
                err.message =
                    error_json.value("message", "Unknown Graph error");
            } else {
                err.message = "Missing Graph error payload";
            }
        } else {
            err.message =
                std::string("Unable to parse error payload:\n") + response.body;
        }
        return err;
    }

    template <typename T>
    static constexpr ClientResponse<T> parseContent(
        const HttpResponse& response) noexcept {
        try {
            const auto json = nlohmann::json::parse(response.body);
            return deserializeJSON<T>(json);
        } catch (const nlohmann::json::exception& e) {
            return std::unexpected(
                ParsingError{.message = std::string{e.what()}});
        }
    }

    template <typename T>
    static constexpr T deserializeJSON(const nlohmann::json& json) {
        return json.template get<T>();
    }

    template <typename T>
        requires IsCollection<T>
    static constexpr T deserializeJSON(const nlohmann::json& json) {
        return json.at("value").template get<T>();
    }
};
}  // namespace teams::priv
