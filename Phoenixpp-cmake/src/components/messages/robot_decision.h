#ifndef ROBOT_DECISION_H
#define ROBOT_DECISION_H

#include <vector>
#include <string>

using namespace std;

struct SingleDecision{
    vector<double> destination;
    double kick_x;
    double kick_z;
    bool spinner;
    int driveMode;
    string role;
    string tactic;
    string skill;
    string skill_state;
};

struct RobotDecision{
    vector<SingleDecision> decision; // for 6 robots
};

#endif // ROBOT_DECISION_H
