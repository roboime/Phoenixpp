//
// Created by lucas on 30/08/2024.
//

#ifndef SKILL_H
#define SKILL_H

#include "Phoenixpp/ai/stp/SkillStateMachine.h"

namespace phoenixpp::ai {

    class Skill {
    protected:
        SkillStateMachine ssm = SkillStateMachine();

    };
}

#endif //SKILL_H
