#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "BaseOptions.hpp"
#include "CLI/CLI.hpp"

namespace sub::automatization::Template {
struct AddOptions : opts::BaseAddOptions {
    std::string text;
    std::string name;
};
struct ListOptions : opts::BaseListOptions {};
struct SendOptions {
    std::string template_name;
    std::string group_name;
    std::vector<std::string> variables;
};
struct ShowOptions {
    std::string name;
};
struct DeleteOptions {
    std::string name;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupDelete(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupShow(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupList(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupSend(CLI::App*, teams::GraphServiceClient&);

}  // namespace sub::automatization::Template