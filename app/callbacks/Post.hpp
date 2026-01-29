#pragma once
#include <string>
#include <teams_lib/client/GraphServiceClient.hpp>

#include "subcommands/Post.hpp"

namespace callbacks::post {

void sendMessage(std::string channel_id, std::string team_id,
                 const std::string& text,
                 teams::GraphServiceClient const& client);

void list(sub::post::ListOptions const&, teams::GraphServiceClient const&);
void add(sub::post::AddOptions const&, teams::GraphServiceClient const&);

}  // namespace callbacks::post
