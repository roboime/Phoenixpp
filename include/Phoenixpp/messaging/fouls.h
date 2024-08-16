//
// Created by ebert on 6/1/2024.
//

#ifndef FOULS_H
#define FOULS_H

#include "message.h"

namespace phoenixpp {
namespace messaging {

struct Fouls : Message{
    void forwardTo(FoulsListener* listener) override;
    void store(const Fouls& other){}
};
using FoulsPtr = std::shared_ptr<Fouls>;

} // messaging
} // phoenixpp

#endif //FOULS_H
