#pragma once
#include <CLI/CLI.hpp>
#include <string>
#include <teams_lib/client/GraphServiceClient.hpp>
#include <vector>

#include "BaseOptions.hpp"
#include "LazyGraphClient.h"

namespace sub::team {
struct RemoveOptions : opts::BaseRemoveOptions {
    std::vector<std::string> names;
};
struct AddOptions : opts::BaseAddOptions {
    std::vector<std::string> names;
};
struct ListOptions : opts::BaseListOptions {};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, LazyGraphClient&);
CLI::App* setupList(CLI::App*, LazyGraphClient&);
CLI::App* setupRemove(CLI::App*, LazyGraphClient&);
}  // namespace sub::team
