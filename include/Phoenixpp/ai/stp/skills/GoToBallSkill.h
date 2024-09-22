//
// Created by lucas on 03/09/2024.
//

#ifndef GOTOBALLSKILL_H
#define GOTOBALLSKILL_H

#include "Phoenixpp/ai/stp/Skill.h"
#include "Phoenixpp/ai/stp/SkillStateMachine.h"
#include <Phoenixpp/messaging/RobotDecision.h>

namespace phoenixpp::ai {

    class GoToBallSkill : public Skill {
    public:
        GoToBallSkill(){
            ssm = SkillStateMachine();
            addTransitions();
            ssm.setInitialState("RUNNING");
        }
        SkillStateMachine getSSM() {
            return ssm;
        }
    private:
       void addTransitions() {
           ssm.addState("IDLE", [](const messaging::EnvironmentPtr environment, std::shared_ptr<messaging::DecisionsStore> message) {
               return RobotDecision();
           });
           ssm.addState("RUNNING", [](const messaging::EnvironmentPtr environment, std::shared_ptr<messaging::DecisionsStore> message) {
               auto robotDecision = RobotDecision();

               robotDecision.x.store(environment->balls[0].positionX);
               robotDecision.y.store(environment->balls[0].positionY);

                message->storeRobot(robotDecision);
           });

           ssm.addTransition("IDLE", "RUNNING", [](const messaging::EnvironmentPtr environment) {
               return true;
           });
           ssm.addTransition("RUNNING", "IDLE", [](const messaging::EnvironmentPtr environment) {
               return false;
           });
       }
    };
}

#endif //GOTOBALLSKILL_H
