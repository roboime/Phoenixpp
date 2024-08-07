//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_FEEDBACK_H
#define ROBOTS_FEEDBACK_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsFeedback {

};
class RobotsFeedbackWrapper : public Message{
public:
    void forwardTo(RobotsFeedbackListener *listener) override;
    RobotsFeedback getRobotsFeedback() const {return feedback;}
private:
    RobotsFeedback feedback;
};
using RobotsFeedbackWrapperPtr = std::shared_ptr<RobotsFeedbackWrapper>;
using RobotsFeedbackPtr = std::shared_ptr<boost::atomic<RobotsFeedback>>;
} // messaging
} // phoenixpp

#endif //ROBOTS_FEEDBACK_H
