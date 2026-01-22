#include "Template.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "utils.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace callbacks::automatization::Template {

void add(sub::automatization::Template::AddOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path filePath = repo / "app/data/templates.json";

    fs::create_directories(filePath.parent_path());
    json root;

    if (fs::exists(filePath)) {
        std::ifstream in(filePath);
        if (in.good()) {
            in >> root;
        }
    }
    if (!root.contains("templates") || !root["templates"].is_array()) {
        root["templates"] = json::array();
    }

    json group;
    group["name"] = options.name;
    group["text"] = options.text;
    root["templates"].push_back(group);

    std::ofstream out(filePath);
    out << root.dump(4);
}

void list(sub::automatization::Template::ListOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path filePath = repo / "app/data/templates.json";

    fs::create_directories(filePath.parent_path());
    json root;

    if (fs::exists(filePath)) {
        std::ifstream in(filePath);
        if (in.good()) {
            in >> root;
        }
    }
    if (!root.contains("templates") || !root["templates"].is_array()) {
        root["templates"] = json::array();
    }

    for (const auto& group : root["templates"].items()) {
        if (!group.value().contains("name") || group.value()["name"].is_null())
            continue;
        std::cout << group.value()["name"] << "\n";
    }
}

void show(sub::automatization::Template::ShowOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path filePath = repo / "app/data/templates.json";

    fs::create_directories(filePath.parent_path());
    json root;

    if (fs::exists(filePath)) {
        std::ifstream in(filePath);
        if (in.good()) {
            in >> root;
        }
    }
    if (!root.contains("templates") || !root["templates"].is_array()) {
        root["templates"] = json::array();
    }

    for (const auto& group : root["templates"].items()) {
        if (!group.value().contains("name") ||
            group.value()["name"].is_null() ||
            group.value()["name"] != options.name)
            continue;
        std::cout << "Name: " << group.value()["name"] << "\n"
                  << "Text: " << group.value()["text"] << "\n ";
    }
}

void remove(sub::automatization::Template::RemoveOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path filePath = repo / "app/data/templates.json";

    fs::create_directories(filePath.parent_path());
    json root;

    if (fs::exists(filePath)) {
        std::ifstream in(filePath);
        if (in.good()) {
            in >> root;
        }
    }
    if (!root.contains("templates") || !root["templates"].is_array()) {
        root["templates"] = json::array();
    }

    json newTemplates = json::array();

    for (const auto& group : root["templates"]) {
        if (group.contains("name") && group["name"].is_string() &&
            group["name"] == options.name)
            continue;
        newTemplates.push_back(group);
    }

    root["templates"] = std::move(newTemplates);

    fs::create_directories(filePath.parent_path());
    std::ofstream out(filePath);
    if (!out.good()) {
        std::cerr << "Failed to open templates file for writing\n";
        return;
    }
    out << root.dump(4);
}

void send(sub::automatization::Template::SendOptions const& options,
          teams::GraphServiceClient const& client) {
    namespace fs = std::filesystem;

    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path filePathGroups = repo / "app/data/groups.json";
    fs::path filePathTemplates = repo / "app/data/templates.json";

    json groupsRoot;
    if (!fs::exists(filePathGroups)) {
        std::cerr << "Groups file not found\n";
        return;
    }
    {
        std::ifstream in(filePathGroups);
        if (!in.good()) {
            std::cerr << "Failed to open groups file\n";
            return;
        }
        in >> groupsRoot;
    }

    if (!groupsRoot.contains("groups") || !groupsRoot["groups"].is_array()) {
        std::cerr << "Invalid groups format\n";
        return;
    }

    const json* targetGroup = nullptr;
    for (const auto& group : groupsRoot["groups"]) {
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

    json templatesRoot;
    if (!fs::exists(filePathTemplates)) {
        std::cerr << "Templates file not found\n";
        return;
    }
    {
        std::ifstream in(filePathTemplates);
        if (!in.good()) {
            std::cerr << "Failed to open templates file\n";
            return;
        }
        in >> templatesRoot;
    }

    if (!templatesRoot.contains("templates") ||
        !templatesRoot["templates"].is_array()) {
        std::cerr << "Invalid templates format\n";
        return;
    }

    const json* targetTemplate = nullptr;
    for (const auto& tmpl : templatesRoot["templates"]) {
        if (tmpl.contains("name") && tmpl["name"].is_string() &&
            tmpl["name"] == options.template_name) {
            targetTemplate = &tmpl;
            break;
        }
    }

    if (!targetTemplate) {
        std::cerr << "Template not found: " << options.template_name << '\n';
        return;
    }

    if (!targetTemplate->contains("text") ||
        !(*targetTemplate)["text"].is_string()) {
        std::cerr << "Template missing text\n";
        return;
    }

    std::string templateText = (*targetTemplate)["text"];

    std::vector<std::string> placeholders;
    size_t pos = 0;
    while ((pos = templateText.find('[', pos)) != std::string::npos) {
        size_t end = templateText.find(']', pos);
        if (end != std::string::npos) {
            placeholders.push_back(templateText.substr(pos + 1, end - pos - 1));
            pos = end + 1;
        } else
            break;
    }

    const auto& members = (*targetGroup)["members"];
    size_t numPlaceholders = placeholders.size();
    if (options.variables.size() != members.size() * numPlaceholders) {
        std::cerr << "Mismatch: variables size does not match number of "
                     "members * placeholders\n";
        return;
    }

    for (size_t i = 0; i < members.size(); ++i) {
        const auto& member = members[i];
        if (!member.is_string()) continue;

        std::string messageText = templateText;
        for (size_t j = 0; j < numPlaceholders; ++j) {
            std::string ph = "[" + placeholders[j] + "]";
            size_t varIndex = i * numPlaceholders + j;
            size_t pos = 0;
            while ((pos = messageText.find(ph, pos)) != std::string::npos) {
                messageText.replace(pos, ph.size(),
                                    options.variables[varIndex]);
                pos += options.variables[varIndex].size();
            }
        }
        const std::string email = member.get<std::string>();

        try {
            const std::string userId =
                client.users().byEmail(email).get().value().id.value();

            auto me = teams::ConversationMember{
                .id = std::string{client.me().get().value().id.value()},
                .roles = std::vector<std::string>{"owner"}};

            auto other = teams::ConversationMember{
                .id = userId, .roles = std::vector<std::string>{"owner"}};

            auto chat = teams::Chat{
                .type = "oneOnOne",
                .members =
                    std::vector<teams::priv::ConversationMember>{me, other}};

            auto createdChat = client.chats().post(chat);
            auto chat_id = createdChat.value().id.value();

            auto msg = teams::Message{
                .body = teams::priv::ItemBody{.content = messageText,
                                              .content_type = "text"}};
            client.chats().byId(chat_id).messages().post(msg);

            std::cout << "Message sent to " << email << '\n';
        } catch (const std::exception& e) {
            std::cerr << "Failed to send to " << email << ": " << e.what()
                      << '\n';
        }
    }
}

}  // namespace callbacks::automatization::Template
