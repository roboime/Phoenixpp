#ifndef ELO_MEC_TESTER_H
#define ELO_MEC_TESTER_H

#include "base_component.h"
#include "./messages/robot_commands.h"

using namespace std;

class EloMecTester : public TBaseComponent<RobotCommands>
{
public:
    EloMecTester(atomic<bool>& stop, double fps);
    RobotCommands update(RobotCommands robotPath) override;
    void start() override;
    ~EloMecTester() {}
};

#endif // ELO_MEC_TESTER_H
