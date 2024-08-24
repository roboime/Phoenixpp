//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/referee/ssl_referee.h"
#include <iostream>

namespace phoenixpp {
namespace referee {

SSLReferee::SSLReferee(const int &fps) : Referee(fps) {}

void SSLReferee::execute() {
    // std::cout << "Executing SSL Referee" << std::endl;
}

} // referee
} // phoenixpp