#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "BaseOptions.hpp"
#include "CLI/CLI.hpp"
#include "LazyGraphClient.h"

namespace sub::automatization::Template {
struct AddOptions : opts::BaseAddOptions {
    std::string text;
    std::string name;
};
struct ListOptions : opts::BaseListOptions {};
struct SendOptions : opts::BaseSendOptions {
    std::string template_name;
    std::string group_name;
    std::vector<std::string> variables;
};
struct ShowOptions : opts::BaseShowOptions {
    std::string name;
};
struct RemoveOptions : opts::BaseRemoveOptions {
    std::string name;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, LazyGraphClient&);
CLI::App* setupRemove(CLI::App*, LazyGraphClient&);
CLI::App* setupShow(CLI::App*, LazyGraphClient&);
CLI::App* setupList(CLI::App*, LazyGraphClient&);
CLI::App* setupSend(CLI::App*, LazyGraphClient&);

}  // namespace sub::automatization::Template