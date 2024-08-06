//
// Created by ebert on 7/24/2024.
//

#ifndef STP_H
#define STP_H
#include "Phoenixpp/ai/strategy.h"
namespace phoenixpp {
namespace ai {

class STP : public Strategy{
public:
    explicit STP(const string &type);
    ~STP() override = default;
    void execute() override;
};

} // ai
} // phoenixpp

#endif //STP_H
