//
// Created by ebert on 6/1/2024.
//

#ifndef FOULS_H
#define FOULS_H

#include "message.h"

namespace phoenixpp {
namespace messaging {

struct Fouls {
};
class FoulsWrapper : public Message{
public:
    void forwardTo(FoulsListener* listener) override;
    Fouls getFouls() const {return fouls;}
private:
    Fouls fouls;
};
using FoulsWrapperPtr = std::shared_ptr<FoulsWrapper>;
using FoulsPtr = std::shared_ptr<std::atomic<Fouls>>;

} // messaging
} // phoenixpp

#endif //FOULS_H
