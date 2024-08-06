//
// Created by ebert on 7/17/2024.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <atomic>
#include "Phoenixpp/messaging/environment.h"

using namespace phoenixpp::messaging;

TEST(EnvironmentTest, ForwardToTest) {

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
