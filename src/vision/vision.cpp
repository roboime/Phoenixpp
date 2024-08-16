//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/vision/vision.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include <iostream>
#include <memory>

namespace phoenixpp {
namespace vision {

Vision::Vision() : Agent("vision"), rawEnv(messaging::RawEnvironment{}),
    filter(std::make_shared<Filter>()){}
Vision::~Vision() {
    std::cout << "Destroying Vision" << std::endl;
}

void Vision::execute() {
    messaging::Environment environment = filter->execute(rawEnv);
    rawEnv.clear();
    distributeEnvironment(environment);}

void Vision::processPacket(const char *bufferPtr, int size) {
    SSL_WrapperPacket packet;
    packet.ParseFromArray(bufferPtr, size);
    if(packet.has_detection()){
        const SSL_DetectionFrame detection = packet.detection();
        for(int i=0;i<detection.balls_size();i++) {
            messaging::RawBall ball;
            ball.positionX = detection.balls().Get(i).x();
            ball.positionY = detection.balls().Get(i).y();
            ball.confidence = detection.balls().Get(i).confidence();
            ball.radius = messaging::BALL_RADIUS;
            rawEnv.insertBall(ball);
        }
        for(int i=0;i<detection.robots_blue_size();i++) {
            messaging::RawRobot robot;
            robot.positionX = detection.robots_blue().Get(i).x();
            robot.positionY = detection.robots_blue().Get(i).y();
            robot.id = detection.robots_blue().Get(i).robot_id();
            robot.height = detection.robots_blue().Get(i).height();
            robot.orientation = detection.robots_blue().Get(i).orientation();
            robot.radius = messaging::ROBOT_RADIUS;
            robot.kickerDistance = messaging::KICKER_DISTANCE;
            robot.color = messaging::Color::BLUE;
            rawEnv.insertRobot(robot);
        }
        for(int i=0;i<detection.robots_yellow_size();i++) {
            messaging::RawRobot robot;
            robot.positionX = detection.robots_yellow().Get(i).x();
            robot.positionY = detection.robots_yellow().Get(i).y();
            robot.id = detection.robots_yellow().Get(i).robot_id();
            robot.height = detection.robots_yellow().Get(i).height();
            robot.orientation = detection.robots_yellow().Get(i).orientation();
            robot.radius = messaging::ROBOT_RADIUS;
            robot.kickerDistance = messaging::KICKER_DISTANCE;
            robot.color = messaging::Color::YELLOW;
            rawEnv.insertRobot(robot);
        }
    }
    if(packet.has_geometry()){
        messaging::Field field;
        SSL_GeometryData geometry = packet.geometry();
        SSL_GeometryFieldSize fieldSize = geometry.field();
        field.field_length = fieldSize.field_length();
        field.field_width = fieldSize.field_width();
        field.goal_depth = fieldSize.goal_depth();
        field.goal_width = fieldSize.goal_depth();
        rawEnv.field.store(field);
    }
}

void Vision::distributeEnvironment(const messaging::Environment &env) {
    messaging::MessagePtr message = std::make_shared<messaging::Environment>(env);
    publisher.distribute(message);
}

} // vision
} // phoenixpp