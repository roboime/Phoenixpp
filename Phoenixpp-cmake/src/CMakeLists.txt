add_subdirectory(factories)
add_subdirectory(components)
add_subdirectory(user_interfaces)

add_executable(Phoenix main.cpp)
# target_include_directories(Phoenix PRIVATE ${CMAKE_SOURCE_DIR}/utils/components)
# target_include_directories(Phoenix PRIVATE ${CMAKE_SOURCE_DIR}/utils/messages)
target_include_directories(Phoenix PRIVATE ${CMAKE_SOURCE_DIR}/src/user_interfaces/command_line_ui)
target_link_libraries(Phoenix PUBLIC nlohmann_json)
target_link_libraries(Phoenix PUBLIC Cli) # trocar pelo factories dps
