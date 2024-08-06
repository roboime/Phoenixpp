//
// Created by ebert on 7/18/2024.
//

#ifndef SSL_REFEREE_H
#define SSL_REFEREE_H
#include "referee.h"

namespace phoenixpp {
namespace referee {

class SSLReferee : public Referee {
public:
    SSLReferee() = default;
    ~SSLReferee() override = default;
    void execute() override;
};

} // referee
} // phoenixpp

#endif //SSL_REFEREE_H
