//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/factories/referee_factory.h"
#include <Phoenixpp/referee/referee.h>
#include <Phoenixpp/referee/ssl_referee.h>

namespace phoenixpp {
namespace factories {

core::AgentPtr RefereeFactory::createAgent(const std::string &implementation, const int& fps) {
    if(implementation == "ssl"){
        return std::make_shared<referee::SSLReferee>(fps);
    }
    return std::make_shared<referee::Referee>(fps);
}

} // factories
} // phoenixpp