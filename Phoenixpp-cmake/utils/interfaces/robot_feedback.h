#ifndef ROBOT_FEEDBACK_H
#define ROBOT_FEEDBACK_H
#include "../structs/robot_feedback_data.h"

class RobotFeedback {
public:
    virtual void startReceiving() = 0;
    virtual RobotFeedbackData getRobotFeedbackData() = 0;
    virtual ~RobotFeedback() {}
};

#endif // ROBOT_FEEDBACK_H
