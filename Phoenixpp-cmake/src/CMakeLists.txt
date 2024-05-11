add_subdirectory(factories)
add_subdirectory(components)
add_subdirectory(user_interfaces)
add_subdirectory(utils)

add_executable(PhoenixCli main_cli.cpp)
add_executable(PhoenixGui main_gui.cpp)

target_include_directories(PhoenixCli PUBLIC ${CMAKE_SOURCE_DIR}/proto)
target_include_directories(PhoenixCli PUBLIC ${CMAKE_SOURCE_DIR}/src/user_interfaces/command_line_ui)
target_link_libraries(PhoenixCli PUBLIC nlohmann_json)
target_link_libraries(PhoenixCli PUBLIC Cli)
target_link_libraries(PhoenixCli PUBLIC protobuf)

target_include_directories(PhoenixGui PUBLIC ${CMAKE_SOURCE_DIR}/src/user_interfaces/graphical_ui)
target_include_directories(PhoenixGui PUBLIC ${CMAKE_SOURCE_DIR}/proto)
target_link_libraries(PhoenixGui PUBLIC nlohmann_json)
target_link_libraries(PhoenixGui PUBLIC Gui)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
include_directories(${Qt5_INCLUDE_DIRS})
target_link_libraries(PhoenixGui PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)

#find_package (Eigen3 3.3 REQUIRED NO_MODULE)
#target_link_libraries (PhoenixGui PUBLIC Eigen3::Eigen)
#target_link_libraries (PhoenixCli PUBLIC Eigen3::Eigen)
