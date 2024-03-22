#include "elo_mec_tester.h"

EloMecTester::EloMecTester(atomic<bool>& stop, double fps) : TBaseComponent("elomectester", stop, fps)
{
    parameters.load();
}

RobotCommands EloMecTester::update(RobotCommands robotPath){
    RobotCommand command;
    RobotCommands commands;
    try {
        commands.isteamyellow = any_cast<bool>(getParameter("isTeamYellow"));
        command.id = any_cast<int>(getParameter("id"));
        command.kickspeedx = 0.0f;
        command.kickspeedz = 0.0f;
        //command.kickspeedz = (float)any_cast<double>(getParameter("kickzVel"));
        if (any_cast<bool>(getParameter(" "))) {
            command.kickspeedx = (float)any_cast<double>(getParameter("kickxVel"));
        }
        if (any_cast<bool>(getParameter("w"))) {
            command.veltangent = (float)any_cast<double>(getParameter("vel"));
        } else if (any_cast<bool>(getParameter("s"))) {
            command.veltangent = -((float)any_cast<double>(getParameter("vel")));
        }
        if (any_cast<bool>(getParameter("a"))) {
            command.velnormal = (float)any_cast<double>(getParameter("vel"));
        } else if (any_cast<bool>(getParameter("d"))) {
            command.velnormal = -(float)any_cast<double>(getParameter("vel"));
        }
        if (any_cast<bool>(getParameter("q"))) {
            command.velangular = (float)any_cast<double>(getParameter("velAng"));
        } else if (any_cast<bool>(getParameter("e"))) {
            command.velangular = -(float)any_cast<double>(getParameter("velAng"));
        }
    } catch (const std::exception& e) {
        cerr << "Error in Elo Mec Tester: " << e.what() << endl;
    }
    commands.robotCommands.push_back(command);
    return commands;
}

void EloMecTester::start(){

}
