#include "Bot.hpp"
#include "ApiClient.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <vector>

int main(int argc, char* argv[]) {
    try {
        std::string apiUrl = "https://api.example.com";
        
        // Allow API URL override from command line
        if (argc > 1) {
            apiUrl = argv[1];
        }
        
        std::cout << "Bot Nation - C++20 API Client" << std::endl;
        std::cout << "==============================" << std::endl;
        
        // Create shared ApiClient that can be shared among multiple bots
        auto apiClient = std::make_shared<BotNation::ApiClient>(apiUrl);
        
        // Demonstrate spawning multiple bots using the same shared ApiClient
        std::cout << "\n=== Spawning Multiple Bots ===" << std::endl;
        std::vector<std::unique_ptr<BotNation::Bot>> bots;
        
        for (int i = 0; i < 3; ++i) {
            std::cout << "\n--- Creating Bot #" << (i + 1) << " ---" << std::endl;
            auto bot = std::make_unique<BotNation::Bot>(apiClient);
            try {
                bot->Initialize();
                bot->Run();
                bots.push_back(std::move(bot));
            } catch (const std::exception& e) {
                std::cout << "Note: Bot initialization expected to fail without real server: " << e.what() << std::endl;
            }
        }
        
        std::cout << "\n=== All Bots Created ===" << std::endl;
        std::cout << "Total bots successfully initialized: " << bots.size() << std::endl;
        
        // Example API call with first bot (if any succeeded)
        if (!bots.empty()) {
            std::cout << "\nAttempting to fetch data from /api/status with first bot..." << std::endl;
            try {
                auto response = bots[0]->FetchData("/api/status");
                std::cout << "Response: " << response.dump(2) << std::endl;
            } catch (const std::exception& e) {
                std::cout << "API call failed (expected if endpoint doesn't exist): " << e.what() << std::endl;
            }
        }
        
        std::cout << "\nBot execution completed successfully." << std::endl;
        std::cout << "All bots will logout on destruction..." << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
