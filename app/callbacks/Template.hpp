#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/Template.hpp"

namespace callbacks::automatization::Template {

void list(sub::automatization::Template::ListOptions const&);
void add(sub::automatization::Template::AddOptions const&);
void send(sub::automatization::Template::SendOptions const&,
          teams::GraphServiceClient const&);
void show(sub::automatization::Template::ShowOptions const&);
void remove(sub::automatization::Template::RemoveOptions const&);

}  // namespace callbacks::automatization::Template
