#include "Template.hpp"

namespace callbacks::automatization::Template {

void add(sub::automatization::Template::AddOptions const& options,
         teams::GraphServiceClient const& client) {}

void list(sub::automatization::Template::ListOptions const& options,
          teams::GraphServiceClient const& client) {}

void show(sub::automatization::Template::ShowOptions const& options,
          teams::GraphServiceClient const& client) {}

void remove(sub::automatization::Template::RemoveOptions const& options,
            teams::GraphServiceClient const& client) {}

void send(sub::automatization::Template::SendOptions const& options,
          teams::GraphServiceClient const& client) {
    // implementation here
}
}  // namespace callbacks::automatization::Template
