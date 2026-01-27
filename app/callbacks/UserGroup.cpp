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
    fs::path filePath = repo / "app/data/groups.json";

    fs::create_directories(filePath.parent_path());
    json root;

    if (fs::exists(filePath)) {
        std::ifstream in(filePath);
        if (in.good()) {
            in >> root;
        }
    }
    if (!root.contains("groups") || !root["groups"].is_array()) {
        root["groups"] = json::array();
    }

    for (const auto& group : root["groups"])
        if (group.contains("name") && group["name"].is_string() &&
            group["name"] == options.name) {
            std::cerr << "Group with given name already exists\n";
            return;
        }

    json group;
    group["name"] = options.name;
    group["members"] = json::array();
    for (const auto& member : options.members) {
        group["members"].push_back(member);
    }
    root["groups"].push_back(group);

    std::ofstream out(filePath);
    out << root.dump(4);
}

void list(sub::automatization::UserGroup::ListOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path filePath = repo / "app/data/groups.json";

    fs::create_directories(filePath.parent_path());
    json root;

    if (fs::exists(filePath)) {
        std::ifstream in(filePath);
        if (in.good()) {
            in >> root;
        }
    }
    if (!root.contains("groups") || !root["groups"].is_array()) {
        root["groups"] = json::array();
    }

    for (const auto& group : root["groups"].items()) {
        if (!group.value().contains("name") || group.value()["name"].is_null())
            continue;
        std::cout << group.value()["name"] << "\n";
    }
}

void show(sub::automatization::UserGroup::ShowOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path filePath = repo / "app/data/groups.json";

    fs::create_directories(filePath.parent_path());
    json root;

    if (fs::exists(filePath)) {
        std::ifstream in(filePath);
        if (in.good()) {
            in >> root;
        }
    }
    if (!root.contains("groups") || !root["groups"].is_array()) {
        root["groups"] = json::array();
    }

    for (const auto& group : root["groups"].items()) {
        if (!group.value().contains("name") ||
            group.value()["name"].is_null() ||
            group.value()["name"] != options.name)
            continue;
        std::cout << "Name: " << group.value()["name"] << "\n" << "Members: \n";
        for (const auto& member : group.value()["members"])
            std::cout << "\t" << member << "\n";
    }
}

void remove(sub::automatization::UserGroup::RemoveOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path filePath = repo / "app/data/groups.json";

    fs::create_directories(filePath.parent_path());
    json root;

    if (fs::exists(filePath)) {
        std::ifstream in(filePath);
        if (in.good()) {
            in >> root;
        }
    }
    if (!root.contains("groups") || !root["groups"].is_array()) {
        root["groups"] = json::array();
    }

    json newGroups = json::array();

    for (const auto& group : root["groups"]) {
        if (group.contains("name") && group["name"].is_string() &&
            group["name"] == options.name)
            continue;
        newGroups.push_back(group);
    }

    root["groups"] = std::move(newGroups);

    fs::create_directories(filePath.parent_path());
    std::ofstream out(filePath);
    if (!out.good()) {
        std::cerr << "Failed to open groups file for writing\n";
        return;
    }
    out << root.dump(4);
}

void send(sub::automatization::UserGroup::SendOptions const& options,
          teams::GraphServiceClient const& client) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path filePath = repo / "app/data/groups.json";

    json root;

    if (!fs::exists(filePath)) {
        std::cerr << "Groups file not found\n";
        return;
    }

    std::ifstream in(filePath);
    if (!in.good()) {
        std::cerr << "Failed to open groups file\n";
        return;
    }

    in >> root;

    if (!root.contains("groups") || !root["groups"].is_array()) {
        std::cerr << "Invalid groups format\n";
        return;
    }

    const json* targetGroup = nullptr;

    for (const auto& group : root["groups"]) {
        if (group.contains("name") && group["name"].is_string() &&
            group["name"] == options.group_name) {
            targetGroup = &group;
            break;
        }
    }

    if (!targetGroup) {
        std::cerr << "Group not found: " << options.group_name << '\n';
        return;
    }

    if (!targetGroup->contains("members") ||
        !(*targetGroup)["members"].is_array()) {
        std::cerr << "Group has no members\n";
        return;
    }

    for (const auto& member : (*targetGroup)["members"]) {
        if (!member.is_string()) continue;

        const std::string email = member.get<std::string>();

        try {
            const std::string userId =
                client.users().byEmail(email).get().value().id.value();

            auto me = teams::ConversationMember{
                .id = std::string{client.me().get().value().id.value()},
                .roles = std::vector<std::string>{"owner"}};
            me.history_visibility_start.reset();

            auto other = teams::ConversationMember{
                .id = std::string{userId},
                .roles = std::vector<std::string>{"owner"}};
            other.history_visibility_start.reset();

            auto chat = teams::Chat{
                .type = std::string{"oneOnOne"},
                .members =
                    std::vector<teams::priv::ConversationMember>{me, other}};
            auto createdChat = client.chats().post(chat);

            if (!createdChat.has_value()) {
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
                    createdChat.error());

                return;
            }
            auto chat_id = createdChat.value().id.value();

            auto msg = teams::Message{
                .body = teams::priv::ItemBody{.content = options.text,
                                              .content_type = "text"}};
            client.chats().byId(chat_id).messages().post(msg);
            std::cout << "Message sent to " << email << '\n';
        } catch (const std::exception& e) {
            std::cerr << "Failed to send to " << email << ": " << e.what()
                      << '\n';
        }
    }
}
}  // namespace callbacks::automatization::UserGroup
