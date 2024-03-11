#include "test_logic.h"

TestLogic::TestLogic(atomic<bool>& stop, double fps)
    : BaseComponent("testlogic", stop, fps) { }

void TestLogic::start(){
}

RobotCommands TestLogic::update(RobotCommands message){
    Environment env;
    {
        lock_guard<mutex> lock(component_mtx);
        if (!isComponentValid("vision")) return message;
        env = components["vision"]->getMessage<Environment>();
    }
    RobotCommands robotCommands;
    robotCommands.vel_norm = (env.ball.x + env.ball.y)*env.field.field_length + env.field.field_width;
    robotCommands.vel_tang = (env.ball.x + env.ball.y)*env.field.field_width + env.field.field_length;
    return robotCommands;
}

TestLogic::~TestLogic(){
    //BaseComponent::~BaseComponent();
}
