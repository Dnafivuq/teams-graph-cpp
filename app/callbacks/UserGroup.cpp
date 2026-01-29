#include "UserGroup.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "utils.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace callbacks::automatization::UserGroup {

void add(sub::automatization::UserGroup::AddOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path file_path = repo / "app/data/groups.json";

    fs::create_directories(file_path.parent_path());
    json root;

    if (fs::exists(file_path)) {
        std::ifstream instream(file_path);
        if (instream.good()) {
            instream >> root;
        }
    }
    if (!root.contains("groups") || !root["groups"].is_array()) {
        root["groups"] = json::array();
    }

    for (const auto& group : root["groups"]) {
        if (group.contains("name") && group["name"].is_string() &&
            group["name"] == options.name) {
            std::cerr << "Group with given name already exists\n";
            return;
        }
    }

    json group;
    group["name"] = options.name;
    group["members"] = json::array();
    for (const auto& member : options.members) {
        group["members"].push_back(member);
    }
    root["groups"].push_back(group);

    std::ofstream out(file_path);
    out << root.dump(4);
}

void list(sub::automatization::UserGroup::ListOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path file_path = repo / "app/data/groups.json";

    fs::create_directories(file_path.parent_path());
    json root;

    if (fs::exists(file_path)) {
        std::ifstream instream(file_path);
        if (instream.good()) {
            instream >> root;
        }
    }
    if (!root.contains("groups") || !root["groups"].is_array()) {
        root["groups"] = json::array();
    }

    for (const auto& group : root["groups"].items()) {
        if (!group.value().contains("name") || group.value()["name"].is_null()) {
            continue;
        }
        std::cout << group.value()["name"] << "\n";
    }
}

void show(sub::automatization::UserGroup::ShowOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path file_path = repo / "app/data/groups.json";

    fs::create_directories(file_path.parent_path());
    json root;

    if (fs::exists(file_path)) {
        std::ifstream instream(file_path);
        if (instream.good()) {
            instream >> root;
        }
    }
    if (!root.contains("groups") || !root["groups"].is_array()) {
        root["groups"] = json::array();
    }

    for (const auto& group : root["groups"].items()) {
        if (!group.value().contains("name") ||
            group.value()["name"].is_null() ||
            group.value()["name"] != options.name) {
            continue;
        }
        std::cout << "Name: " << group.value()["name"] << "\n"
                  << "Members: \n";
        for (const auto& member : group.value()["members"]) {
            std::cout << "\t" << member << "\n";
        }
    }
}

void remove(sub::automatization::UserGroup::RemoveOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path file_path = repo / "app/data/groups.json";

    fs::create_directories(file_path.parent_path());
    json root;

    if (fs::exists(file_path)) {
        std::ifstream instream(file_path);
        if (instream.good()) {
            instream >> root;
        }
    }
    if (!root.contains("groups") || !root["groups"].is_array()) {
        root["groups"] = json::array();
    }

    json new_groups = json::array();

    for (const auto& group : root["groups"]) {
        if (group.contains("name") && group["name"].is_string() &&
            group["name"] == options.name) {
            continue;
        }
        new_groups.push_back(group);
    }

    root["groups"] = std::move(new_groups);

    fs::create_directories(file_path.parent_path());
    std::ofstream out(file_path);
    if (!out.good()) {
        std::cerr << "Failed to open groups file for writing\n";
        return;
    }
    out << root.dump(4);
}

void send(sub::automatization::UserGroup::SendOptions const& options,
          teams::GraphServiceClient const& client) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path file_path = repo / "app/data/groups.json";

    json root;

    if (!fs::exists(file_path)) {
        std::cerr << "Groups file not found\n";
        return;
    }

    std::ifstream instream(file_path);
    if (!instream.good()) {
        std::cerr << "Failed to open groups file\n";
        return;
    }

    instream >> root;

    if (!root.contains("groups") || !root["groups"].is_array()) {
        std::cerr << "Invalid groups format\n";
        return;
    }

    const json* target_group = nullptr;

    for (const auto& group : root["groups"]) {
        if (group.contains("name") && group["name"].is_string() &&
            group["name"] == options.group_name) {
            target_group = &group;
            break;
        }
    }

    if (target_group == nullptr) {
        std::cerr << "Group not found: " << options.group_name << '\n';
        return;
    }

    if (!target_group->contains("members") ||
        !(*target_group)["members"].is_array()) {
        std::cerr << "Group has no members\n";
        return;
    }

    for (const auto& member : (*target_group)["members"]) {
        if (!member.is_string()) {
            continue;
        }

        const std::string email = member.get<std::string>();

        try {
            const std::string user_id =
                client.users().byEmail(email).get().value().id.value();

            auto myself = teams::ConversationMember{
                .id = std::string{client.me().get().value().id.value()},
                .roles = std::vector<std::string>{"owner"}};
            myself.history_visibility_start.reset();

            auto other = teams::ConversationMember{
                .id = std::string{user_id},
                .roles = std::vector<std::string>{"owner"}};
            other.history_visibility_start.reset();

            auto chat = teams::Chat{
                .type = std::string{"oneOnOne"},
                .members =
                    std::vector<teams::priv::ConversationMember>{myself, other}};
            auto created_chat = client.chats().post(chat);

            if (!created_chat.has_value()) {
                std::visit(
                    [](const auto& err) {
                        using T = std::decay_t<decltype(err)>;

                        if constexpr (std::is_same_v<
                                          T, teams::priv::TransportError>) {
                            std::cerr << "Transport error: " << err.message
                                      << '\n';
                        } else if constexpr (std::is_same_v<
                                                 T,
                                                 teams::priv::ParsingError>) {
                            std::cerr << "Parsing error: " << err.message
                                      << '\n';
                        } else if constexpr (std::is_same_v<
                                                 T, teams::priv::GraphError>) {
                            std::cerr << "Graph error: " << err.message << '\n';
                        }
                    },
                    created_chat.error());

                return;
            }
            auto chat_id = created_chat.value().id.value();

            auto msg = teams::Message{
                .body = teams::priv::ItemBody{.content = options.text,
                                              .content_type = "text"}};
            auto const result = client.chats().byId(chat_id).messages().post(msg);
            std::cout << "Message sent to " << email << '\n';
        } catch (const std::exception& e) {
            std::cerr << "Failed to send to " << email << ": " << e.what()
                      << '\n';
        }
    }
}
}  // namespace callbacks::automatization::UserGroup
