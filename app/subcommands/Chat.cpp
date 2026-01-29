#include "Chat.hpp"

#include "LazyGraphClient.h"
#include "callbacks/Chat.hpp"

namespace sub::chat {
namespace cc = callbacks::chat;

CLI::App* setup(CLI::App* app) {
    return app->add_subcommand("chat", "Manage chats")
        ->require_subcommand();
}

CLI::App* setupAdd(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<AddOptions>();
    auto* sub = app->add_subcommand("add", "Add private chat")
                    ->alias("a")
                    ->callback([opt, &client]() { cc::add(*opt, *client); });
    sub->add_option("emails", opt->emails);

    return sub;
}

CLI::App* setupList(CLI::App* app, LazyGraphClient& client) {
    const auto opt = std::make_shared<ListOptions>();

    auto* sub = app->add_subcommand("list", "List chats")
                    ->alias("ls")
                    ->callback([opt, &client]() { cc::list(*opt, *client); });

    return sub;
}

}  // namespace sub::chat
