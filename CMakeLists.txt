cmake_minimum_required(VERSION 3.14) # FetchContent needs at least 3.11
project(daggr-cli VERSION 0.1.0 LANGUAGES CXX)

# Set C++17 standard (required for CLI11 and modern JSON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Networking (System Dependency) ---
# We use find_package for curl because it's a compiled system library
find_package(CURL REQUIRED)

# --- 2. External Header-Only Libraries (Automated Download) ---
include(FetchContent)

# Add CLI11 for argument parsing
FetchContent_Declare(
  cli11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG      v2.4.2
)

# Add nlohmann_json for API response parsing
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG      v3.11.3
)

# Make them available to the project
FetchContent_MakeAvailable(cli11 json)

# --- 3. Executable Setup ---
add_executable(daggr-cli main.cpp)

# Link everything together
target_link_libraries(daggr-cli PRIVATE
    CURL::libcurl
    CLI11::CLI11
    nlohmann_json::nlohmann_json
)
