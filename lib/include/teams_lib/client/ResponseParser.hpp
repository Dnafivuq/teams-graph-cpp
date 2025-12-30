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

        return parseContent<ResourceType>(response.status, response.body);
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

        if (response.status < HTTP_SUCCESS || response.status >= HTTP_FAILURE) {
            return ClientError{parseGraphError(response.status, response.body)};
        }

        return std::nullopt;
    }

    static constexpr TransportError parseTransportError(
        const HttpError& error) {
        return TransportError{.code = error,
                              .message = httplib::to_string(error)};
    }

    static GraphError parseGraphError(const HttpCode& code,
                                      const HttpBody& body) noexcept {
        GraphError err;
        err.code = code;
        err.status = map(code);

        // parse without exceptions
        const auto json = nlohmann::json::parse(body, nullptr, false);
        if (!json.is_discarded()) {
            if (json.contains("error")) {
                const auto& error_json = json.at("error");
                err.message =
                    error_json.value("message", "Unknown Graph error");
            } else {
                err.message = "Missing Graph error payload";
            }
        } else {
            err.message = std::string("Failed to parse error response") + body;
        }
        return err;
    }

    template <typename T>
    static constexpr ClientResponse<T> parseContent(
        const HttpCode& code, const HttpBody& body) noexcept {
        try {
            const auto json = nlohmann::json::parse(body);
            std::cout << json.dump(4) << "\n";
            return deserializeJSON<T>(json);
        } catch (const nlohmann::json::exception& e) {
            return std::unexpected(
                GraphError{.message = std::string{"JSON error: "} + e.what(),
                           .code = code,
                           .status = GraphErrorStatus::PARSING});
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

    static constexpr GraphErrorStatus map(HttpCode code) noexcept {
        switch (code) {
            case 400:  // NOLINT
                return GraphErrorStatus::BAD_REQUEST;
            case 401:  // NOLINT
                return GraphErrorStatus::AUTHENTICATION;
            case 402:  // NOLINT
                return GraphErrorStatus::LICENSING;
            case 403:  // NOLINT
                return GraphErrorStatus::AUTHORIZATION;
            case 404:  // NOLINT
                return GraphErrorStatus::NOT_FOUND;
            case 405:  // NOLINT
                return GraphErrorStatus::METHOD_NOT_ALLOWED;
            case 406:  // NOLINT
                return GraphErrorStatus::NOT_ACCEPTABLE;
            case 409:  // NOLINT
                return GraphErrorStatus::CONFLICT;
            case 410:  // NOLINT
                return GraphErrorStatus::GONE;
            case 411:  // NOLINT
                return GraphErrorStatus::LENGTH_REQUIRED;
            case 412:  // NOLINT
                return GraphErrorStatus::PRECONDITION_FAILED;
            case 413:  // NOLINT
                return GraphErrorStatus::REQUEST_TOO_LARGE;
            case 415:  // NOLINT
                return GraphErrorStatus::UNSUPPORTED_MEDIA_TYPE;
            case 416:  // NOLINT
                return GraphErrorStatus::RANGE_NOT_SATISFIABLE;
            case 422:  // NOLINT
                return GraphErrorStatus::VALIDATION;
            case 423:  // NOLINT
                return GraphErrorStatus::LOCKED;
            case 429:  // NOLINT
                return GraphErrorStatus::THROTTLING;

            case 500:  // NOLINT
                return GraphErrorStatus::SERVICE_ERROR;
            case 501:  // NOLINT
                return GraphErrorStatus::NOT_IMPLEMENTED;
            case 503:  // NOLINT
                return GraphErrorStatus::SERVICE_ERROR;
            case 504:  // NOLINT
                return GraphErrorStatus::SERVICE_ERROR;
            case 507:  // NOLINT
                return GraphErrorStatus::LICENSING;
            case 509:  // NOLINT
                return GraphErrorStatus::THROTTLING;

            default:
                return GraphErrorStatus::UNKNOWN;
        }
    }
};
}  // namespace teams::priv
