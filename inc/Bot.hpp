#ifndef BOT_HPP
#define BOT_HPP

#include "ApiClient.hpp"
#include <string>
#include <memory>

namespace BotNation {

class Bot {
public:
    Bot(const std::string& apiBaseUrl);
    ~Bot();
    
    void Initialize();
    void Run();
    nlohmann::json FetchData(const std::string& endpoint);
    nlohmann::json SubmitData(const std::string& endpoint, const nlohmann::json& data);

private:
    std::unique_ptr<ApiClient> _apiClient;
    bool _initialized;
    
    void ValidateInitialization() const;
};

} // namespace BotNation

#endif // BOT_HPP
