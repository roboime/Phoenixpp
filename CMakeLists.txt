cmake_minimum_required(VERSION 3.28)
project(Phoenixpp VERSION 1.0
        DESCRIPTION "RoboIME's SSL Robot soccer software"
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
############# Generating protobuf files #############
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
############## Adding Boost Library #############
find_package(Boost 1.85 REQUIRED COMPONENTS atomic)
include_directories(${Boost_INCLUDE_DIRS})
############## Adding QT LIBRARY #############
# set(CMAKE_PREFIX_PATH "C:/Users/lucas/.vcpkg-clion/vcpkg3/installed/x64-windows")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)
############# Source and Executable #############
include_directories(include)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/resources/qt)
add_executable(Phoenixpp
    apps/Phoenixpp.cpp
    src/qt/gui.cpp
    resources/qt/gui.ui
    include/Phoenixpp/qt/gui.h
)
#target_link_libraries(Phoenixpp PRIVATE ssl_proto)
add_subdirectory(src)
target_link_libraries(Phoenixpp PRIVATE core)
target_link_libraries(Phoenixpp PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
target_link_libraries(Phoenixpp PRIVATE ${Boost_LIBRARIES})
if (WIN32) # AND NOT DEFINED CMAKE_TOOLCHAIN_FILE
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}/..")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
############# Tests #############
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()



