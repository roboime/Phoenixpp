//
// Created by lucas on 03/09/2024.
//

#ifndef DUMBATTACKERTACTIC_H
#define DUMBATTACKERTACTIC_H

#include "Phoenixpp/ai/stp/Tactic.h"
#include "Phoenixpp/ai/stp/skills/GoToBallSKill.h"

namespace phoenixpp::ai {
    class DumbAttackerTactic : public Tactic {
    public:
        DumbAttackerTactic() {
            auto goToBallSKill = GoToBallSkill();
            ssms.push_back(goToBallSKill.getSSM());
        }
    };
}

#endif //DUMBATTACKERTACTIC_H
