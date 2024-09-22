//
// Created by lucas on 30/08/2024.
//

#ifndef TACTIC_H
#define TACTIC_H

#include <Phoenixpp/messaging/DecisionsStore.h>
#include <Phoenixpp/messaging/environment.h>

#include "Phoenixpp/ai/stp/Skill.h"

namespace phoenixpp::ai {

    class Tactic {
    public:
        void execute(messaging::EnvironmentPtr environment, std::shared_ptr<messaging::DecisionsStore> message) {
            if(!ssms.empty()) {
                ssms[0].update(environment, message);
            }
        }
    protected:
        std::vector<SkillStateMachine> ssms;


    };
}

#endif //TACTIC_H
