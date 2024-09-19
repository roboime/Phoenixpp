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
        std::string name = "Empty default role";
    public:
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
