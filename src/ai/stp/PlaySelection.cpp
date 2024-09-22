//
// Created by ebert on 7/24/2024.
//

#include "Phoenixpp/ai/stp/PlaySelection.h"
#include "Phoenixpp/messaging/DecisionsStore.h"
#include "Phoenixpp/ai/stp/plays/DumbAttackerPlay.h"
#include <chrono>

#include "Phoenixpp/ai/stp/Play.h"
#include <iostream>
#include <bits/ranges_algo.h>

namespace phoenixpp::ai {

    PlaySelection::PlaySelection(const string &type, const int &fps) : Strategy(type, fps) {
    }
    void PlaySelection::fillDictionary() {
        auto idlePlay = Play("IDLE");
        playDictionary.try_emplace(idlePlay.name, idlePlay);
    }

    //

    void PlaySelection::execute() {
        if(actualPlay->stopConditionReached() || shouldUpdatePlay()) {
            actualPlay = playSelector();
            std::cout << "New play is: " << actualPlay->name << std::endl;
        }

        assignRolesFromPlay(*actualPlay);

        if(!rolesMap.empty()) {
            SkillExecutor::executeSkills(rolesMap, environment);
        }

        messaging::MessagePtr message = std::make_shared<messaging::DecisionsStore>(decisionsStore);
        publisher.distribute(message);
    }

    void PlaySelection::assignRolesFromPlay(const Play& play) { //TODO: create and inspect logic for roleAssigner
        for(const auto& role : play.roles) {
            for(const auto& robot : environment->blueRobots) {
                if(robot.valid == true && !rolesMap.contains(robot.id) && role.name != "Empty default role") {
                    std::cout << "Robot " << robot.id << " gained role " << role << std::endl;
                    rolesMap[robot.id] = role;
                    break;
                }
            }
        }
    }

    bool PlaySelection::checkIfRoleIsPresentInRolesMap(const string& roleName) {
        for (const auto& [key, value] : rolesMap) {
            if (value.name == roleName) {
                return true;
            }
        }

        return false;
    }

    bool PlaySelection::shouldUpdatePlay() {
        // TODO: create logic on how to update play (even if the other play is running)
        return false;
    }

    std::shared_ptr<Play> PlaySelection::playSelector() { // TODO: create logic for play selector
        return std::make_shared<DumbAttackerPlay>();
    }


    void PlaySelection::registerPlay(const Play& newPlay) {
        playDictionary.try_emplace(newPlay.name, newPlay);
    }

} // ai
// phoenixpp