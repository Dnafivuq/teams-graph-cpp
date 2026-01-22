#include "UserGroup.hpp"

#include "callbacks/UserGroup.hpp"

namespace sub::automatization::UserGroup {
namespace caUG = callbacks::automatization::UserGroup;

CLI::App* setup(CLI::App* app) {
    return app->add_subcommand("group", "Manage user groups")
        ->require_subcommand();
}

CLI::App* setupAdd(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<AddOptions>();
    auto* sub = app->add_subcommand("add", "Add group")
                    ->alias("a")
                    ->callback([opt, &client]() { caUG::add(*opt, *client); });
    sub->add_option("-n, --name", opt->name, "Name of the group")->required();
    sub->add_option("-a, --addressees", opt->addressees,
                    "Target addressees (email addresses)")
        ->required()
        ->expected(-1);
    return sub;
}

CLI::App* setupList(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<ListOptions>();
    return app->add_subcommand("list", "List groups")
        ->alias("ls")
        ->callback([opt, &client]() { caUG::list(*opt, *client); });
}

CLI::App* setupShow(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<ShowOptions>();
    auto* sub = app->add_subcommand("show", "Show members of the group")
                    ->alias("sh")
                    ->callback([opt, &client]() { caUG::show(*opt, *client); });
    sub->add_option("-n, --name", opt->name, "Name of the group")->required();
    return sub;
}

CLI::App* setupRemove(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<RemoveOptions>();
    auto* sub =
        app->add_subcommand("remove", "Remove group")
            ->alias("d")
            ->callback([opt, &client]() { caUG::remove(*opt, *client); });
    sub->add_option("-n, --name", opt->name, "Name of the group")->required();
    return sub;
}

CLI::App* setupSend(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<SendOptions>();
    auto* sub = app->add_subcommand("send", "Send a message to the group")
                    ->alias("s")
                    ->callback([opt, &client]() { caUG::send(*opt, *client); });
    sub->add_option("msg", opt->text, "Message text");
    sub->add_option("-g, --group", opt->group_name, "target group")->required();

    return sub;
}
}  // namespace sub::automatization::UserGroup