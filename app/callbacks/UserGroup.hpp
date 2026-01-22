#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/UserGroup.hpp"

namespace callbacks::automatization::UserGroup {

void list(sub::automatization::UserGroup::ListOptions const&,
          teams::GraphServiceClient const&);
void add(sub::automatization::UserGroup::AddOptions const&,
         teams::GraphServiceClient const&);
void send(sub::automatization::UserGroup::SendOptions const&,
          teams::GraphServiceClient const&);
void remove(sub::automatization::UserGroup::RemoveOptions const&,
            teams::GraphServiceClient const&);
void show(sub::automatization::UserGroup::ShowOptions const&,
          teams::GraphServiceClient const&);

}  // namespace callbacks::automatization::UserGroup