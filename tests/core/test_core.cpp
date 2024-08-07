//
// Created by ebert on 7/18/2024.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Phoenixpp/core/agent_controller.h"

using namespace phoenixpp::core;

TEST(ControllerTest, LoopAgentsTest) {
    AgentController controller;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    controller.setAgent("blue_ai", "blabla");
    std::cout << "switching strategy" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
