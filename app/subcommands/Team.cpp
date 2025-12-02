#include "Team.hpp"

#include "callbacks/Team.hpp"


namespace sub::team {
namespace ct = callbacks::team;


CLI::App* setup(CLI::App* app) {
    return app->add_subcommand("team", "Manage teams")
        ->alias("t")
        ->require_subcommand();
}

CLI::App* setupAdd(CLI::App* app) {
    const auto opt = std::make_shared<AddOptions>();
    return app->add_subcommand("add", "Add team")
        ->alias("a")
        ->callback([opt]() { ct::add(*opt); });
}

CLI::App* setupList(CLI::App* app) {
    const auto opt = std::make_shared<ListOptions>();
    return app->add_subcommand("list", "List teams")
        ->alias("ls")
        ->callback([opt]() { ct::list(*opt); });
}
}  // namespace sub::team