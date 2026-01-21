#include "UserGroup.hpp"

namespace callbacks::automatization::UserGroup {

void add(sub::automatization::UserGroup::AddOptions const& options,
         teams::GraphServiceClient& client) {}

void list(sub::automatization::UserGroup::ListOptions const& options,
          teams::GraphServiceClient& client) {}

void show(sub::automatization::UserGroup::ShowOptions const& options,
          teams::GraphServiceClient& client) {}

void del(sub::automatization::UserGroup::DeleteOptions const& options,
         teams::GraphServiceClient& client) {}

void send(sub::automatization::UserGroup::SendOptions const& options,
          teams::GraphServiceClient& client) {
    // implementation here
}
}  // namespace callbacks::automatization::UserGroup
