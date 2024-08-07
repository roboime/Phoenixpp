//
// Created by ebert on 7/24/2024.
//

#include "Phoenixpp/ai/stp/stp.h"
#include <iostream>

namespace phoenixpp {
namespace ai {

STP::STP(const string &type) : Strategy(type) {}
void STP::execute() {
    messaging::Environment env = environment->load();
}

} // ai
} // phoenixpp