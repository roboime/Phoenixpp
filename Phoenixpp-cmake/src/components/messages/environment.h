#ifndef FILTERED_ENVIRONMENT_H
#define FILTERED_ENVIRONMENT_H

#include "raw_environment.h"

using namespace std;

struct Object{
    double x;
    double y;
    double velX;
    double velY;
    double aX;
    double aY;
    int id;
    double radius;
    double confidence;
};

struct Ball : Object{
    double z;
};

struct Robot : Object{
    double orientation;
    double height;
    double kickerDistance; // distance between center of the robot to the kicker
};

struct Environment{
    bool received;
    vector<Ball> ball;
    vector<Robot> robot;
    Field field;
};

#endif // FILTERED_ENVIRONMENT_H
