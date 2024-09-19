//
// Created by ebert on 7/24/2024.
//

#ifndef PLAYSELECTION_H
#define PLAYSELECTION_H

#include "Phoenixpp/ai/stp/Play.h"
#include <map>
#include <Phoenixpp/messaging/DecisionsStore.h>

#include "Phoenixpp/ai/strategy.h"

namespace phoenixpp::ai {

class PlaySelection : public Strategy{
public:
    std::unique_ptr<Play> actualPlay = std::make_unique<Play>("Initial default play");
    explicit PlaySelection(const string &type, const int &fps);
    std::unique_ptr<Play> playSelector();
    ~PlaySelection() override = default;
    void execute() override;
    static bool shouldUpdatePlay();
    std::map<std::string, Play> playDictionary;
    void fillDictionary();
    void registerPlay(const Play& newPlay);
    void assignRolesFromPlay(const Play& play);
    std::map<unsigned int, Role> rolesMap;
    messaging::DecisionsStore decisionsStore;
};

} // ai
// phoenixpp

#endif //PLAYSELECTION_H