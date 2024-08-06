//
// Created by ebert on 7/22/2024.
//

#include "Phoenixpp/ai/strategy.h"

#include <iostream>
#include <memory>
#include <Phoenixpp/factories/listener_factory.h>

namespace phoenixpp {
namespace ai {

Strategy::Strategy(const std::string &type) : Agent(type){}
void Strategy::execute() {
    // std::cout << "Executing Default Strategy" << std::endl;
    messaging::Environment env = environment->load();
    std::cout << type << " Strategy counter: " << env.a << std::endl;
}
messaging::ListenerPtr Strategy::createListener(const std::string &type) {
    if(type == "vision") {
        return factories::ListenerFactory::createListener(environment);
    }
    if(type == "feedback") {
        return factories::ListenerFactory::createListener(robotsFeedback);
    }
    if(type == "referee") {
        return factories::ListenerFactory::createListener(fouls);
    }
    return nullptr;
}
Strategy::~Strategy() {
    std::cout << "Destroying " << type << " Strategy" << std::endl;
}

} // ai
} // phoenix