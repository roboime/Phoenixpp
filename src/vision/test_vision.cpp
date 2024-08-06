//
// Created by ebert on 7/23/2024.
//

#include "Phoenixpp/vision/test_vision.h"

#include <iostream>

namespace phoenixpp {
namespace vision {

void TestVision::execute() {
    messaging::Environment newEnv = environment;
    newEnv.a += 2;
    std::cout << "SSL Vision counter: " << newEnv.a << std::endl;
    distributeEnvironment(newEnv);
}

} // vision
} // phoenixpp