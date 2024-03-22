#ifndef ROBOT_PATHS_H
#define ROBOT_PATHS_H

#include <vector>

using namespace std;

struct RobotPath{
    vector<vector<vector<double>>> blueRobotsPath; // dimension for 6 robots, and n (x,y) points: [6,n,2]
    vector<vector<vector<double>>> yellowRobotsPath; // dimension for 6 robots, and n (x,y) points: [6,n,2]
};

#endif // ROBOT_PATHS_H
