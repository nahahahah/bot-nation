#include "Bot.hpp"
#include <iostream>
#include <stdexcept>
#include <random>
#include <sstream>

namespace BotNation {

Bot::Bot(std::shared_ptr<ApiClient> apiClient) 
    : _apiClient(apiClient), _initialized(false) {
    // Generate a unique username for this bot instance
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    std::stringstream ss;
    ss << "bot_" << dis(gen);
    _username = ss.str();
}

Bot::~Bot() {
    // Logout on destruction
    if (_initialized) {
        try {
            std::cout << "Logging out bot: " << _username << std::endl;
            _apiClient->Post("/api/logout", nlohmann::json::object());
        } catch (const std::exception& e) {
            std::cerr << "Warning: Failed to logout: " << e.what() << std::endl;
        }
    }
}

void Bot::Initialize() {
    std::cout << "Initializing bot with API: " << _apiClient->GetBaseUrl() << std::endl;
    
    // Try to register first
    try {
        nlohmann::json registerData = {
            {"username", _username},
            {"password", "password123"}
        };
        
        std::cout << "Attempting to register user: " << _username << std::endl;
        auto registerResponse = _apiClient->Post("/api/register", registerData);
        
        // Registration successful
        if (registerResponse.contains("token")) {
            std::string token = registerResponse["token"];
            _apiClient->SetAuthToken(token);
            std::cout << "Registration successful for: " << _username << std::endl;
        }
    } catch (const std::exception& e) {
        // Registration failed, try to login
        std::cout << "Registration failed (user may already exist), attempting login..." << std::endl;
        
        try {
            nlohmann::json loginData = {
                {"username", _username},
                {"password", "password123"}
            };
            
            auto loginResponse = _apiClient->Post("/api/login", loginData);
            
            if (loginResponse.contains("token")) {
                std::string token = loginResponse["token"];
                _apiClient->SetAuthToken(token);
                std::cout << "Login successful for: " << _username << std::endl;
            } else {
                throw std::runtime_error("Login response missing token");
            }
        } catch (const std::exception& loginError) {
            throw std::runtime_error(std::string("Failed to login: ") + loginError.what());
        }
    }
    
    // Verify we are connected by calling /api/me
    try {
        std::cout << "Verifying connection with /api/me..." << std::endl;
        auto meResponse = _apiClient->Get("/api/me");
        
        if (meResponse.contains("username")) {
            std::cout << "Connection verified. Logged in as: " << meResponse["username"] << std::endl;
        }
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to verify connection: ") + e.what());
    }
    
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
