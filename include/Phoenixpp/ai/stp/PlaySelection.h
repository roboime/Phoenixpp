//
// Created by ebert on 7/24/2024.
//

#ifndef PLAYSELECTION_H
#define PLAYSELECTION_H

#include "Phoenixpp/ai/stp/Play.h"
#include <map>
#include "Phoenixpp/ai/strategy.h"

namespace phoenixpp::ai {

class PlaySelection : public Strategy{
public:
    Play actualPlay = Play("Initial play");
    explicit PlaySelection(const string &type, const int &fps);
    ~PlaySelection() override = default;
    void execute() override;
    static bool shouldUpdatePlay();
    std::map<std::string, Play> playDictionary;
    void fillDictionary();
    void registerPlay(const Play& newPlay);
};

} // ai
// phoenixpp

#endif //PLAYSELECTION_H