#ifndef TEST_LOGIC_H
#define TEST_LOGIC_H

#include <iostream>
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <any>
#include "../../../utils/components/base_component.h"
#include "../../../utils/components/parameters_manager.h"
#include "../../../utils/messages/robot_commands.h"
#include "../../../utils/messages/environment.h"

using namespace std;

class TestLogic : public BaseComponent<RobotCommands> {
private:
public:
    void start() override;
    RobotCommands update() override;
    TestLogic(atomic<bool>& stop, double fps);
    ~TestLogic(){};
};

#endif // TEST_LOGIC_H
