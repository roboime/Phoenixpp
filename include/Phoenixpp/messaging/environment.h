//
// Created by ebert on 6/1/2024.
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "message.h"
#include <boost/atomic.hpp>
#include <complex>
#include <array>

namespace phoenixpp {
namespace messaging {

constexpr int MAX_ROBOTS = 32;
constexpr int MAX_BALLS = 10;
constexpr double BALL_RADIUS = 21.5;
constexpr double ROBOT_RADIUS = 90;
constexpr double KICKER_DISTANCE = 73;

struct RawObject{
    bool valid;
    std::complex<double> position;
    double radius;
    double confidence;
};

struct RawBall : RawObject{
    double z;
};

struct RawRobot : RawObject{
    int id;
    double orientation;
    double height;
    double kickerDistance; // distance between center of the robot to the kicker
};

struct Field {
    int field_length; // x axis
    int field_width; // y axis
    int goal_depth; // x axis
    int goal_width; // y axis
    int boundary_width;
    int penalty_area_depth; // x axis
    int penalty_area_width; // y axis
    std::complex<double> blueGoalPosition; // [x,y]
    std::complex<double> yellowGoalPosition; // [x,y]
    double penaltyDistance;
};

struct RawEnvironment{
    bool received;
    std::array<RawBall, MAX_BALLS> balls;
    std::array<RawRobot, MAX_ROBOTS> robots;
    Field field;
    void insertBall(RawBall ball){
        for(int i = 0; i < MAX_BALLS; i++){
            if(balls[i].valid) continue;
            ball.valid = true;
            balls[i] = ball;
            return;
        }
    }
    void insertRobot(RawRobot robot) {
        for(int i = 0; i < MAX_ROBOTS; i++){
            if(robots[i].valid) continue;
            robot.valid = true;
            robots[i] = robot;
            return;
        }
    }
    void clear() {
        for(auto &robot : robots) {
            robot.valid = false;
        }
        for(auto &ball : balls) {
            ball.valid = false;
        }
    }
};

struct Object{
    bool valid;
    std::complex<double> position;
    std::complex<double> velocity;
    std::complex<double> acceleration;
    double radius;
    double confidence;
};

struct Ball : Object{
    double z;
};

struct Robot : Object{
    int id;
    double orientation;
    double height;
    double kickerDistance; // distance between center of the robot to the kicker
};

struct Environment{
    bool received;
    std::array<Ball, MAX_BALLS> balls;
    std::array<Robot, MAX_ROBOTS> robots;
    Field field;
};
class EnvironmentWrapper : public Message {
public:
    explicit EnvironmentWrapper(const Environment env) : environment(env) {};
    ~EnvironmentWrapper() override = default;
    void forwardTo(EnvironmentListener* listener) override;
    [[nodiscard]] Environment getEnvironment() const {return environment;}
private:
    Environment environment;
};
using EnvironmentWrapperPtr = std::shared_ptr<EnvironmentWrapper>;
using EnvironmentPtr = std::shared_ptr<boost::atomic<Environment>>;

} // messaging
} // phoenixpp

#endif //ENVIRONMENT_H
