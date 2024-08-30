//
// Created by lucas on 30/08/2024.
//

#ifndef PLAY_H
#define PLAY_H

#include <utility>

#include "Phoenixpp/ai/stp/Role.h"


namespace phoenixpp::ai {

    class Play {
        Role roles[6];

    public:
        std::string name;
        explicit Play(std::string name) : name(std::move(name)) {
        }

    };
}

#endif //PLAY_H
