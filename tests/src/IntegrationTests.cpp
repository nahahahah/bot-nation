#include <snitch/snitch.hpp>
#include "Bot.hpp"
#include "TestHelpers.hpp"

using namespace BotNation;
using namespace BotNation::Testing;

TEST_CASE("Bot - Initialization", "[integration][Bot]") {
    SECTION("Bot can be created") {
        Bot bot("https://api.example.com");
        REQUIRE_NOTHROW(bot.Initialize());
    }
    
    SECTION("Bot requires initialization before running") {
        Bot bot("https://api.example.com");
        REQUIRE_THROWS_AS(bot.Run(), std::runtime_error);
    }
    
    SECTION("Bot can run after initialization") {
        Bot bot("https://api.example.com");
        bot.Initialize();
        REQUIRE_NOTHROW(bot.Run());
    }
}

TEST_CASE("Bot - Data operations require initialization", "[integration][Bot]") {
    SECTION("FetchData requires initialization") {
        Bot bot("https://api.example.com");
        REQUIRE_THROWS_AS(bot.FetchData("/test"), std::runtime_error);
    }
    
    SECTION("SubmitData requires initialization") {
        Bot bot("https://api.example.com");
        nlohmann::json data = CreateTestData("key", "value");
        REQUIRE_THROWS_AS(bot.SubmitData("/test", data), std::runtime_error);
    }
}
