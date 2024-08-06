#ifndef LISTENER_H
#define LISTENER_H

#include "message.h"
#include "environment.h"
#include "fouls.h"
#include "robots_feedback.h"
#include "robots_decision.h"
#include "robots_path.h"
#include "robots_commands.h"
#include "robots_output.h"

namespace phoenixpp {
namespace messaging {

class Listener {
public:
    virtual void update(MessagePtr message) = 0;
    virtual ~Listener() = default;
};
using ListenerPtr = std::shared_ptr<Listener>;

class EnvironmentListener: public Listener {
public:
    explicit EnvironmentListener(const EnvironmentPtr &env);
    void update(MessagePtr message) override;
    void updateEnvironment(EnvironmentWrapper* newEnvironment) const;
private:
    EnvironmentPtr environment;
};

class FoulsListener : public Listener {
public:
    explicit FoulsListener(const FoulsPtr &fouls);
    void update(MessagePtr message) override;
    void updateFouls(FoulsWrapper* newFouls) const;

private:
    FoulsPtr fouls;
};

class RobotsFeedbackListener : public Listener {
public:
    explicit RobotsFeedbackListener(const RobotsFeedbackPtr &feedback);
    void update(MessagePtr message) override;
    void updateRobotsFeedback(RobotsFeedbackWrapper* newFeedback) const;

private:
    RobotsFeedbackPtr robotsFeedback;
};

class RobotsDecisionListener : public Listener {
public:
    explicit RobotsDecisionListener(const RobotsDecisionPtr &decision);
    void update(MessagePtr message) override;
    void updateRobotsDecision(RobotsDecisionWrapper* newDecision) const;

private:
    RobotsDecisionPtr robotsDecision;
};

class RobotsPathListener : public Listener {
public:
    explicit RobotsPathListener(const RobotsPathPtr &path);
    void update(MessagePtr message) override;
    void updateRobotsPath(RobotsPathWrapper* newPath) const;

private:
    RobotsPathPtr robotsPath;
};

class RobotsCommandsListener : public Listener {
public:
    explicit RobotsCommandsListener(const RobotsCommandsPtr &commands);
    void update(MessagePtr message) override;
    void updateRobotsCommands(RobotsCommandsWrapper* newCommands) const;

private:
    RobotsCommandsPtr robotsCommands;
};

class RobotsOutputListener : public Listener {
public:
    explicit RobotsOutputListener(const RobotsOutputPtr &output);
    void update(MessagePtr message) override;
    void updateRobotsOutput(RobotsOutputWrapper* newOutput) const;

private:
    RobotsOutputPtr robotsOutput;
};

} // messaging
} // phoenixpp

#endif // LISTENER_H