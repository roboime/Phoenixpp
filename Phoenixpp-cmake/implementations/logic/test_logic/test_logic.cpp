#include "test_logic.h"

TestLogic::TestLogic(std::shared_ptr<Vision> vision_ptr, std::atomic<bool>& stop)
    : vision_ptr(vision_ptr), stop(stop) {
}

void TestLogic::startLogic() {
    while (!stop.load()) {
        Environment env = vision_ptr->getEnvironment();
        RobotCommands commands = execute(env);
        {
            std::lock_guard<std::mutex> lock(mtx);
            this->commands = commands;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}

RobotCommands TestLogic::execute(Environment& env){
    RobotCommands robotCommands;
    robotCommands.vel_norm = (env.ball.x + env.ball.y)*env.field_lenght + env.field_width;
    robotCommands.vel_tang = (env.ball.x + env.ball.y)*env.field_width + env.field_lenght;
    return robotCommands;
}

RobotCommands TestLogic::getRobotCommands() {
    std::lock_guard<std::mutex> lock(mtx);
    return commands;
}

void TestLogic::setVision(std::shared_ptr<Vision> newVision) {
    // Implementation for setVision
}

void TestLogic::setParameter(std::string key, std::any value) {
    // Implementation for setParameter
}

TestLogic::~TestLogic() {
    // Destructor implementation
}