cmake_minimum_required(VERSION 3.10)
project(PhoenixProj)
set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0079 NEW)
add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(ABSL_PROPAGATE_CXX_STD ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
# set(CMAKE_AUTOMOC ON)  # Enable automatic MOC (Meta-Object Compiler)
# set(CMAKE_AUTOUIC ON)  # Enable automatic UIC (User Interface Compiler)
# set(CMAKE_AUTORCC ON)  # Enable automatic RCC (Resource Compiler)

add_subdirectory(proto)
add_subdirectory(src)

# adding Qt libraries
# find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
include_directories(${Qt5_INCLUDE_DIRS})
# target_link_libraries(Phoenix PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)

# fetching nlohmann/json
include(FetchContent)
FetchContent_Declare(json
URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)
include_directories(${json_SOURCE_DIR}/include)

FetchContent_Declare(
  poco
  GIT_REPOSITORY "https://github.com/pocoproject/poco.git"
  GIT_TAG        "poco-1.13.2-release"
  GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(poco)
include_directories(${poco_SOURCE_DIR}/Net/include/Poco/Net)

