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
    fs::path file_path = repo / "app/data/templates.json";

    fs::create_directories(file_path.parent_path());
    json root;

    if (fs::exists(file_path)) {
        std::ifstream instream(file_path);
        if (instream.good()) {
            instream >> root;
        }
    }
    if (!root.contains("templates") || !root["templates"].is_array()) {
        root["templates"] = json::array();
    }
    for (const auto& user_template : root["templates"]) {
        if (user_template.contains("name") &&
            user_template["name"].is_string() &&
            user_template["name"] == options.name) {
            std::cerr << "Template with given name already exists\n";
            return;
        }
    }

    json user_template;
    user_template["name"] = options.name;
    user_template["text"] = options.text;
    root["templates"].push_back(user_template);

    std::ofstream out(file_path);
    out << root.dump(4);
}

void list(sub::automatization::Template::ListOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path file_path = repo / "app/data/templates.json";

    fs::create_directories(file_path.parent_path());
    json root;

    if (fs::exists(file_path)) {
        std::ifstream instream(file_path);
        if (instream.good()) {
            instream >> root;
        }
    }
    if (!root.contains("templates") || !root["templates"].is_array()) {
        root["templates"] = json::array();
    }

    for (const auto& user_template : root["templates"].items()) {
        if (!user_template.value().contains("name") ||
            user_template.value()["name"].is_null()) {
            continue;
        }
        std::cout << user_template.value()["name"] << "\n";
    }
}

void show(sub::automatization::Template::ShowOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path file_path = repo / "app/data/templates.json";

    fs::create_directories(file_path.parent_path());
    json root;

    if (fs::exists(file_path)) {
        std::ifstream instream(file_path);
        if (instream.good()) {
            instream >> root;
        }
    }
    if (!root.contains("templates") || !root["templates"].is_array()) {
        root["templates"] = json::array();
    }

    for (const auto& user_template : root["templates"].items()) {
        if (!user_template.value().contains("name") ||
            user_template.value()["name"].is_null() ||
            user_template.value()["name"] != options.name) {
            continue;
        }
        std::cout << "Name: " << user_template.value()["name"] << "\n"
                  << "Text: " << user_template.value()["text"] << "\n ";
    }
}

void remove(sub::automatization::Template::RemoveOptions const& options) {
    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path file_path = repo / "app/data/templates.json";

    fs::create_directories(file_path.parent_path());
    json root;

    if (fs::exists(file_path)) {
        std::ifstream instream(file_path);
        if (instream.good()) {
            instream >> root;
        }
    }
    if (!root.contains("templates") || !root["templates"].is_array()) {
        root["templates"] = json::array();
    }

    json new_templates = json::array();

    for (const auto& user_template : root["templates"]) {
        if (user_template.contains("name") &&
            user_template["name"].is_string() &&
            user_template["name"] == options.name) {
            continue;
        }
        new_templates.push_back(user_template);
    }

    root["templates"] = std::move(new_templates);

    fs::create_directories(file_path.parent_path());
    std::ofstream out(file_path);
    if (!out.good()) {
        std::cerr << "Failed to open templates file for writing\n";
        return;
    }
    out << root.dump(4);
}

void send(sub::automatization::Template::SendOptions const& options,  // NOLINT
          teams::GraphServiceClient const& client) {
    namespace fs = std::filesystem;

    fs::path repo = utils::find_repo_root(fs::current_path());
    fs::path file_path_groups = repo / "app/data/groups.json";
    fs::path file_path_templates = repo / "app/data/templates.json";

    json groups_root;
    if (!fs::exists(file_path_groups)) {
        std::cerr << "Groups file not found\n";
        return;
    }
    {
        std::ifstream instream(file_path_groups);
        if (!instream.good()) {
            std::cerr << "Failed to open groups file\n";
            return;
        }
        instream >> groups_root;
    }

    if (!groups_root.contains("groups") || !groups_root["groups"].is_array()) {
        std::cerr << "Invalid groups format\n";
        return;
    }

    const json* target_group = nullptr;
    for (const auto& group : groups_root["groups"]) {
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

    json templates_root;
    if (!fs::exists(file_path_templates)) {
        std::cerr << "Templates file not found\n";
        return;
    }
    {
        std::ifstream instream(file_path_templates);
        if (!instream.good()) {
            std::cerr << "Failed to open templates file\n";
            return;
        }
        instream >> templates_root;
    }

    if (!templates_root.contains("templates") ||
        !templates_root["templates"].is_array()) {
        std::cerr << "Invalid templates format\n";
        return;
    }

    const json* target_template = nullptr;
    for (const auto& tmpl : templates_root["templates"]) {
        if (tmpl.contains("name") && tmpl["name"].is_string() &&
            tmpl["name"] == options.template_name) {
            target_template = &tmpl;
            break;
        }
    }

    if (target_template == nullptr) {
        std::cerr << "Template not found: " << options.template_name << '\n';
        return;
    }

    if (!target_template->contains("text") ||
        !(*target_template)["text"].is_string()) {
        std::cerr << "Template missing text\n";
        return;
    }

    std::string template_text = (*target_template)["text"];

    std::vector<std::string> placeholders;
    size_t pos = 0;
    while ((pos = template_text.find('[', pos)) != std::string::npos) {
        size_t end = template_text.find(']', pos);
        if (end != std::string::npos) {
            placeholders.push_back(template_text.substr(pos + 1, end - pos - 1));
            pos = end + 1;
        } else {
            break;
        }
    }

    const auto& members = (*target_group)["members"];
    size_t num_placeholders = placeholders.size();
    if (options.variables.size() != members.size() * num_placeholders) {
        std::cerr << "Mismatch: variables size does not match number of "
                     "members * placeholders\n";
        return;
    }

    for (size_t i = 0; i < members.size(); ++i) {
        const auto& member = members[i];
        if (!member.is_string()) {
            continue;
        }

        std::string message_text = template_text;
        for (size_t j = 0; j < num_placeholders; ++j) {
            std::string placeholder = "[" + placeholders[j] + "]";
            size_t var_index = (i * num_placeholders) + j;
            size_t pos = 0;
            while ((pos = message_text.find(placeholder, pos)) != std::string::npos) {
                message_text.replace(pos, placeholder.size(),
                                     options.variables[var_index]);
                pos += options.variables[var_index].size();
            }
        }
        const std::string email = member.get<std::string>();

        try {
            const std::string user_id =
                client.users().byEmail(email).get().value().id.value();

            auto myself = teams::ConversationMember{
                .id = std::string{client.me().get().value().id.value()},
                .roles = std::vector<std::string>{"owner"}};

            auto other = teams::ConversationMember{
                .id = user_id, .roles = std::vector<std::string>{"owner"}};

            auto chat = teams::Chat{
                .type = "oneOnOne",
                .members =
                    std::vector<teams::priv::ConversationMember>{myself, other}};

            auto created_chat = client.chats().post(chat);
            auto chat_id = created_chat.value().id.value();

            auto msg = teams::Message{
                .body = teams::priv::ItemBody{.content = message_text,
                                              .content_type = "text"}};
            auto const result = client.chats().byId(chat_id).messages().post(msg);

            std::cout << "Message sent to " << email << '\n';
        } catch (const std::exception& e) {
            std::cerr << "Failed to send to " << email << ": " << e.what()
                      << '\n';
        }
    }
}

}  // namespace callbacks::automatization::Template
