#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

using namespace std;

struct Ball{
    double x;
    double y;
};

struct Field{
    double field_length;
    double field_width;
};

struct Environment{
    bool received;
    Ball ball;
    Field field;
};

#endif
