#pragma once
#include "subcommands/Team.hpp"

namespace callbacks::team {
void list(sub::team::ListOptions const&, teams::GraphServiceClient&);
void add(sub::team::AddOptions const&, teams::GraphServiceClient&);

}  // namespace callbacks::team