#pragma once
#include <CLI/CLI.hpp>
#include <string>
#include <vector>

#include "BaseOptions.hpp"
#include "LazyGraphClient.h"

namespace sub::post {
struct AddOptions : opts::BaseAddOptions {
    std::string text;
    std::vector<std::string> team;
    std::vector<std::string> channel;
};
struct ListOptions : opts::BaseListOptions {
    std::string team;
    std::string channel;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, LazyGraphClient&);
CLI::App* setupList(CLI::App*, LazyGraphClient&);

}  // namespace sub::post