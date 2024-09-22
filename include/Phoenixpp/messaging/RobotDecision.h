//
// Created by lucas on 02/09/2024.
//

#ifndef ROBOTDECISION_H
#define ROBOTDECISION_H

#include <optional>
#include <atomic>
using std::atomic;

struct RobotDecision{
    RobotDecision() :
        id(0),
        x(0),
        y(0),
        orientation(0),
        validDecision(false),
        kick(false),
        drible(false) {};
    atomic<int> id;
    atomic<double> x;
    atomic<double> y;
    atomic<double> orientation;
    atomic<bool> validDecision;
    atomic<bool> kick;
    atomic<bool> drible;

    void store(const RobotDecision& other) {
        x.store(other.x.load());
        y.store(other.y.load());
        orientation.store(other.orientation.load());
        validDecision.store(other.validDecision.load());
        kick.store(other.kick.load());
        drible.store(other.drible.load());
    }

    ~RobotDecision() = default;

};

#endif //ROBOTDECISION_H
