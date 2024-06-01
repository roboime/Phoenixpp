cmake_minimum_required(VERSION 3.28)
project(Phoenixpp VERSION 1.0
        DESCRIPTION "RoboIME's SSL Robot soccer software"
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include_directories(include)

# Generating protobuf files
find_package(Protobuf CONFIG REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(PROTO_FILES
        ${CMAKE_SOURCE_DIR}/proto/game_event.proto
        ${CMAKE_SOURCE_DIR}/proto/grSim_Commands.proto
        ${CMAKE_SOURCE_DIR}/proto/grSim_Packet.proto
        ${CMAKE_SOURCE_DIR}/proto/grSim_Replacement.proto
        ${CMAKE_SOURCE_DIR}/proto/messages_robocup_ssl_detection.proto
        ${CMAKE_SOURCE_DIR}/proto/messages_robocup_ssl_detection_tracked.proto
        ${CMAKE_SOURCE_DIR}/proto/messages_robocup_ssl_geometry.proto
        ${CMAKE_SOURCE_DIR}/proto/messages_robocup_ssl_geometry_legacy.proto
        ${CMAKE_SOURCE_DIR}/proto/messages_robocup_ssl_refbox_log.proto
        ${CMAKE_SOURCE_DIR}/proto/messages_robocup_ssl_wrapper.proto
        ${CMAKE_SOURCE_DIR}/proto/messages_robocup_ssl_wrapper_legacy.proto
        ${CMAKE_SOURCE_DIR}/proto/rcon.proto
        ${CMAKE_SOURCE_DIR}/proto/referee.proto
        ${CMAKE_SOURCE_DIR}/proto/savestate.proto
)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
add_library(ssl_proto STATIC ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(ssl_proto PUBLIC protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

add_executable(Phoenixpp apps/PhoenixCLI/PhoenixCli.cpp)

target_link_libraries(Phoenixpp PRIVATE ssl_proto)
#find_package(nlohmann CONFIG REQUIRED)
#target_link_libraries(Phoenixpp PRIVATE nlohmann::json)
add_subdirectory(src)
target_link_libraries(Phoenixpp PRIVATE base_component)
target_link_libraries(Phoenixpp PRIVATE udpVision)
target_link_libraries(Phoenixpp PRIVATE baseUI)

