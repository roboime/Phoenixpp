//
// Created by lucas on 03/09/2024.
//

#ifndef GOTOBALLSKILL_H
#define GOTOBALLSKILL_H

#include "Phoenixpp/ai/stp/Skill.h"
#include "Phoenixpp/ai/stp/SkillStateMachine.h"

namespace phoenixpp::ai {

    class GoToBallSkill : public Skill {
    public:
        GoToBallSkill(){
            auto ssm = SkillStateMachine();
            addTransitions();
        }
    private:
       void addTransitions() {
           ssm.addState("Idle", []() { std::cout << "State: Idle\n"; });
           ssm.addState("Running", []() { std::cout << "State: Running\n"; });

           ssm.addTransition("Idle", "Running");
           ssm.addTransition("Running", "Idle");
       }
    };
}

#endif //GOTOBALLSKILL_H
