#pragma once
#include "subcommands/Team.hpp"

namespace callbacks::team {
void list(sub::team::ListOptions const&);
void add(sub::team::AddOptions const&);

}  // namespace callbacks::team