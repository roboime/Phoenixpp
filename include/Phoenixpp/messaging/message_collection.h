//
// Created by ebert on 8/6/2024.
//

#ifndef MESSAGE_COLLECTION_H
#define MESSAGE_COLLECTION_H

#include <Phoenixpp/messaging/environment.h>
#include <Phoenixpp/messaging/fouls.h>
#include <Phoenixpp/messaging/robots_feedback.h>
#include <Phoenixpp/messaging/robots_decision.h>
#include <Phoenixpp/messaging/robots_path.h>
#include <Phoenixpp/messaging/robots_commands.h>
#include <Phoenixpp/messaging/robots_output.h>
#include <Phoenixpp/messaging/listener.h>

namespace phoenixpp {
namespace messaging {

struct MessageCollection {
    EnvironmentPtr environment;
    FoulsPtr fouls;
    RobotsFeedbackPtr robotsFeedback;
    DecisionsStorePtr blueDecision;
    DecisionsStorePtr yellowDecision;
    RobotsPathPtr robotsPath;
    RobotsCommandsPtr robotsCommands;
    RobotsOutputPtr robotsOutput;
    MessageCollection();
    ListenerPtr createListener(const std::string &key);
};

} // messaging
} // phoenixpp

#endif //MESSAGE_COLLECTION_H
