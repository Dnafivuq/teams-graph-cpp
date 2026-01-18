#include <CLI/CLI.hpp>

#include "subcommands/Channel.hpp"
#include "subcommands/Post.hpp"
#include "subcommands/Team.hpp"

// Based on the example here but in classes
// https://github.com/CLIUtils/CLI11/tree/main/examples/subcom_in_files

int main(int argc, char** argv) {
    CLI::App app{"CLI for Microsoft Teams", "teams_cli"};
    app.require_subcommand();
    argv = app.ensure_utf8(argv);

    auto credentials =
        teams::DeviceCodeCredential{"cbcda674-1840-429c-88af-b400689789d6",
                                    "e3f095a1-d977-400f-943d-f82bcc743564"};

    auto scopes = teams::Scopes{"offline_access user.read team.readbasic.all"};

    auto client = teams::GraphServiceClient{credentials, scopes};

    auto* sub_team = sub::team::setup(&app);
    auto* sub_team_list = sub::team::setupList(sub_team, client);
    auto* sub_team_add = sub::team::setupAdd(sub_team, client);

    auto* sub_channel = sub::channel::setup(&app);
    auto* sub_channel_list = sub::channel::setupList(sub_channel, client);

    auto* sub_post = sub::post::setup(&app);
    auto* sub_post_add = sub::post::setupAdd(sub_post, client);

    CLI11_PARSE(app, argc, argv);
}