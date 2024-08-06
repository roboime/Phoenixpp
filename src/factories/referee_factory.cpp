//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/factories/referee_factory.h"
#include <Phoenixpp/referee/referee.h>
#include <Phoenixpp/referee/ssl_referee.h>

namespace phoenixpp {
namespace factories {

core::AgentPtr RefereeFactory::createAgent(const std::string &implementation) {
    if(implementation == "ssl"){
        return std::make_shared<referee::SSLReferee>();
    }
    return std::make_shared<referee::Referee>();
}

} // factories
} // phoenixpp