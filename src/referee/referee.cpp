//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/referee/referee.h"
#include <iostream>

namespace phoenixpp {
namespace referee {

Referee::Referee(const int &fps) : Agent("referee", fps) {}

void Referee::execute() {
    std::cout << "Executing Default Referee" << std::endl;
}

} // referee
} // phoenixpp