//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/vision/ssl_vision.h"

#include <iostream>

namespace phoenixpp {
namespace vision {
using std::cout, std::endl;

SSLVision::SSLVision() = default;

void SSLVision::execute() {
    messaging::Environment newEnv = environment;
    if(newEnv.a == 0) newEnv.a++;
    newEnv.a+=2;
    cout << "SSL Vision counter: " << newEnv.a << endl;
    distributeEnvironment(newEnv);
}

} // vision
} // phoenixpp