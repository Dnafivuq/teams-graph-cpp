#include "Team.hpp"

#include "subcommands/Team.hpp"

namespace callbacks::team {
void add(sub::team::AddOptions const& options) {
    std::cout << "Hello from team add";
}
void list(sub::team::ListOptions const& options) {
    std::cout << "Hello from team list";
}
}  // namespace callbacks::team
