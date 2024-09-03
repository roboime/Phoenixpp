//
// Created by ebert on 7/24/2024.
//

#include "Phoenixpp/ai/stp/PlaySelection.h"
#include "Phoenixpp/messaging/DecisionsStore.h"
#include "Phoenixpp/ai/stp/plays/DumbAttackerPlay.h"
#include <chrono>

#include "Phoenixpp/ai/stp/Play.h"
#include <iostream>

namespace phoenixpp::ai {

    PlaySelection::PlaySelection(const string &type, const int &fps) : Strategy(type, fps) {
    }
    int getSecondsOfTheActualHour() { // TODO: função temporaria para mudar play de 5 em 5 segundos
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm* parts = std::localtime(&now_c);

        // Extract the current second of the minute
        return parts->tm_sec;

    }

    bool temporaryFunctionToChangePlay() { // TODO: função temporaria para mudar play de 5 em 5 segundos
        bool flag = false;

        if (getSecondsOfTheActualHour() % 5 == 0) {
            flag = true;
        } else {
            flag = false;
        }

        return flag;
    }

    void PlaySelection::fillDictionary() {
        auto idlePlay = Play("IDLE");
        playDictionary.try_emplace(idlePlay.name, idlePlay);
    }


    void PlaySelection::execute() {
        if (shouldUpdatePlay()) {
            std::string playName = std::format("{} {}","New play number ", std::to_string(getSecondsOfTheActualHour()));
            if(playName != actualPlay->name) {
                actualPlay = new Play(playName);
                std::cout << "New play is: " << actualPlay->name << std::endl;
            }
        }

        auto dumbAttackerPlay = DumbAttackerPlay();
        actualPlay = &dumbAttackerPlay;
        fillDecisionsFromPlay(actualPlay);

        messaging::MessagePtr message = std::make_shared<messaging::DecisionsStore>(decisionsStore);
        publisher.distribute(message);
    }

    void PlaySelection::fillDecisionsFromPlay(Play* play) {
        for(auto role : play)
    }

    bool PlaySelection::shouldUpdatePlay() {
        return temporaryFunctionToChangePlay();
    }

    void PlaySelection::registerPlay(const Play& newPlay) {
        playDictionary.try_emplace(newPlay.name, newPlay);
    }

} // ai
// phoenixpp