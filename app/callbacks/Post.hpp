#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/Post.hpp"

namespace callbacks::post {

void list(sub::post::ListOptions const&, teams::GraphServiceClient&);
void add(sub::post::AddOptions const&, teams::GraphServiceClient&);

}  // namespace callbacks::post