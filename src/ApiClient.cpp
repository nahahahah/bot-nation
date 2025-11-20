#include "ApiClient.hpp"
#include <curl/curl.h>
#include <sstream>
#include <stdexcept>

namespace BotNation {

// Helper callback for CURL to write response data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

ApiClient::ApiClient(const std::string& baseUrl) : _baseUrl(baseUrl) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

ApiClient::~ApiClient() {
    curl_global_cleanup();
}

void ApiClient::SetBaseUrl(const std::string& url) {
    _baseUrl = url;
}

std::string ApiClient::GetBaseUrl() const {
    return _baseUrl;
}

void ApiClient::SetAuthToken(const std::string& token) {
    _authToken = token;
}

std::string ApiClient::GetAuthToken() const {
    return _authToken;
}

std::string ApiClient::MakeRequest(const std::string& method, const std::string& endpoint, const std::string& body) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }
    
    std::string responseString;
    std::string fullUrl = _baseUrl + endpoint;
    
    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);
    
    struct curl_slist* headers = nullptr;
    
    // Add auth token if available
    if (!_authToken.empty()) {
        std::string authHeader = "X-Api-Token: " + _authToken;
        headers = curl_slist_append(headers, authHeader.c_str());
    }
    
    if (method == "POST") {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    } else if (headers) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }
    
    CURLcode res = curl_easy_perform(curl);
    
    if (headers) {
        curl_slist_free_all(headers);
    }
    
    if (res != CURLE_OK) {
        std::string error = std::string("CURL error: ") + curl_easy_strerror(res);
        curl_easy_cleanup(curl);
        throw std::runtime_error(error);
    }
    
    curl_easy_cleanup(curl);
    return responseString;
}

nlohmann::json ApiClient::Get(const std::string& endpoint) {
    std::string response = MakeRequest("GET", endpoint);
    if (response.empty()) {
        return nlohmann::json::object();
    }
    return nlohmann::json::parse(response);
}

nlohmann::json ApiClient::Post(const std::string& endpoint, const nlohmann::json& data) {
    std::string body = data.dump();
    std::string response = MakeRequest("POST", endpoint, body);
    if (response.empty()) {
        return nlohmann::json::object();
    }
    return nlohmann::json::parse(response);
}

} // namespace BotNation
