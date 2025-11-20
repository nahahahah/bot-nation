# Bot Nation

C++20 bot that makes API calls to the Code Commit and Conquer app.

## Overview

Bot Nation is a modern C++20 application designed to interact with REST APIs. It demonstrates best practices in C++ development including proper error handling, modern C++ features, and comprehensive testing.

## Features

- **Modern C++20**: Utilizes the latest C++ standard features
- **HTTP Client**: Uses curlpp for making HTTP GET and POST requests
- **JSON Processing**: Leverages nlohmann_json for parsing and serializing JSON data
- **Comprehensive Testing**: Includes unit, integration, and end-to-end tests using Snitch framework
- **Clean Architecture**: Follows SOLID principles with clear separation of concerns

## Project Structure

```
bot-nation/
├── inc/                    # Public header files
│   ├── ApiClient.hpp      # HTTP client for API calls
│   └── Bot.hpp            # Main bot class
├── src/                    # Implementation files
│   ├── ApiClient.cpp      # ApiClient implementation
│   ├── Bot.cpp            # Bot implementation
│   └── main.cpp           # Application entry point
├── tests/                  # Test files
│   ├── inc/               # Test header files
│   │   └── TestHelpers.hpp
│   └── src/               # Test implementation files
│       ├── TestHelpers.cpp
│       ├── UnitTests.cpp
│       ├── IntegrationTests.cpp
│       └── E2ETests.cpp
├── xmake.lua              # Build configuration
└── README.md              # This file
```

## Prerequisites

- C++20 compatible compiler (GCC 10+, Clang 11+, or MSVC 2019+)
- Xmake build system
- Internet connection (for downloading dependencies)

## Dependencies

The project uses the following libraries (automatically managed by Xmake):
- **libcurl**: Industry-standard library for making HTTP requests
- **nlohmann_json**: Modern JSON library for C++
- **snitch**: Lightweight C++ testing framework

## Building

### Install Xmake

If you don't have Xmake installed:

```bash
# On Linux/macOS
curl -fsSL https://xmake.io/shget.text | bash

# On Windows (PowerShell)
Invoke-Expression (Invoke-Webrequest 'https://xmake.io/psget.text' -UseBasicParsing).Content
```

### Build the Project

```bash
# Configure and build
xmake

# Or build in release mode
xmake f -m release
xmake
```

## Running

### Run the Application

```bash
# Run with default API URL (https://api.example.com)
xmake run bot-nation

# Run with custom API URL
xmake run bot-nation https://your-api-url.com
```

### Run Tests

```bash
# Build and run all tests
xmake build bot-nation-tests
xmake run bot-nation-tests

# Run specific test categories
xmake run bot-nation-tests "[unit]"        # Run only unit tests
xmake run bot-nation-tests "[integration]" # Run only integration tests
xmake run bot-nation-tests "[e2e]"         # Run only end-to-end tests
```

## Code Style Guidelines

The project follows these coding conventions:

- **Classes and Methods**: PascalCase (e.g., `ApiClient`, `FetchData`)
- **Private Attributes**: camelCase with underscore prefix (e.g., `_baseUrl`, `_initialized`)
- **Curly Braces**: Same line opening (K&R style)
- **Header Guards**: Use `#ifndef`/`#define`/`#endif` pattern
- **Namespaces**: Code organized under `BotNation` namespace

## Functionality

### ApiClient

The `ApiClient` class provides a simple interface for making HTTP requests:

```cpp
#include "ApiClient.hpp"

BotNation::ApiClient client("https://api.example.com");

// GET request
auto response = client.Get("/endpoint");

// POST request
nlohmann::json data = {{"key", "value"}};
auto response = client.Post("/endpoint", data);
```

### Bot

The `Bot` class orchestrates the application logic with authentication support:

```cpp
#include "Bot.hpp"
#include "ApiClient.hpp"
#include <memory>

// Create shared ApiClient
auto apiClient = std::make_shared<BotNation::ApiClient>("https://api.example.com");

// Create bot with shared ApiClient
BotNation::Bot bot(apiClient);

// Initialize will:
// 1. Try to register at /api/register
// 2. Fall back to /api/login if account exists
// 3. Verify connection with /api/me
bot.Initialize();
bot.Run();

// Fetch data (authenticated with token)
auto data = bot.FetchData("/api/status");

// Submit data (authenticated with token)
nlohmann::json payload = {{"action", "submit"}};
auto result = bot.SubmitData("/api/data", payload);

// Bot will automatically logout on destruction via /api/logout
```

#### Multiple Bot Support

You can spawn multiple bots sharing the same ApiClient:

```cpp
auto apiClient = std::make_shared<BotNation::ApiClient>("https://api.example.com");

std::vector<std::unique_ptr<BotNation::Bot>> bots;
for (int i = 0; i < 5; ++i) {
    auto bot = std::make_unique<BotNation::Bot>(apiClient);
    bot->Initialize();  // Each bot gets unique username
    bots.push_back(std::move(bot));
}
// All bots share the same ApiClient but have independent authentication
```

## Development

### Adding New Features

1. Add header files to `inc/` directory
2. Add implementation files to `src/` directory
3. Update `xmake.lua` if adding new dependencies
4. Add corresponding tests in `tests/src/`

### Testing

The project includes three types of tests:

- **Unit Tests**: Test individual components in isolation
- **Integration Tests**: Test component interactions
- **End-to-End Tests**: Test complete workflows

All tests use the Snitch framework and follow the naming pattern:
- `UnitTests.cpp` - Unit tests
- `IntegrationTests.cpp` - Integration tests
- `E2ETests.cpp` - End-to-end tests

## Troubleshooting

### Build Issues

If you encounter build issues:

```bash
# Clean and rebuild
xmake clean
xmake

# Force package update
xmake f -c
xmake
```

### Dependency Issues

If dependencies fail to download:

```bash
# Check Xmake package repository
xmake repo -l

# Update package repository
xmake repo -u
```

## License

This project is part of the Code Commit and Conquer challenge.

## Contributing

When contributing, please:
1. Follow the established code style guidelines
2. Add tests for new functionality
3. Update documentation as needed
4. Ensure all tests pass before submitting
