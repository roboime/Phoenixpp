//
// Created by ebert on 7/22/2024.
//

#include "Phoenixpp/ai/strategy.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <Phoenixpp/factories/listener_factory.h>

namespace phoenixpp {
namespace ai {

Strategy::Strategy(const std::string &type, const int &fps) : Agent(type, fps){}
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
} // phoenix