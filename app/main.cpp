#include <CLI/CLI.hpp>

#include "subcommands/Channel.hpp"
#include "subcommands/Post.hpp"
#include "subcommands/Team.hpp"
#include "subcommands/UserGroup.hpp"

// Based on the example here but in classes
// https://github.com/CLIUtils/CLI11/tree/main/examples/subcom_in_files

int main(int argc, char** argv) {
    CLI::App app{"CLI for Microsoft Teams", "teams_cli"};
    app.require_subcommand();
    argv = app.ensure_utf8(argv);

    auto credentials =
        teams::DeviceCodeCredential{"078cf7f9-6a56-48fe-afa7-39582cbda561",
                                    "c573277f-2096-455c-b284-13a31ec76252"};

    auto scopes = teams::Scopes{"offline_access user.read team.readbasic.all"};

    auto client = teams::GraphServiceClient{credentials, scopes};

    auto* sub_team = sub::team::setup(&app);
    auto* sub_team_list = sub::team::setupList(sub_team, client);
    auto* sub_team_login = sub::team::setupAdd(sub_team, client);

    auto* sub_channel = sub::channel::setup(&app);
    auto* sub_channel_list = sub::channel::setupList(sub_channel, client);

    auto* sub_post = sub::post::setup(&app);
    auto* sub_post_list = sub::post::setupAdd(sub_post, client);

    auto* sub_auto_user_group = sub::automatization::UserGroup::setup(&app);
    auto* sub_auto_user_group_add =
        sub::automatization::UserGroup::setupAdd(sub_auto_user_group, client);
    auto* sub_auto_user_group_delete =
        sub::automatization::UserGroup::setupDelete(sub_auto_user_group,
                                                    client);
    auto* sub_auto_user_group_show =
        sub::automatization::UserGroup::setupShow(sub_auto_user_group, client);
    auto* sub_auto_user_group_list =
        sub::automatization::UserGroup::setupList(sub_auto_user_group, client);
    auto* sub_auto_user_group_send =
        sub::automatization::UserGroup::setupSend(sub_auto_user_group, client);

    CLI11_PARSE(app, argc, argv);
}