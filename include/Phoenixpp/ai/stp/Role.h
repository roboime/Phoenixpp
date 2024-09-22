//
// Created by lucas on 30/08/2024.
//

#ifndef ROLE_H
#define ROLE_H

#include "Phoenixpp/ai/stp/Tactic.h"
#include <vector>
#include <iostream>
#include <Phoenixpp/messaging/DecisionsStore.h>
#include <Phoenixpp/messaging/environment.h>

namespace phoenixpp::ai {

    class Role {
    protected:
        Tactic* currentTactic;
        std::vector<Tactic> tactics;
    public:
        std::string name = "Empty default role";
        void execute(messaging::EnvironmentPtr environment, std::shared_ptr<messaging::DecisionsStore> message) {
            tactics[0].execute(environment, message); //TODO: consertar o currentTactic, está indo para o espaço
            // currentTactic->execute(environment);
        }
        std::string getName() {
            return name;
        }
        friend inline std::ostream& operator<<(std::ostream& os, const Role& obj);
    };

    std::ostream& operator<<(std::ostream& os, const Role& obj) {
        os << obj.name;
        return os;
    }
}

#endif //ROLE_H
