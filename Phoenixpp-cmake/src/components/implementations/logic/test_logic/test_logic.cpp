#include "test_logic.h"

TestLogic::TestLogic(atomic<bool>& stop, double fps)
    : BaseComponent("testlogic", stop, fps) { }

void TestLogic::start(){
}

RobotCommands TestLogic::update(){
    Environment env;
    {
        std::lock_guard<std::mutex> lock(component_mtx);
        if (!isComponentValid("vision")) return message;
        env = components["vision"]->getMessage<Environment>();
    }
    RobotCommands robotCommands;
    robotCommands.vel_norm = (env.ball.x + env.ball.y)*env.field_lenght + env.field_width;
    robotCommands.vel_tang = (env.ball.x + env.ball.y)*env.field_width + env.field_lenght;
    return robotCommands;
}