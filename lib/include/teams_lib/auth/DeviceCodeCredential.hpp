#pragma once
#include <string>

namespace teams {
namespace priv {

class DeviceCodeCredential {
    using ID = std::string;

public:
    DeviceCodeCredential(ID tenant_id, ID client_id)
        : tenant_id_{std::move(tenant_id)}, client_id_{std::move(client_id)} {}

    const ID& tenant() const { return tenant_id_; }
    const ID& client() const { return client_id_; }

private:
    std::string tenant_id_;
    std::string client_id_;
};

}  // namespace priv
using DeviceCodeCredential = priv::DeviceCodeCredential;
}  // namespace teams