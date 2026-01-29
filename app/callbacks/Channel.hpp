#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/Channel.hpp"

namespace callbacks::channel {

void list(sub::channel::ListOptions const&, teams::GraphServiceClient const&);
void add(sub::channel::AddOptions const&, teams::GraphServiceClient const&);
void remove(sub::channel::RemoveOptions const&,
            teams::GraphServiceClient const&);

}  // namespace callbacks::channel
