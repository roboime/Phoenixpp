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
            auto dumbAttackerTactic = DumbAttackerTactic();
            tactics.push_back(dumbAttackerTactic);
        }
        friend std::ostream& operator<<(std::ostream& os, const DumbAttackerRole& dt);
    };

    std::ostream& operator<<(std::ostream& os, const DumbAttackerRole& obj) {
        os << "Dumb attacker role";
        return os;
    }
}

#endif //DUMBATTACKER_H
