//
// Created by ebert on 6/1/2024.
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "message.h"
#include <atomic>

namespace phoenixpp {
namespace messaging {

struct Environment{
    int a;
};
class EnvironmentWrapper : public Message {
public:
    explicit EnvironmentWrapper(const Environment env) : environment(env) {};
    ~EnvironmentWrapper() override = default;
    void forwardTo(EnvironmentListener* listener) override;
    Environment getEnvironment() const {return environment;}
private:
    Environment environment;
};
using EnvironmentWrapperPtr = std::shared_ptr<EnvironmentWrapper>;
using EnvironmentPtr = std::shared_ptr<std::atomic<Environment>>;

} // messaging
} // phoenixpp

#endif //ENVIRONMENT_H
