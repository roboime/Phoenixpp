#ifndef CLI_H
#define CLI_H
#include <atomic>
#include <memory>
#include "../../implementations/logic/test_logic/test_logic.h"
#include "../../implementations/vision/test_vision/test_vision.h"

using namespace std;

class Cli {
private:
    atomic<bool> stopFlag;
    shared_ptr<Vision> vision_ptr;
    shared_ptr<TestLogic> logic_ptr;
    void showEnvironment();
    void showRobotCommands();
public:
    Cli();
    void start();
    ~Cli() {}
};

#endif // CLI_H
