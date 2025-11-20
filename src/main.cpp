#include "Bot.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        std::string apiUrl = "https://api.example.com";
        
        // Allow API URL override from command line
        if (argc > 1) {
            apiUrl = argv[1];
        }
        
        std::cout << "Bot Nation - C++20 API Client" << std::endl;
        std::cout << "==============================" << std::endl;
        
        BotNation::Bot bot(apiUrl);
        bot.Initialize();
        bot.Run();
        
        // Example API call
        std::cout << "\nAttempting to fetch data from /api/status..." << std::endl;
        try {
            auto response = bot.FetchData("/api/status");
            std::cout << "Response: " << response.dump(2) << std::endl;
        } catch (const std::exception& e) {
            std::cout << "API call failed (expected if endpoint doesn't exist): " << e.what() << std::endl;
        }
        
        std::cout << "\nBot execution completed successfully." << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
