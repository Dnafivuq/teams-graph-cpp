#pragma once
#include <CLI/CLI.hpp>
#include <string>
#include <vector>

#include "BaseOptions.hpp"
#include "LazyGraphClient.h"

namespace sub::chat {
struct AddOptions : opts::BaseAddOptions {
    std::vector<std::string> emails;
};
struct ListOptions : opts::BaseListOptions {
    std::vector<std::string> emails;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, LazyGraphClient&);
CLI::App* setupList(CLI::App*, LazyGraphClient&);

}  // namespace sub::chat
