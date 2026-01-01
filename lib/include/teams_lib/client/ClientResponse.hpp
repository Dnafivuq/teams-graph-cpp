#pragma once
#include <expected>
#include <teams_lib/common.hpp>
#include <variant>

namespace teams {
namespace priv {

struct TransportError {
    HttpError code;
    std::string message;
};

struct ParsingError {
    std::string message;
};

struct GraphError {
    HttpStatus status;
    std::string message;
};

using ClientError = std::variant<TransportError, ParsingError, GraphError>;

template <typename Resource>
using ClientResponse = std::expected<Resource, ClientError>;

}  // namespace priv

using TransportError = priv::TransportError;
using ParsingError = priv::ParsingError;
using GraphError = priv::GraphError;

template <typename Resource>
using ClientResponse = priv::ClientResponse<Resource>;

}  // namespace teams
