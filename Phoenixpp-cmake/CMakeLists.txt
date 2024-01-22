cmake_minimum_required(VERSION 3.10)
project(PhoenixProj)
set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0079 NEW)

add_subdirectory(src)
add_subdirectory(utils)
add_subdirectory(implementations)
add_subdirectory(proto)

# adding Qt libraries
find_package(Qt5 COMPONENTS Core Network REQUIRED)
target_link_libraries(Phoenix PRIVATE Qt5::Core Qt5::Network)

include(FetchContent)

# fetching nlohmann/json
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(Phoenix PRIVATE nlohmann_json::nlohmann_json)
