#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/Chat.hpp"

namespace callbacks::chat {

void list(sub::chat::ListOptions const&, teams::GraphServiceClient const&);
void add(sub::chat::AddOptions const&, teams::GraphServiceClient const&);

}  // namespace callbacks::chat