#include "CLI/CLI.hpp"
#include "subcommands/Team.hpp"
#include "teams_lib/Test.h"

// Based on the example here but in classes
// https://github.com/CLIUtils/CLI11/tree/main/examples/subcom_in_files

int main(int argc, char** argv) {
    CLI::App app{"CLI for Microsoft Teams", "Teams CLI"};
    app.require_subcommand();
    argv = app.ensure_utf8(argv);

    auto* sub_team = sub::team::setup(&app);
    auto* sub_team_list = sub::team::setupList(sub_team);
    auto* sub_team_add = sub::team::setupAdd(sub_team);

    CLI11_PARSE(app, argc, argv);

    return 0;
}
