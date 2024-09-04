//
// Created by lucas on 30/08/2024.
//

#ifndef SKILL_H
#define SKILL_H

#include "Phoenixpp/ai/stp/SkillStateMachine.h"

namespace phoenixpp::ai {

    template <typename State>
    class Skill {
    protected:
        SkillStateMachine<State> ssm = SkillStateMachine(State::IDLE);

    };
}

#endif //SKILL_H
