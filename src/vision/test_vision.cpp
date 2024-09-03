//
// Created by ebert on 7/23/2024.
//

#include "Phoenixpp/vision/test_vision.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace phoenixpp {
namespace vision {

TestVision::TestVision(const int &fps) : Vision(fps) {}

void TestVision::execute() {
    std::cout << "Executing Test Vision" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Vision Executed" << std::endl;
}

} // vision
} // phoenixpp