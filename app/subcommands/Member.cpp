#include "Member.hpp"

#include "LazyGraphClient.h"
#include "callbacks/Member.hpp"

namespace sub::member {
namespace cm = callbacks::member;

CLI::App* setup(CLI::App* app) {
    return app->add_subcommand("member", "Manage members")
        ->require_subcommand();
}

CLI::App* setupAdd(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<AddOptions>();
    auto* sub = app->add_subcommand("add", "Add members")
                    ->alias("a")
                    ->callback([opt, &client]() { cm::add(*opt, *client); });
    sub->add_option("-c, --channel", opt->channel, "Channel name");
    sub->add_option("-t, --team", opt->team)->required();
    sub->add_option("email", opt->email);

    return sub;
}

CLI::App* setupList(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<ListOptions>();

    auto* sub = app->add_subcommand("list", "List members")
                    ->alias("ls")
                    ->callback([opt, &client]() { cm::list(*opt, *client); });
    sub->add_option("-t, --team", opt->team)->required();
    sub->add_option("-c, --channel", opt->channel, "Channel name");

    return sub;
}

CLI::App* setupRemove(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<RemoveOptions>();
    auto* sub = app->add_subcommand("remove", "Delete members")
                    ->alias("r")
                    ->callback([opt, &client]() { cm::remove(*opt, *client); });
    sub->add_option("email", opt->email);
    sub->add_option("-c, --channel", opt->channel, "Channel name");
    sub->add_option("-t, --team", opt->team)->required();
    return sub;
}

}  // namespace sub::member
