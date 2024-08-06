//
// Created by ebert on 7/17/2024.
//

#ifndef AGENT_CONTROLLER_H
#define AGENT_CONTROLLER_H

#include <condition_variable>
#include <thread>
#include <unordered_map>
#include <vector>
#include <nlohmann/adl_serializer.hpp>
#include <Phoenixpp/factories/agent_factory_registry.h>
#include <Phoenixpp/messaging/message_collection.h>
#include "Phoenixpp/core/agent.h"

namespace phoenixpp {
namespace core {
using std::unordered_map, std::atomic, std::string;
class AgentController{
public:
    AgentController();
    ~AgentController();
    void setAgent(const string &key,const string &implementation);
    void subscribe(const string &agentKey, const messaging::ListenerPtr &);
    messaging::MessageCollection &getMessageCollection() {return messageCollection;}
private:
    void initializeThreads();
    void initializeAgents();
    nlohmann::json loadConfig();
    void loopAgent(const std::string &key);
    void subscribeAgentPair(const std::string &publisherAgent, const std::string &subscriberAgent);
    factories::AgentFactoryRegistry agentFactoryRegistry;
    unordered_map<string, AgentPtr> agentMap;
    unordered_map<string, double> fpsMap;
    std::vector<std::thread> threads;
    atomic<bool> stopSign;
    std::mutex agentsMutex;
    static const string configFile;
    messaging::MessageCollection messageCollection;
};

} // core
} // phoenixpp

#endif //AGENT_CONTROLLER_H
