#ifndef TEST_LOGIC_H
#define TEST_LOGIC_H

#include <iostream>
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include "../../../utils/interfaces/logic.h"
#include "../../../utils/interfaces/vision.h"
#include "../../../utils/structs/robot_commands.h"

using namespace std;

class TestLogic : public Logic {
private:
    shared_ptr<Vision> vision_ptr;
    atomic<bool>& stop;
    mutex mtx;
    RobotCommands commands;
    RobotCommands execute(Environment& env);

public:
    TestLogic(std::shared_ptr<Vision> vision_ptr, std::atomic<bool>& stop);
    void startLogic() override;
    RobotCommands getRobotCommands() override;
    void setVision(std::shared_ptr<Vision> newVision) override;
    void setParameter(std::string key, std::any value) override;
    ~TestLogic();
};

#endif // TEST_LOGIC_H
