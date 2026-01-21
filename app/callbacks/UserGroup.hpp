#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/UserGroup.hpp"

namespace callbacks::automatization::UserGroup {

void list(sub::automatization::UserGroup::ListOptions const&,
          teams::GraphServiceClient&);
void add(sub::automatization::UserGroup::AddOptions const&,
         teams::GraphServiceClient&);
void send(sub::automatization::UserGroup::SendOptions const&,
          teams::GraphServiceClient&);
void del(sub::automatization::UserGroup::DeleteOptions const&,
         teams::GraphServiceClient&);
void show(sub::automatization::UserGroup::ShowOptions const&,
          teams::GraphServiceClient&);

}  // namespace callbacks::automatization::UserGroup