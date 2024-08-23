//
// Created by ebert on 6/1/2024.
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "message.h"
#include <atomic>

namespace phoenixpp {
namespace messaging {
using std::atomic;
constexpr int MAX_ROBOTS = 32;
constexpr int MAX_BALLS = 10;
constexpr double BALL_RADIUS = 21.5;
constexpr double ROBOT_RADIUS = 90;
constexpr double KICKER_DISTANCE = 73;
enum class Color {BLUE, YELLOW};

struct RawObject{
    bool valid;
    double positionX;
    double positionY;
    double radius;
    double confidence;
};

struct RawBall : RawObject{
    double z;
};

struct RawRobot : RawObject{
    unsigned int id;
    double orientation;
    double height;
    double kickerDistance; // distance between center of the robot to the kicker
    Color color;
};

struct Field {
    atomic<bool> valid;
    atomic<int> field_length; // x axis
    atomic<int> field_width; // y axis
    atomic<int> goal_depth; // x axis
    atomic<int> goal_width; // y axis
    atomic<int> boundary_width;
    atomic<int> penalty_area_depth; // x axis
    atomic<int> penalty_area_width; // y axis
    atomic<double> centerRadius;
    atomic<double> penaltyDistance;

    void store(const Field& other) {
        field_length.store(other.field_length.load());
        field_width.store(other.field_width.load());
        goal_depth.store(other.goal_depth.load());
        goal_width.store(other.goal_width.load());
        boundary_width.store(other.boundary_width.load());
        penalty_area_depth.store(other.penalty_area_depth.load());
        penalty_area_width.store(other.penalty_area_width.load());
        penaltyDistance.store(other.penaltyDistance.load());
        centerRadius.store(other.centerRadius.load());
        valid.store(other.valid);
    }
};

struct RawEnvironment{
    bool received;
    RawBall balls[MAX_BALLS];
    RawRobot robots[MAX_ROBOTS];
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
    Object() :
        valid(false),
        radius(0),
        confidence(0),
        positionX(0),
        positionY(0),
        velocityX(0),
        velocityY(0),
        accelerationX(0),
        accelerationY(0) {};
    atomic<bool> valid;
    atomic<double> radius;
    atomic<double> confidence;
    atomic<double> positionX;
    atomic<double> positionY;
    atomic<double> velocityX;
    atomic<double> velocityY;
    atomic<double> accelerationX;
    atomic<double> accelerationY;
    void store(const Object& other) {
        valid.store(other.valid.load());
        radius.store(other.radius.load());
        confidence.store(other.confidence.load());
        positionX.store(other.positionX.load());
        positionY.store(other.positionY.load());
        velocityX.store(other.velocityX.load());
        velocityY.store(other.velocityY.load());
        accelerationX.store(other.accelerationX.load());
        accelerationY.store(other.accelerationY.load());
    }
};

struct Ball : Object{
    Ball() : z(0) {};
    atomic<double> z;
    void store(const Ball& other) {
        Object::store(other);
        z = other.z.load();
    }
};

struct Robot : Object{
    Robot() :
        id(99),
        orientation(0),
        height(0),
        kickerDistance(0),
        color(Color::BLUE) {};
    atomic<unsigned int> id;
    atomic<double> orientation;
    atomic<double> height;
    atomic<double> kickerDistance;
    atomic<Color> color;
    void store(const Robot& other) {
        Object::store(other);
        id.store(other.id.load());
        orientation.store(other.orientation.load());
        height.store(other.height.load());
        kickerDistance.store(other.kickerDistance.load());
        color.store(other.color.load());
    }
};

struct Environment: Message{
    Environment() : received(false) {};
    Environment(const Environment& other) { store(other); };
    Environment(Environment&& other) noexcept { store(other); }
    Environment& operator=(const Environment& other) {
        if(this != &other) store(other);
        return *this;
    };
    atomic<bool> received;
    Ball balls[MAX_BALLS];
    Robot robots[MAX_ROBOTS];
    Field field;
    void store(const Environment& other) {
        received.store(other.received.load());
        field.store(other.field);
        for(int i=0;i<MAX_ROBOTS;i++) {
            robots[i].store(other.robots[i]);
        }
        for(int i=0;i<MAX_BALLS;i++) {
            balls[i].store(other.balls[i]);
        }
    }
    void forwardTo(EnvironmentListener* listener) override;
};
using EnvironmentPtr = std::shared_ptr<Environment>;
} // messaging
} // phoenixpp

#endif //ENVIRONMENT_H
