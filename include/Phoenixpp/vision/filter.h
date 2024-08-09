//
// Created by ebert on 8/8/2024.
//

#ifndef FILTER_H
#define FILTER_H
#include <Phoenixpp/messaging/environment.h>

namespace phoenixpp {
namespace vision {

class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual messaging::Environment execute(messaging::RawEnvironment &rawEnv);
};
using FilterPtr = std::shared_ptr<Filter>;
} // vision
} // phoenixpp

#endif //FILTER_H
