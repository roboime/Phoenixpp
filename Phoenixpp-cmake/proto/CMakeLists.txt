include(FetchContent)
#fetching protobuf
FetchContent_Declare(protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG        v4.25.2

)
FetchContent_MakeAvailable(protobuf)
FetchContent_GetProperties(protobuf SOURCE_DIR Protobuf_SOURCE_DIR)
FetchContent_GetProperties(protobuf INCLUDE_DIRS Protobuf_INCLUDE_DIRS)

include(${Protobuf_SOURCE_DIR}/cmake/protobuf-generate.cmake)
include_directories(
    ${Protobuf_SOURCE_DIR}/src
    ${Protobuf_SOURCE_DIR}/third_party/abseil-cpp
    ${Protobuf_SOURCE_DIR}/third_party/googletest/googletest/include
    ${Protobuf_SOURCE_DIR}/third_party/googletest/googlemock/include
    ${Protobuf_SOURCE_DIR}/third_party/jsoncpp/include
)

add_library(ssl_proto
    OBJECT
    game_event.proto
    grSim_Commands.proto
    grSim_Packet.proto
    grSim_Replacement.proto
    messages_robocup_ssl_detection.proto
    messages_robocup_ssl_detection_tracked.proto
    messages_robocup_ssl_geometry.proto
    messages_robocup_ssl_geometry_legacy.proto
    messages_robocup_ssl_refbox_log.proto
    messages_robocup_ssl_wrapper.proto
    messages_robocup_ssl_wrapper_legacy.proto
    rcon.proto
    referee.proto
    savestate.proto
)
target_link_libraries(ssl_proto PUBLIC protobuf::libprotobuf)

target_include_directories(
    ssl_proto PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
    ${INCLUDE_DIRECTORIES}
)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate(
    TARGET ssl_proto
    LANGUAGE cpp
    IMPORT_DIRS  ${CMAKE_SOURCE_DIR}/proto
    PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(Phoenix PRIVATE ssl_proto)
