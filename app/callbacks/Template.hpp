#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/Template.hpp"

namespace callbacks::automatization::Template {

void list(sub::automatization::Template::ListOptions const&,
          teams::GraphServiceClient&);
void add(sub::automatization::Template::AddOptions const&,
         teams::GraphServiceClient&);
void send(sub::automatization::Template::SendOptions const&,
          teams::GraphServiceClient&);
void show(sub::automatization::Template::ShowOptions const&,
          teams::GraphServiceClient&);
void del(sub::automatization::Template::DeleteOptions const&,
         teams::GraphServiceClient&);

}  // namespace callbacks::automatization::Template