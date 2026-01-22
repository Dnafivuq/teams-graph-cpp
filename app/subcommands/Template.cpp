#include "Template.hpp"

#include "callbacks/Template.hpp"

namespace sub::automatization::Template {
namespace caT = callbacks::automatization::Template;

CLI::App* setup(CLI::App* app) {
    return app->add_subcommand("template", "Manage templates")
        ->require_subcommand();
}

CLI::App* setupAdd(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<AddOptions>();
    auto* sub = app->add_subcommand("add", "Add template")
                    ->alias("a")
                    ->callback([opt, &client]() { caT::add(*opt); });
    sub->add_option("-n, --name", opt->name, "Name of the template")
        ->required();
    sub->add_option("-t, --text", opt->text, "Text of the template")
        ->required();
    return sub;
}

CLI::App* setupRemove(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<RemoveOptions>();
    auto* sub = app->add_subcommand("remove", "Remove template")
                    ->alias("r")
                    ->callback([opt, &client]() { caT::remove(*opt); });
    sub->add_option("-n, --name", opt->name, "Name of the template")
        ->required();
    return sub;
}

CLI::App* setupShow(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<ShowOptions>();
    auto* sub =
        app->add_subcommand("show", "Show content of the chosen template")
            ->alias("sh")
            ->callback([opt, &client]() { caT::show(*opt); });
    sub->add_option("-n, --name", opt->name, "Name of the template")
        ->required();
    return sub;
}

CLI::App* setupList(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<ListOptions>();
    return app->add_subcommand("list", "List templates")
        ->alias("ls")
        ->callback([opt, &client]() { caT::list(*opt); });
}

CLI::App* setupSend(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<SendOptions>();
    auto* sub = app->add_subcommand("send", "Send template to a group")
                    ->alias("s")
                    ->callback([opt, &client]() { caT::send(*opt, *client); });
    sub->add_option("-t, --template", opt->template_name, "Template to send")
        ->required();
    sub->add_option("-g, --group", opt->group_name,
                    "Group to send the template to")
        ->required();
    sub->add_option("-v, --variables", opt->variables,
                    "Values to fill the variables in the template")
        ->required()
        ->expected(-1);

    return sub;
}
}  // namespace sub::automatization::Template