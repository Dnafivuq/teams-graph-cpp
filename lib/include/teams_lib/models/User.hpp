#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace teams {
namespace priv {

struct User {
    std::optional<std::string> id;
    std::optional<std::string> display_name;
    std::optional<std::string> email;
};

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const User& user);
void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, User& user);

}  // namespace priv
using User = priv::User;
}  // namespace teams