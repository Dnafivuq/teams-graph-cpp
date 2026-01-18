#include "Post.hpp"

#include "callbacks/Post.hpp"

namespace sub::post {
namespace cp = callbacks::post;

CLI::App* setup(CLI::App* app) {
    return app->add_subcommand("post", "Manage posts")->require_subcommand();
}

CLI::App* setupAdd(CLI::App* app, teams::GraphServiceClient& client) {
    const auto opt = std::make_shared<AddOptions>();
    auto* sub = app->add_subcommand("add", "Add post")
                    ->alias("a")
                    ->callback([opt, &client]() { cp::add(*opt, client); });
    sub->add_option("msg", opt->text, "Message text");
    sub->add_option("-t,--team", opt->team, "target team")->required();
    sub->add_option("-c, --channel", opt->channel, "target channel")
        ->required();

    return sub;
}

CLI::App* setupList(CLI::App* app, teams::GraphServiceClient& client) {
    const auto opt = std::make_shared<ListOptions>();
    auto* sub = app->add_subcommand("list", "List posts")
                    ->alias("ls")
                    ->callback([opt, &client]() { cp::list(*opt, client); });
    sub->add_option("-t,--team", opt->team, "target team")->required();
    sub->add_option("-c, --channel", opt->channel, "target channel")
        ->required();

    return sub;
}
}  // namespace sub::post