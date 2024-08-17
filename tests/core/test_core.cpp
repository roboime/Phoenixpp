//
// Created by ebert on 7/18/2024.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Phoenixpp/core/agent_controller.h"

using namespace phoenixpp::core;

TEST(ControllerTest, LoopAgentsTest) {
    AgentController controller("test_settings.json");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
