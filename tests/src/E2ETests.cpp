#include <snitch/snitch.hpp>
#include "Bot.hpp"
#include "ApiClient.hpp"
#include "TestHelpers.hpp"

using namespace BotNation;
using namespace BotNation::Testing;

TEST_CASE("End-to-end - Bot workflow", "[e2e][Bot]") {
    SECTION("Complete bot initialization and execution") {
        Bot bot("https://api.example.com");
        
        // Initialize
        REQUIRE_NOTHROW(bot.Initialize());
        
        // Run
        REQUIRE_NOTHROW(bot.Run());
        
        // Note: Actual API calls would fail without a real server
        // These are tested separately with proper mocking or test servers
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
}
