#pragma once
#include <cstdint>
#include <string>
#include <teams_lib/common.hpp>

namespace teams {
namespace priv {
enum class GraphErrorStatus : std::uint8_t {
    // Authentication / identity
    AUTHENTICATION,  // 401

    // Authorization, licensing, policy
    AUTHORIZATION,  // 403, conditional access, insufficient claims
    LICENSING,      // 402, 507 (quota)

    // Client request errors (syntax / protocol)
    BAD_REQUEST,             // 400
    METHOD_NOT_ALLOWED,      // 405
    NOT_ACCEPTABLE,          // 406
    LENGTH_REQUIRED,         // 411
    UNSUPPORTED_MEDIA_TYPE,  // 415
    RANGE_NOT_SATISFIABLE,   // 416
    REQUEST_TOO_LARGE,       // 413

    // Semantic / business logic errors
    VALIDATION,           // 422
    CONFLICT,             // 409
    PRECONDITION_FAILED,  // 412
    LOCKED,               // 423

    // Resource lifecycle
    NOT_FOUND,  // 404
    GONE,       // 410

    // Throttling / limits (retryable)
    THROTTLING,  // 429, 509

    // Service-side failures (retryable)
    SERVICE_ERROR,    // 500, 503, 504
    NOT_IMPLEMENTED,  // 501

    // Library internal response parsing error
    PARSING,
    // Unknown
    UNKNOWN
};

struct GraphError {
    std::string message;
    HttpCode code;
    GraphErrorStatus status;
};
}  // namespace priv

using GraphErrorStatus = priv::GraphErrorStatus;
using GraphError = priv::GraphError;

}  // namespace teams
