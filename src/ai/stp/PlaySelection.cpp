//
// Created by ebert on 7/24/2024.
//

#include "Phoenixpp/ai/stp/PlaySelection.h"

#include <chrono>

#include "Phoenixpp/ai/stp/Play.h"
#include <iostream>

namespace phoenixpp::ai {

    bool temporaryFunctionToChangePlay() {
        bool flag = false;

        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm* parts = std::localtime(&now_c);

        // Extract the current second of the minute
        int current_second = parts->tm_sec;

        // Set the flag to true every 5 seconds
        if (current_second % 5 == 0) {
            flag = true;
        } else {
            flag = false;
        }

        return flag;
    }

    PlaySelection::PlaySelection(const string &type, const int &fps) : Strategy(type, fps) {
    }
    void PlaySelection::execute() {
        // messaging::Environment env = environment->load();
        if (shouldUpdatePlay()) {
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm* parts = std::localtime(&now_c);

            // Extract the current second of the minute
            int current_second = parts->tm_sec;

            std::string playName = std::format("{} {}","New play number ", std::to_string(current_second));
            if(playName != actualPlay.name) {

                actualPlay = Play(playName);
                std::cout << "New play is: " << actualPlay.name << std::endl;
            }
        }
    }

    bool PlaySelection::shouldUpdatePlay() {
        return temporaryFunctionToChangePlay();
    }


} // ai
// phoenixpp