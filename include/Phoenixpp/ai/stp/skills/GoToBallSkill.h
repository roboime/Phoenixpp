//
// Created by lucas on 03/09/2024.
//

#ifndef GOTOBALLSKILL_H
#define GOTOBALLSKILL_H

#include "Phoenixpp/ai/stp/Skill.h"
#include "Phoenixpp/ai/stp/SkillStateMachine.h"

namespace phoenixpp::ai {

    enum class GoToBallSkillState{
        IDLE,
        GO_TO_BALL
    };

    class GoToBallSkill : public Skill {
    public:
        GoToBallSkill(){
            auto ssm = SkillStateMachine<GoToBallSkillState>(GoToBallSkillState::IDLE);
            addTransitions();
        }
    private:
       void addTransitions() {
           ssm.addTransition(GoToBallSkillState::IDLE, GoToBallSkillState::GO_TO_BALL);
           ssm.addTransition(GoToBallSkillState::GO_TO_BALL, GoToBallSkillState::IDLE);
       }
    };
}

#endif //GOTOBALLSKILL_H
