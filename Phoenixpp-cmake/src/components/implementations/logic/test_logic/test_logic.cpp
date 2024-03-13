#include "test_logic.h"

TestLogic::TestLogic(atomic<bool>& stop, double fps)
    : TBaseComponent("testlogic", stop, fps) { }

void TestLogic::start(){
}

RobotCommands TestLogic::update(RobotCommands message){
    Environment env;
    {
        lock_guard<mutex> lock(component_mtx);
        if (!isComponentValid("vision")) return message;
        try{
            env = components["vision"]->getMessage<Environment>();
        } catch(exception&){
            return message;
        }
    }
    RobotCommands robotCommands;
    robotCommands.timestamp = (double)(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
    robotCommands.isteamyellow = false;
    RobotCommand command;

    command.id = 0;
    command.velangular = 0;
    command.velnormal = 0;
    command.veltangent = 4;
    command.kickspeedx = 0;
    command.kickspeedz = 0;
    command.spinner = 0;
    command.wheel1 = 0;
    command.wheel2 = 0;
    command.wheel3 = 0;
    command.wheel4 = 0;
    command.wheelsspeed = 0;

    robotCommands.robotCommands.push_back(command);

    return robotCommands;
}

TestLogic::~TestLogic(){
    //BaseComponent::~BaseComponent();
}
