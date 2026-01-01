#pragma once
#include <httplib.h>

#include <vector>

namespace teams {
using HttpHeader = httplib::Headers;
using HttpClient = httplib::Client;
using HttpResult = httplib::Result;
using HttpResponse = httplib::Response;
using HttpError = httplib::Error;
using HttpStatus = httplib::StatusCode;
using HttpBody = std::string;

template <typename ResourceType>
using Collection = std::vector<ResourceType>;

using Token = std::string;

using RefreshToken = Token;
using AccessToken = Token;
using Scopes = std::string;

using ID = std::string;
using URL = std::string;

}  // namespace teams
