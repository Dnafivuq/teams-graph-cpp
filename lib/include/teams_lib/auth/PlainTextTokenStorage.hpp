#pragma once

#include <httplib.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <teams_lib/auth/TokenStorageProvider.hpp>

namespace teams {
namespace priv {

class PlainTextTokenStorage
    : public TokenStorageProvider<PlainTextTokenStorage> {
    friend TokenStorageProvider;

public:
    PlainTextTokenStorage(std::filesystem::path file_path = ".token")
        : TokenStorageProvider<PlainTextTokenStorage>(),
          file_path_(std::move(file_path)) {}

private:
    std::optional<RefreshToken> loadImpl() const {
        std::ifstream file_handle(file_path_);
        if (!file_handle.is_open()) {
            return std::nullopt;
            // throw std::runtime_error("Token file could not be opened");
        }
        return RefreshToken(std::istreambuf_iterator<char>{file_handle}, {});
    }

    // TODO: add status returning
    void storeImpl(const RefreshToken& token) const {
        std::ofstream file_handle(file_path_);
        if (file_handle.is_open()) {
            file_handle << token;
        } else {
            std::cout << "[LOG] Unable to store token\n";
            // throw std::runtime_error("Token file could not be opened");
        }
    }

    std::filesystem::path file_path_;
};
}  // namespace priv
using PlainTextTokenStorage = priv::PlainTextTokenStorage;
}  // namespace teams
