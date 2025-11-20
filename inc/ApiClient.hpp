#ifndef API_CLIENT_HPP
#define API_CLIENT_HPP

#include <string>
#include <memory>
#include <nlohmann/json.hpp>

namespace BotNation {

class ApiClient {
public:
    ApiClient(const std::string& baseUrl);
    ~ApiClient();
    
    nlohmann::json Get(const std::string& endpoint);
    nlohmann::json Post(const std::string& endpoint, const nlohmann::json& data);
    
    void SetBaseUrl(const std::string& url);
    std::string GetBaseUrl() const;
    
    void SetAuthToken(const std::string& token);
    std::string GetAuthToken() const;

private:
    std::string _baseUrl;
    std::string _authToken;
    
    std::string MakeRequest(const std::string& method, const std::string& endpoint, const std::string& body = "");
};

} // namespace BotNation

#endif // API_CLIENT_HPP
