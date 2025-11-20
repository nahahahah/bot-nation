#ifndef TEST_HELPERS_HPP
#define TEST_HELPERS_HPP

#include <string>
#include <nlohmann/json.hpp>

namespace BotNation {
namespace Testing {

// Mock API response for testing
std::string CreateMockJsonResponse(const std::string& status, const std::string& message);

// Helper to create test JSON data
nlohmann::json CreateTestData(const std::string& key, const std::string& value);

} // namespace Testing
} // namespace BotNation

#endif // TEST_HELPERS_HPP
