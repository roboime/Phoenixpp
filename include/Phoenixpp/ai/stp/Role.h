//
// Created by lucas on 30/08/2024.
//

#ifndef ROLE_H
#define ROLE_H

#include "Phoenixpp/ai/stp/Tactic.h"
#include <vector>

namespace phoenixpp::ai {

    class Role {
    protected:
        std::vector<Tactic> tactics;

    };
}

#endif //ROLE_H
