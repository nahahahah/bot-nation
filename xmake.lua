-- Set project version and languages
set_project("bot-nation")
set_version("1.0.0")
set_languages("c++20")

-- Add required packages
add_requires("libcurl", "nlohmann_json", "snitch")

-- Main executable target
target("bot-nation")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("inc")
    add_packages("libcurl", "nlohmann_json")
    set_warnings("all")
target_end()

-- Test target
target("bot-nation-tests")
    set_kind("binary")
    add_files("tests/src/*.cpp")
    add_files("src/ApiClient.cpp", "src/Bot.cpp")
    add_includedirs("inc", "tests/inc")
    add_packages("libcurl", "nlohmann_json", "snitch")
    set_warnings("all")
target_end()
