#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <atomic>

using namespace std;

struct Ball{
    double x;
    double y;
};

struct Environment{
    double field_lenght;
    double field_width;
    Ball ball;
};

#endif
