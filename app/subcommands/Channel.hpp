#pragma once
#include <CLI/CLI.hpp>

#include "BaseOptions.hpp"
#include "LazyGraphClient.h"

namespace sub::channel {
struct AddOptions : opts::BaseAddOptions {
    std::string team;
};
struct ListOptions : opts::BaseListOptions {
    std::string team;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, LazyGraphClient&);
CLI::App* setupList(CLI::App*, LazyGraphClient&);

}  // namespace sub::channel