#pragma once
#include <httplib.h>

#include <vector>

using HttpHeader = httplib::Headers;
using HttpClient = httplib::Client;

template <typename ResourceType>
using Collection = std::vector<ResourceType>;

using Token = std::string;

using RefreshToken = Token;
using AccessToken = Token;

using ID = std::string;
using URL = std::string;
