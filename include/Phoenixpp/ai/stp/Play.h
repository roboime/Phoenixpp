//
// Created by lucas on 30/08/2024.
//

#ifndef PLAY_H
#define PLAY_H

#include <utility>
#include <vector>
#include "Phoenixpp/ai/stp/Role.h"


namespace phoenixpp::ai {

    class Play {
    public:
        std::vector<Role> roles;
        std::string name;
        virtual bool stopConditionReached() {
            return true;
        };
        explicit Play(std::string name) : name(std::move(name)) {
        }
        virtual ~Play() = default;
    };
}

#endif //PLAY_H
