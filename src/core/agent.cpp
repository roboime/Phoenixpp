//
// Created by ebert on 7/18/2024.
//
#include <utility>

#include "Phoenixpp/core/agent.h"

namespace phoenixpp {
namespace core {

Agent::Agent(std::string type, const int &fps) : type(std::move(type)), fps(fps) {}
Agent::Agent(const Agent &agent) : type(agent.type) {}
const std::string &Agent::getType() const { return type; }
void Agent::subscribe(const messaging::ListenerPtr &listener) {
    publisher.addListener(listener);
}
messaging::Publisher Agent::getPublisher() const {
    return publisher;
}
void Agent::setPublisher(const messaging::Publisher &pub) {
    publisher = pub;
}
messaging::ListenerPtr Agent::createListener(const std::string &key) {
    return nullptr;
}
std::size_t AgentHash::operator()(const AgentPtr &agent) const {
    return std::hash<std::string>()(agent->getType());
}
bool AgentEqual::operator()(const AgentPtr &a, const AgentPtr &b) const {
    return a->getType() == b->getType();
}

} // core
} // phoenixpp