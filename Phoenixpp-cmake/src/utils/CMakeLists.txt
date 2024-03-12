add_library(Utils parameters_manager.cpp parameters_manager.h udp_receiver.cpp udp_receiver.h udp_sender.h udp_sender.cpp)
target_link_libraries(Utils PUBLIC nlohmann_json)
target_link_libraries(Utils PUBLIC Poco::Net)

