#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/Channel.hpp"

namespace callbacks::channel {

void list(sub::channel::ListOptions const&, teams::GraphServiceClient&);
void add(sub::channel::AddOptions const&, teams::GraphServiceClient&);

}  // namespace callbacks::channel