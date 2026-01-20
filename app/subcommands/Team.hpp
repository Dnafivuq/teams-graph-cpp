#pragma once
#include <CLI/CLI.hpp>
#include <string>
#include <teams_lib/client/GraphServiceClient.hpp>

#include "BaseOptions.hpp"
#include "LazyGraphClient.h"

namespace sub::team {
struct AddOptions : opts::BaseAddOptions {
    std::string name;
};
struct ListOptions : opts::BaseListOptions {};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, LazyGraphClient&);
CLI::App* setupList(CLI::App*, LazyGraphClient&);
}  // namespace sub::team