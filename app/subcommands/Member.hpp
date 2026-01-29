#pragma once
#include <CLI/CLI.hpp>
#include <string>
#include <vector>

#include "BaseOptions.hpp"
#include "LazyGraphClient.h"

namespace sub::member {
struct RemoveOptions : opts::BaseRemoveOptions {
    std::string team;
    std::string channel;
    std::vector<std::string> email;
};
struct AddOptions : opts::BaseAddOptions {
    std::string team;
    std::string channel;
    std::vector<std::string> email;
};
struct ListOptions : opts::BaseListOptions {
    std::string team;
    std::string channel;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, LazyGraphClient&);
CLI::App* setupList(CLI::App*, LazyGraphClient&);
CLI::App* setupRemove(CLI::App*, LazyGraphClient&);

}  // namespace sub::member
