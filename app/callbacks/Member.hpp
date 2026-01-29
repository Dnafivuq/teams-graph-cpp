#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/Member.hpp"

namespace callbacks::member {

void list(sub::member::ListOptions const&, teams::GraphServiceClient const&);
void add(sub::member::AddOptions const&, teams::GraphServiceClient const&);
void remove(sub::member::RemoveOptions const&,
            teams::GraphServiceClient const&);

}  // namespace callbacks::member
