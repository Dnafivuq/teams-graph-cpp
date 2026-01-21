#include "Template.hpp"

namespace callbacks::automatization::Template {

void add(sub::automatization::Template::AddOptions const& options,
         teams::GraphServiceClient& client) {}

void list(sub::automatization::Template::ListOptions const& options,
          teams::GraphServiceClient& client) {}

void show(sub::automatization::Template::ShowOptions const& options,
          teams::GraphServiceClient& client) {}

void del(sub::automatization::Template::DeleteOptions const& options,
         teams::GraphServiceClient& client) {}

void send(sub::automatization::Template::SendOptions const& options,
          teams::GraphServiceClient& client) {
    // implementation here
}
}  // namespace callbacks::automatization::Template
