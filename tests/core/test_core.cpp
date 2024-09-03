//
// Created by ebert on 7/18/2024.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Phoenixpp/vision/vision.h>

#include "Phoenixpp/core/agent_controller.h"

using namespace phoenixpp::core;

TEST(ControllerTest, LoopAgentsTest) {
    AgentController controller("test_settings.json");
    controller.setAgent("vision", "test", 120);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Start acquiring setAgent lock" << std::endl;
    controller.setAgent("vision", "test", 40);
    std::cout << "Agent set" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
