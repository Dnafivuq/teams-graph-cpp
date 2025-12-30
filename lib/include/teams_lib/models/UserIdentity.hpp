#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <teams_lib/common.hpp>

namespace teams::priv {

struct UserIdentity {
    std::string display_name;
    ID id;
};

void to_json(  // NOLINT(readability-identifier-naming)
    nlohmann::json& json, const UserIdentity& user);
void from_json(  // NOLINT(readability-identifier-naming)
    const nlohmann::json& json, UserIdentity& user);

}  // namespace teams::priv
