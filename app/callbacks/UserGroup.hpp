#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/UserGroup.hpp"

namespace callbacks::automatization::UserGroup {

void list(sub::automatization::UserGroup::ListOptions const&);
void add(sub::automatization::UserGroup::AddOptions const&);
void send(sub::automatization::UserGroup::SendOptions const&,
          teams::GraphServiceClient const&);
void remove(sub::automatization::UserGroup::RemoveOptions const&);
void show(sub::automatization::UserGroup::ShowOptions const&);

}  // namespace callbacks::automatization::UserGroup