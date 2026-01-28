#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace teams {
namespace priv {

struct Channel {
    std::optional<std::string> id;
    std::optional<std::string> display_name;
    std::optional<std::string> description;
    std::optional<std::string> membership_type;
};

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const Channel& channel);
void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, Channel& channel);

}  // namespace priv
using Channel = priv::Channel;
}  // namespace teams
