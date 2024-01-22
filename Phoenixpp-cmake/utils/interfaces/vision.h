#ifndef VISION_H
#define VISION_H
#include <string>
#include "../structs/environment.h"

class Vision {
public:
    virtual void startReceiving() = 0;
    virtual Environment getEnvironment() = 0;
    virtual void setFilter(std::string filter) = 0;
    virtual ~Vision() {}
};

#endif // VISION_H
