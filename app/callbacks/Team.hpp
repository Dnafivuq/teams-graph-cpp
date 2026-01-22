#pragma once
#include "subcommands/Team.hpp"
#include "teams_lib/client/GraphServiceClient.hpp"

namespace callbacks::team {
void list(sub::team::ListOptions const&, teams::GraphServiceClient const&);
void add(sub::team::AddOptions const&, teams::GraphServiceClient const&);
void remove(sub::team::RemoveOptions const&, teams::GraphServiceClient const&);

}  // namespace callbacks::team