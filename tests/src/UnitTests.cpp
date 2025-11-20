#include <snitch/snitch.hpp>
#include "ApiClient.hpp"
#include "TestHelpers.hpp"

using namespace BotNation;
using namespace BotNation::Testing;

TEST_CASE("ApiClient - Constructor and basic operations", "[unit][ApiClient]") {
    SECTION("Create ApiClient with base URL") {
        ApiClient client("https://api.example.com");
        REQUIRE(client.GetBaseUrl() == "https://api.example.com");
    }
    
    SECTION("Set and get base URL") {
        ApiClient client("https://api.example.com");
        client.SetBaseUrl("https://newapi.example.com");
        REQUIRE(client.GetBaseUrl() == "https://newapi.example.com");
    }
}

TEST_CASE("ApiClient - URL construction", "[unit][ApiClient]") {
    SECTION("Base URL is properly stored") {
        std::string baseUrl = "https://test.api.com";
        ApiClient client(baseUrl);
        REQUIRE(client.GetBaseUrl() == baseUrl);
    }
}
