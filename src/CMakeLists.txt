add_library(messaging
        STATIC
        messaging/message_listener.cpp
        messaging/message_wrapper.tpp
        messaging/message_publisher.tpp
)

find_package(nlohmann_json CONFIG REQUIRED)
#target_link_libraries(baseUI PRIVATE nlohmann_json::nlohmann_json)