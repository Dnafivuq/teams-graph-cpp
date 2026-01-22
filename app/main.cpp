#include <CLI/CLI.hpp>

#include "LazyGraphClient.h"
#include "subcommands/Channel.hpp"
#include "subcommands/Member.hpp"
#include "subcommands/Post.hpp"
#include "subcommands/Team.hpp"
#include "subcommands/Chat.hpp"


// Based on the example here but in classes
// https://github.com/CLIUtils/CLI11/tree/main/examples/subcom_in_files

int main(int argc, char** argv) {
    CLI::App app{"CLI for Microsoft Teams", "teams_cli"};
    // app.require_subcommand();
    app.set_config("--config");
    argv = app.ensure_utf8(argv);

    auto credentials =
        // teams::DeviceCodeCredential{"cbcda674-1840-429c-88af-b400689789d6",
        //                             "e3f095a1-d977-400f-943d-f82bcc743564"};
        teams::DeviceCodeCredential{"078cf7f9-6a56-48fe-afa7-39582cbda561",
                                    "c573277f-2096-455c-b284-13a31ec76252"};

    auto scopes = teams::Scopes{
        "offline_access user.read team.readbasic.all group.readwrite.all"};

    auto client = LazyGraphClient{credentials, scopes};

    auto* sub_team = sub::team::setup(&app);
    auto* sub_team_add = sub::team::setupAdd(sub_team, client);
    auto* sub_team_list = sub::team::setupList(sub_team, client);
    auto* sub_team_remove = sub::team::setupRemove(sub_team, client);

    auto* sub_channel = sub::channel::setup(&app);
    auto* sub_channel_add = sub::channel::setupAdd(sub_channel, client);
    auto* sub_channel_list = sub::channel::setupList(sub_channel, client);
    auto* sub_channel_remove = sub::channel::setupRemove(sub_channel, client);

    auto* sub_member = sub::member::setup(&app);
    auto* sub_member_add = sub::member::setupAdd(sub_member, client);
    auto* sub_member_list = sub::member::setupList(sub_member, client);
    auto* sub_member_remove = sub::member::setupRemove(sub_member, client);

    auto* sub_chat = sub::chat::setup(&app);
    auto* sub_chat_add = sub::chat::setupAdd(sub_chat, client);
    auto* sub_chat_list = sub::chat::setupList(sub_chat, client);

    auto* sub_post = sub::post::setup(&app);
    auto* sub_post_add = sub::post::setupAdd(sub_post, client);
    auto* sub_post_list = sub::post::setupList(sub_post, client);

    CLI11_PARSE(app, argc, argv);
}