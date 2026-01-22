#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "BaseOptions.hpp"
#include "CLI/CLI.hpp"
#include "LazyGraphClient.h"

namespace sub::automatization::UserGroup {
struct AddOptions : opts::BaseAddOptions {
    std::string name;
    std::vector<std::string> members;
};
struct ListOptions : opts::BaseListOptions {};
struct RemoveOptions : opts::BaseRemoveOptions {
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
CLI::App* setupAdd(CLI::App*, LazyGraphClient&);
CLI::App* setupList(CLI::App*, LazyGraphClient&);
CLI::App* setupSend(CLI::App*, LazyGraphClient&);
CLI::App* setupShow(CLI::App*, LazyGraphClient&);
CLI::App* setupRemove(CLI::App*, LazyGraphClient&);

}  // namespace sub::automatization::UserGroup