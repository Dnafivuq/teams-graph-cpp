#include "Channel.hpp"

#include "LazyGraphClient.h"
#include "callbacks/Channel.hpp"

namespace sub::channel {
namespace cc = callbacks::channel;

CLI::App* setup(CLI::App* app) {
    return app->add_subcommand("channel", "Manage channels")
        ->require_subcommand();
}

CLI::App* setupAdd(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<AddOptions>();
    auto* sub = app->add_subcommand("add", "Add channel")
                    ->alias("a")
                    ->callback([opt, &client]() { cc::add(*opt, *client); });
    sub->add_option("name", opt->name, "Channel name")->required();
    sub->add_option("-t, --team", opt->team)->required();
    sub->add_flag("-p, --public", opt->isPublic, "Make the channel public");
    return sub;
}

CLI::App* setupList(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<ListOptions>();

    auto* sub = app->add_subcommand("list", "List channels")
                    ->alias("ls")
                    ->callback([opt, &client]() { cc::list(*opt, *client); });
    sub->add_option("-t, --team", opt->team)->required();
    return sub;
}

CLI::App* setupRemove(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<RemoveOptions>();
    auto* sub = app->add_subcommand("remove", "Delete channel")
                    ->alias("r")
                    ->callback([opt, &client]() { cc::remove(*opt, *client); });
    sub->add_option("name", opt->name, "Channel name")->required();
    sub->add_option("-t, --team", opt->team)->required();
    return sub;
}

}  // namespace sub::channel
