#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "BaseOptions.hpp"
#include "CLI/CLI.hpp"

namespace sub::channel {
struct AddOptions : opts::BaseAddOptions {
    std::string team;
};
struct ListOptions : opts::BaseListOptions {
    std::string team;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupList(CLI::App*, teams::GraphServiceClient&);

}  // namespace sub::channel