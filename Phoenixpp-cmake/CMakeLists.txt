cmake_minimum_required(VERSION 3.10)
project(PhoenixProj)
set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0079 NEW)
add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(ABSL_PROPAGATE_CXX_STD ON)

add_subdirectory(src)
add_subdirectory(proto)

# if(NOT DEFINED QT_QMAKE_EXECUTABLE)
# adding Qt libraries
find_package(Qt5 COMPONENTS Core Network REQUIRED)
include_directories(${Qt5_INCLUDE_DIRS})
target_link_libraries(UdpVision PUBLIC Qt5::Core Qt5::Network)

#else()
#    cmake_policy(SET CMP0135 NEW)
#endif()

# cmake_policy(SET CMP0135 NEW)

# fetching nlohmann/json
include(FetchContent)
FetchContent_Declare(json
URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)
include_directories(${json_SOURCE_DIR}/include)