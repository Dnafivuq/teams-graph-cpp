#pragma once
#include <string>
#include <teams_lib/common.hpp>

namespace teams {
namespace priv {

class DeviceCodeCredential {
public:
    DeviceCodeCredential(ID tenant_id, ID client_id)
        : tenant_id_{std::move(tenant_id)}, client_id_{std::move(client_id)} {}

    const ID& tenant() const { return tenant_id_; }
    const ID& client() const { return client_id_; }

private:
    ID tenant_id_;
    ID client_id_;
};

}  // namespace priv
using DeviceCodeCredential = priv::DeviceCodeCredential;
}  // namespace teams