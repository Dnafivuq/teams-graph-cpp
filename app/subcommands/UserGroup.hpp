#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "BaseOptions.hpp"
#include "CLI/CLI.hpp"

namespace sub::automatization::UserGroup {
struct AddOptions : opts::BaseAddOptions {
    std::string name;
    std::vector<std::string> addressees;
};
struct ListOptions : opts::BaseListOptions {};
struct DeleteOptions : opts::BaseDeleteOptions {
    std::string name;
};
struct ShowOptions : opts::BaseShowOptions {
    std::string name;
};
struct SendOptions : opts::BaseSendOptions {
    std::string text;
    std::string group_name;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupList(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupSend(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupShow(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupDelete(CLI::App*, teams::GraphServiceClient&);

}  // namespace sub::automatization::UserGroup