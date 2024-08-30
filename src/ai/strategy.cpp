//
// Created by ebert on 7/22/2024.
//

#include "Phoenixpp/ai/strategy.h"

#include <iostream>
#include <memory>
#include <Phoenixpp/factories/listener_factory.h>


namespace phoenixpp::ai {

Strategy::Strategy(const std::string &type, const int &fpsa) : Agent(type, fps){}
void Strategy::execute() {
    // messaging::Environment env = environment->load();
}
messaging::ListenerPtr Strategy::createListener(const std::string &key) {
    if(key == "vision") {
        return factories::ListenerFactory::createListener(environment);
    }
    if(key == "feedback") {
        return factories::ListenerFactory::createListener(robotsFeedback);
    }
    if(key == "referee") {
        return factories::ListenerFactory::createListener(fouls);
    }
    return nullptr;
}
Strategy::~Strategy() {
    std::cout << "Destroying " << type << " Strategy" << std::endl;
}

} // ai
// phoenix