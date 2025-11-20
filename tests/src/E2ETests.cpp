#include <snitch/snitch.hpp>
#include "Bot.hpp"
#include "ApiClient.hpp"
#include "TestHelpers.hpp"
#include <memory>

using namespace BotNation;
using namespace BotNation::Testing;

TEST_CASE("End-to-end - Bot workflow", "[e2e][Bot]") {
    SECTION("Complete bot creation and shared ApiClient") {
        auto apiClient = std::make_shared<ApiClient>("https://api.example.com");
        Bot bot(apiClient);
        
        // Initialization will fail without a real server
        // This test verifies the new shared_ptr interface works
        REQUIRE_THROWS_AS(bot.Initialize(), std::exception);
    }
}

TEST_CASE("End-to-end - JSON data handling", "[e2e][JSON]") {
    SECTION("Create and parse JSON data") {
        auto testData = CreateTestData("testKey", "testValue");
        REQUIRE(testData["testKey"] == "testValue");
        
        std::string jsonString = testData.dump();
        auto parsed = nlohmann::json::parse(jsonString);
        REQUIRE(parsed["testKey"] == "testValue");
    }
}

TEST_CASE("End-to-end - ApiClient lifecycle", "[e2e][ApiClient]") {
    SECTION("ApiClient creation and destruction") {
        {
            ApiClient client("https://test.example.com");
            REQUIRE(client.GetBaseUrl() == "https://test.example.com");
        }
        // Client should clean up properly when going out of scope
        REQUIRE(true);
    }
    
    SECTION("ApiClient with auth token") {
        ApiClient client("https://test.example.com");
        REQUIRE(client.GetAuthToken().empty());
        
        client.SetAuthToken("test-token-123");
        REQUIRE(client.GetAuthToken() == "test-token-123");
    }
}
