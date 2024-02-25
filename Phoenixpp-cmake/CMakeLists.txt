cmake_minimum_required(VERSION 3.10)
project(PhoenixProj)
set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0079 NEW)
add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(utils)
add_subdirectory(implementations)
add_subdirectory(src)
add_subdirectory(proto)

# adding Qt libraries
find_package(Qt5 COMPONENTS Core Network REQUIRED)
target_link_libraries(Phoenix PRIVATE Qt5::Core Qt5::Network)

include(FetchContent)

# fetching nlohmann/json
FetchContent_Declare(json
URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)
include_directories(${json_SOURCE_DIR}/include)

#add_library(nlohmann_json INTERFACE)
#target_include_directories(nlohmann_json INTERFACE ${json_SOURCE_DIR}/include)
target_link_libraries(Phoenix PRIVATE nlohmann_json)