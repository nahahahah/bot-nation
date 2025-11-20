#include "TestHelpers.hpp"

namespace BotNation {
namespace Testing {

std::string CreateMockJsonResponse(const std::string& status, const std::string& message) {
    nlohmann::json response;
    response["status"] = status;
    response["message"] = message;
    return response.dump();
}

nlohmann::json CreateTestData(const std::string& key, const std::string& value) {
    nlohmann::json data;
    data[key] = value;
    return data;
}

} // namespace Testing
} // namespace BotNation
