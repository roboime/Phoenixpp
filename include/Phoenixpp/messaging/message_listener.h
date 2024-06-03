//
// Created by ebert on 6/1/2024.
//

#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H

#include "message.h"
#include "environment.h"
#include "fouls.h"
#include "robots_feedback.h"
#include "robots_decision.h"
#include "robots_path.h"
#include "robots_commands.h"
#include "robots_output.h"
#include <iostream>
#include <memory>


namespace roboime {
namespace messaging {

class MessageListener {
public:
    static void overrideWarning(const std::string&);
    void update(const std::shared_ptr<roboime::messaging::Message>&);
    virtual void updateVisit(Environment);
    virtual void updateVisit(Fouls);
    virtual void updateVisit(RobotsFeedback);
    virtual void updateVisit(RobotsDecision);
    virtual void updateVisit(RobotsPath);
    virtual void updateVisit(RobotsCommands);
    virtual void updateVisit(RobotsOutput);
    virtual ~MessageListener();
};

} // messaging
}// roboime

#endif //MESSAGE_LISTENER_H
