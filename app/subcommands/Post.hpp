#pragma once
#include <teams_lib/client/GraphServiceClient.hpp>

#include "BaseOptions.hpp"
#include "CLI/CLI.hpp"

namespace sub::post {
struct AddOptions : opts::BaseAddOptions {
    std::string text;
    std::string team;
    std::string channel;
};
struct ListOptions : opts::BaseListOptions {
    std::string team;
    std::string channel;
};

CLI::App* setup(CLI::App*);
CLI::App* setupAdd(CLI::App*, teams::GraphServiceClient&);
CLI::App* setupList(CLI::App*, teams::GraphServiceClient&);

}  // namespace sub::post