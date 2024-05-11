#ifndef TEST_LOGIC_H
#define TEST_LOGIC_H

#include <iostream>
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <any>
#include "../../../base_component.h"
#include "../../../../utils/parameters_manager.h"
#include "../../../messages/robot_commands.h"
#include "../../../messages/raw_environment.h"

using namespace std;

class TestLogic : public TBaseComponent<RobotCommands> {
private:
public:
    void start() override;
    RobotCommands update(RobotCommands message) override;
    TestLogic(atomic<bool>& stop, double fps);
    ~TestLogic();
};

#endif // TEST_LOGIC_H
