#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/Post.hpp"

namespace callbacks::post {

void list(sub::post::ListOptions const&, teams::GraphServiceClient const&);
void add(sub::post::AddOptions const&, teams::GraphServiceClient const&);

}  // namespace callbacks::post