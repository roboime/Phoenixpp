//
// Created by lucas on 03/09/2024.
//

#ifndef DUMBATTACKERPLAY_H
#define DUMBATTACKERPLAY_H
#include "Phoenixpp/ai/stp/Play.h"
#include "Phoenixpp/ai/stp/roles/DumbAttackerRole.h"

namespace phoenixpp::ai {

    class DumbAttackerPlay : public Play {

    public:
        DumbAttackerPlay() : Play("DumbAttackerPlay") {
            DumbAttackerRole dumbAttackerRole;
            roles.push_back(dumbAttackerRole);
        }
        bool stopConditionReached() override{
            return false;
        }


    };
}


#endif //DUMBATTACKERPLAY_H
