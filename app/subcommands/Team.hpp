#pragma once
#include "BaseOptions.hpp"
#include "CLI/CLI.hpp"

namespace sub::team {
struct AddOptions : opts::BaseAddOptions {};
struct ListOptions : opts::BaseListOptions {};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*);
CLI::App* setupList(CLI::App*);
}  // namespace sub::team