//
// Created by lucas on 30/08/2024.
//

#ifndef ROLE_H
#define ROLE_H

#include "Phoenixpp/ai/stp/Tactic.h"
#include <vector>
#include <iostream>

namespace phoenixpp::ai {

    class Role {
    protected:
        std::vector<Tactic> tactics;
    public:
        friend inline std::ostream& operator<<(std::ostream& os, const Role& dt);
    };

    std::ostream& operator<<(std::ostream& os, const Role& obj) {
        os << "Default empty role";
        return os;
    }
}

#endif //ROLE_H
