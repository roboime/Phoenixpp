add_library(core
        STATIC
        core/agent_controller.cpp
        core/agent.cpp
)
add_library(factories
        STATIC
        factories/vision_factory.cpp
        factories/agent_factory_registry.cpp
        factories/referee_factory.cpp
        factories/strategy_factory.cpp
        factories/listener_factory.cpp
)
add_library(messaging
        STATIC
        messaging/message.cpp
        messaging/listener.cpp
        messaging/publisher.cpp
        messaging/message_collection.cpp
)
add_library(vision
        STATIC
        vision/vision.cpp
        vision/ssl_vision.cpp
        vision/test_vision.cpp
)
add_library(referee
        STATIC
        referee/referee.cpp
        referee/ssl_referee.cpp
)
add_library(ai
        STATIC
        ai/strategy.cpp
        ai/stp/stp.cpp
)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(core PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(core PRIVATE factories)
target_link_libraries(core PRIVATE messaging)
target_link_libraries(factories PRIVATE vision)
target_link_libraries(factories PRIVATE referee)
target_link_libraries(factories PRIVATE ai)
target_link_libraries(referee PRIVATE core)
target_link_libraries(vision PRIVATE core)
target_link_libraries(ai PRIVATE core)
target_link_libraries(ai PRIVATE factories)
