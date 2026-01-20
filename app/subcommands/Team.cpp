#include "Team.hpp"

#include "callbacks/Team.hpp"

namespace sub::team {
namespace ct = callbacks::team;

CLI::App* setup(CLI::App* app) {
    return app->add_subcommand("team", "Manage teams")->require_subcommand();
}

CLI::App* setupAdd(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<AddOptions>();
    return app->add_subcommand("add", "Add teams")
        ->alias("a")
        ->callback([opt, &client]() { ct::add(*opt, *client); });
}

CLI::App* setupList(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<ListOptions>();
    return app->add_subcommand("list", "List teams")
        ->alias("ls")
        ->callback([opt, &client]() { ct::list(*opt, *client); });
}
}  // namespace sub::team