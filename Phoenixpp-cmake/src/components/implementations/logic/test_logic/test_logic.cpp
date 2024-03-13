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
    robotCommands.timestamp = (double)(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
    robotCommands.isteamyellow = false;
    RobotCommand command;

    command.id = 0;
    command.velangular = 1;
    command.velnormal = 1;
    command.veltangent = 1;
    robotCommands.robotCommands.push_back(command);

    return robotCommands;
}

TestLogic::~TestLogic(){
    //BaseComponent::~BaseComponent();
}
