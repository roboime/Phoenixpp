#include "cli.h"

Cli::Cli() : stopFlag(false), vision_ptr(make_shared<TestVision>(stopFlag)),
    logic_ptr(make_shared<TestLogic>(vision_ptr, stopFlag)) { }

void Cli::start(){
    thread logicThread([this]() { logic_ptr->startLogic(); });
    thread visionThread([this]() { vision_ptr->startReceiving(); });
    char chr;
    while (!stopFlag.load()){
        cout << "show environment: (e);\nshow robot commands: (r);\nstop: (s)" << endl;
        cin >> chr;
        switch (chr){
            case 'e':
                showEnvironment();
                break;
            case 'r':
                showRobotCommands();
                break;
            case 's':
                stopFlag.store(true);
                break;
            default:
                break;
        }
    }
    logicThread.join();
    visionThread.join();
}

void Cli::showEnvironment(){
    Environment env = vision_ptr->getEnvironment();
    cout << "field lenght: " << env.field_lenght << endl;
    cout << "field width: " << env.field_width << endl;
}

void Cli::showRobotCommands(){
    RobotCommands robotCommands = logic_ptr->getRobotCommands();
    cout << "vel_norm: " << robotCommands.vel_norm << endl;
    cout << "vel_tang: " << robotCommands.vel_tang << endl;
}