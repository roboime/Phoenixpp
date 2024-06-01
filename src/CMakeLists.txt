add_library(base_component base_component.cpp)
add_library(udpVision vision/udp_vision.cpp)
add_library(baseUI base_ui.cpp)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(baseUI PRIVATE nlohmann_json::nlohmann_json)