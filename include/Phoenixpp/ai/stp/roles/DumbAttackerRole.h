//
// Created by lucas on 03/09/2024.
//

#ifndef DUMBATTACKER_H
#define DUMBATTACKER_H

#include "Phoenixpp/ai/stp/tactics/DumbAttackerTactic.h"


namespace phoenixpp::ai {

    class DumbAttackerRole : public Role {
    public:
        DumbAttackerRole() {
            name = "Dumb attacker role";
            DumbAttackerTactic dumbAttackerTactic;
            tactics.push_back(dumbAttackerTactic);
        }
    };

}

#endif //DUMBATTACKER_H
