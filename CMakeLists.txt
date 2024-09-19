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
if (Protobuf_FOUND)
    message(STATUS "Protobuf found: ${Protobuf_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Protobuf not found")
endif()
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(GENERATED_PROTO_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_PROTO_DIR})
include_directories(${GENERATED_PROTO_DIR})
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
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES} PROTOC_OUT_DIR ${GENERATED_PROTO_DIR})
add_library(ssl_proto STATIC ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(ssl_proto PUBLIC protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
############## Adding QT LIBRARY #############

set(QT6_DIR "C:/Qt/6.7.2/mingw_64/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64" ${CMAKE_PREFIX_PATH})
# set(QT6_DIR "C:/Users/lucas/.vcpkg-clion/vcpkg3/installed/x64-windows/share/Qt6")
# set(CMAKE_PREFIX_PATH "C:/Users/lucas/.vcpkg-clion/vcpkg3/installed/x64-windows" ${CMAKE_PREFIX_PATH})
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED
)
function(copy_qt_dlls target)
    if (WIN32) # AND NOT DEFINED CMAKE_TOOLCHAIN_FILE
        set(QT_DLLS
                "Qt6Core.dll"
                "Qt6Gui.dll"
                "Qt6Widgets.dll"
                "Qt6Network.dll"
        )
        set(QT_PLUGINS
            "platforms/qwindows.dll"
        )
        foreach (dll ${QT_DLLS})
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${Qt6_DIR}/../../../bin/${dll}"
                    "$<TARGET_FILE_DIR:${target}>/${dll}"
            )
        endforeach ()
        foreach (plugin ${QT_PLUGINS})
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${Qt6_DIR}/../../../plugins/${plugin}"
                    "$<TARGET_FILE_DIR:${target}>/${plugin}"
            )
        endforeach ()
    endif ()
endfunction()
############# Adding Boost#############
find_package(Boost REQUIRED COMPONENTS circular_buffer)
include_directories(${Boost_INCLUDE_DIRS})
############# Source and Executable #############
include_directories(include)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/resources/qt)
set (QTFILES
    src/qt/gui.cpp
    src/qt/field_widget.cpp
    src/io/udp_handler.cpp
    resources/qt/gui.ui
#    resources/qt/field_widget.ui
    include/Phoenixpp/qt/gui.h
    include/Phoenixpp/qt/field_widget.h
    include/Phoenixpp/io/udp_handler.h
)
add_executable(Phoenixpp
    apps/Phoenixpp.cpp
    ${QTFILES}
)
copy_qt_dlls(Phoenixpp)
#target_link_libraries(Phoenixpp PRIVATE ssl_proto)
add_subdirectory(src)
target_link_libraries(Phoenixpp PRIVATE core)
target_link_libraries(Phoenixpp PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
)
target_link_libraries(Phoenixpp PRIVATE ${Boost_LIBRARIES})
############# Tests #############
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

