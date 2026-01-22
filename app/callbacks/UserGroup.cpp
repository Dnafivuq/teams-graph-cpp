#include "UserGroup.hpp"

namespace callbacks::automatization::UserGroup {

void add(sub::automatization::UserGroup::AddOptions const& options,
         teams::GraphServiceClient const& client) {}

void list(sub::automatization::UserGroup::ListOptions const& options,
          teams::GraphServiceClient const& client) {}

void show(sub::automatization::UserGroup::ShowOptions const& options,
          teams::GraphServiceClient const& client) {}

void remove(sub::automatization::UserGroup::RemoveOptions const& options,
            teams::GraphServiceClient const& client) {}

void send(sub::automatization::UserGroup::SendOptions const& options,
          teams::GraphServiceClient const& client) {
    // implementation here
}
}  // namespace callbacks::automatization::UserGroup
