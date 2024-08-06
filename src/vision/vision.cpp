//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/vision/vision.h"

#include <iostream>
#include <memory>

namespace phoenixpp {
namespace vision {

Vision::Vision() : Agent("vision"), environment(messaging::Environment{0}){}
Vision::~Vision() {
    std::cout << "Destroying Vision" << std::endl;
}

void Vision::execute() {
    std::cout << "Executing Default Vision" << std::endl;
}

void Vision::distributeEnvironment(const messaging::Environment &env) {
    messaging::MessagePtr message = std::make_shared<messaging::EnvironmentWrapper>(env);
    publisher.distribute(message);
    environment = env;
}

} // vision
} // phoenixpp