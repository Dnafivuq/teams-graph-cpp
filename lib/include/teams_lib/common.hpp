#pragma once
#include <httplib.h>

#include <vector>

namespace teams {
using HttpHeader = httplib::Headers;
using HttpClient = httplib::Client;
using HttpResult = httplib::Result;
using HttpError = httplib::Error;
using HttpCode = int;
using HttpBody = std::string;

constexpr int HTTP_SUCCESS = 200;
constexpr int HTTP_FAILURE = 300;

template <typename ResourceType>
using Collection = std::vector<ResourceType>;

using Token = std::string;

using RefreshToken = Token;
using AccessToken = Token;
using Scopes = std::string;

using ID = std::string;
using URL = std::string;

}  // namespace teams
