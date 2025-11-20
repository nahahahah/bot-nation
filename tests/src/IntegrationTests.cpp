#include <snitch/snitch.hpp>
#include "Bot.hpp"
#include "ApiClient.hpp"
#include "TestHelpers.hpp"
#include <memory>

using namespace BotNation;
using namespace BotNation::Testing;

TEST_CASE("Bot - Initialization", "[integration][Bot]") {
    SECTION("Bot can be created") {
        auto apiClient = std::make_shared<ApiClient>("https://api.example.com");
        Bot bot(apiClient);
        // Initialization will fail without a real server, so we expect an exception
        REQUIRE_THROWS_AS(bot.Initialize(), std::exception);
    }
    
    SECTION("Bot requires initialization before running") {
        auto apiClient = std::make_shared<ApiClient>("https://api.example.com");
        Bot bot(apiClient);
        REQUIRE_THROWS_AS(bot.Run(), std::runtime_error);
    }
}

TEST_CASE("Bot - Data operations require initialization", "[integration][Bot]") {
    SECTION("FetchData requires initialization") {
        auto apiClient = std::make_shared<ApiClient>("https://api.example.com");
        Bot bot(apiClient);
        REQUIRE_THROWS_AS(bot.FetchData("/test"), std::runtime_error);
    }
    
    SECTION("SubmitData requires initialization") {
        auto apiClient = std::make_shared<ApiClient>("https://api.example.com");
        Bot bot(apiClient);
        nlohmann::json data = CreateTestData("key", "value");
        REQUIRE_THROWS_AS(bot.SubmitData("/test", data), std::runtime_error);
    }
}
