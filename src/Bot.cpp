#include "Bot.hpp"
#include <iostream>
#include <stdexcept>

namespace BotNation {

Bot::Bot(const std::string& apiBaseUrl) 
    : _apiClient(std::make_unique<ApiClient>(apiBaseUrl)), _initialized(false) {
}

Bot::~Bot() = default;

void Bot::Initialize() {
    std::cout << "Initializing bot with API: " << _apiClient->GetBaseUrl() << std::endl;
    _initialized = true;
}

void Bot::ValidateInitialization() const {
    if (!_initialized) {
        throw std::runtime_error("Bot not initialized. Call Initialize() first.");
    }
}

void Bot::Run() {
    ValidateInitialization();
    std::cout << "Bot is running..." << std::endl;
}

nlohmann::json Bot::FetchData(const std::string& endpoint) {
    ValidateInitialization();
    return _apiClient->Get(endpoint);
}

nlohmann::json Bot::SubmitData(const std::string& endpoint, const nlohmann::json& data) {
    ValidateInitialization();
    return _apiClient->Post(endpoint, data);
}

} // namespace BotNation
