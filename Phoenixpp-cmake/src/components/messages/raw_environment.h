#ifndef RAWENVIRONMENT_H
#define RAWENVIRONMENT_H

using namespace std;

struct RawObject{
    double x;
    double y;
    int id;
    double radius;
    double confidence;
};

struct RawBall : RawObject{
    double z;
};

struct RawRobot : RawObject{
    double orientation;
    double height;
    double kickerDistance; // distance between center of the robot to the kicker
};

struct Field{
    int field_length; // x axis
    int field_width; // y axis
    int goal_depth; // x axis
    int goal_width; // y axis
    int boundary_width;
    int penalty_area_depth; // x axis
    int penalty_area_width; // y axis
    vector<double> ourGoalPosition; // [x,y]
    vector<double> penaltySpot; // [x,y]
};

struct RawEnvironment{
    bool received;
    vector<RawBall> balls;
    vector<RawRobot> robots;
    Field field;
};

#endif
