#pragma once
#include <CLI/CLI.hpp>
#include <string>

#include "BaseOptions.hpp"
#include "LazyGraphClient.h"

namespace sub::channel {
struct RemoveOptions : opts::BaseRemoveOptions {
    std::string team;
    std::string name;
};
struct AddOptions : opts::BaseAddOptions {
    std::string team;
    std::string name;
};
struct ListOptions : opts::BaseListOptions {
    std::string team;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, LazyGraphClient&);
CLI::App* setupList(CLI::App*, LazyGraphClient&);
CLI::App* setupRemove(CLI::App*, LazyGraphClient&);

}  // namespace sub::channel