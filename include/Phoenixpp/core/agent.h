//
// Created by ebert on 7/17/2024.
//

#ifndef AGENT_H
#define AGENT_H

#include "Phoenixpp/messaging/publisher.h"
#include <unordered_map>

namespace phoenixpp {
namespace core {
class Agent {
public:
    explicit Agent(std::string type);
    Agent(const Agent &agent);
    void subscribe(const messaging::ListenerPtr &listener);
    messaging::Publisher getPublisher() const;
    void setPublisher(const messaging::Publisher &pub);
    const std::string &getType() const;
    virtual messaging::ListenerPtr createListener(const std::string &key);
    virtual void execute() {};
    virtual ~Agent() = default;
protected:
    messaging::Publisher publisher;
    std::string type;
};
using AgentPtr = std::shared_ptr<Agent>;

struct AgentHash {
    std::size_t operator()(const AgentPtr &agent) const;
};

struct AgentEqual {
    bool operator()(const AgentPtr &a, const AgentPtr &b) const;
};


} // core
} // phoenixpp

#endif //AGENT_H
