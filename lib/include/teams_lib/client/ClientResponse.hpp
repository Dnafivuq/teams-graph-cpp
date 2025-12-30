#pragma once
#include <expected>
#include <teams_lib/client/GraphError.hpp>
#include <teams_lib/common.hpp>
#include <variant>

namespace teams {
namespace priv {

struct TransportError {
    HttpError code;
    std::string message;
};

using ClientError = std::variant<TransportError, GraphError>;

template <typename Resource>
using ClientResponse = std::expected<Resource, ClientError>;

}  // namespace priv

using TransportError = priv::TransportError;

template <typename Resource>
using ClientResponse = priv::ClientResponse<Resource>;

}  // namespace teams
