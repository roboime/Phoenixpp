//
// Created by ebert on 6/1/2024.
//

#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <memory>

namespace phoenixpp{
namespace messaging {
class EnvironmentListener;
class FoulsListener;
class RobotsDecisionListener;
class RobotsFeedbackListener;
class RobotsCommandsListener;
class RobotsPathListener;
class RobotsOutputListener;

class Message {
public:
    virtual void forwardTo(EnvironmentListener *listener);
    virtual void forwardTo(FoulsListener *listener);
    virtual void forwardTo(RobotsDecisionListener *listener);
    virtual void forwardTo(RobotsFeedbackListener *listener);
    virtual void forwardTo(RobotsCommandsListener *listener);
    virtual void forwardTo(RobotsPathListener *listener);
    virtual void forwardTo(RobotsOutputListener *listener);
    virtual ~Message() = default;
private:
    static void logWarning(const std::string&);
};

using MessagePtr = std::shared_ptr<Message>;
} // messagging
}// phoenixpp

#endif //MESSAGE_H
