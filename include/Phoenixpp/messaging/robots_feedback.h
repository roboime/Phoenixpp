//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_FEEDBACK_H
#define ROBOTS_FEEDBACK_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsFeedback : Message{
    void forwardTo(RobotsFeedbackListener *listener) override;
    void store(const RobotsFeedback& other){}
};
using RobotsFeedbackPtr = std::shared_ptr<RobotsFeedback>;
} // messaging
} // phoenixpp

#endif //ROBOTS_FEEDBACK_H
