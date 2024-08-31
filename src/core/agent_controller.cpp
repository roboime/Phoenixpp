//
// Created by ebert on 7/17/2024.
//

#include "Phoenixpp/core/agent_controller.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <Phoenixpp/factories/agent_factory.h>
#include <Phoenixpp/factories/agent_factory_registry.h>
#include <Phoenixpp/factories/listener_factory.h>

namespace phoenixpp {
namespace core {
using std::string;

AgentController::AgentController(const string& configFile) :
    stopSign(false), configFile(configFile) {
    initializeAgents();
    initializeThreads();
}

void AgentController::subscribeAgentPair(const std::string &publisherAgent,
    const std::string &subscriberAgent) {
    const auto publisher = agentMap.find(publisherAgent);
    const auto subscriber = agentMap.find(subscriberAgent);
    if(publisher != agentMap.end()) {
        if(subscriber != agentMap.end()){
            const auto listener = subscriber->second->createListener(publisherAgent);
            if(listener != nullptr) {
                publisher->second->subscribe(listener);
            }
        }
    }
}

void AgentController::setAgent(const std::string &key, const std::string &implementation, const int &fps) {
    const std::shared_ptr<factories::AgentFactory> factory = agentFactoryRegistry.getFactory(key);
    AgentPtr agent = factory->createAgent(implementation, fps);
    string type = agent->getType();
    std::unique_lock lock(agentsMutex);
    auto agentIt = agentMap.find(type);
    if(agentIt != agentMap.end()) {
        agent->setPublisher(agentIt->second->getPublisher());
    } else {
        agent->subscribe(messageCollection.createListener(key));

    }
    agentMap[type] = agent;
    lock.unlock();
}

void AgentController::subscribe(const string &agentKey, const messaging::ListenerPtr &listener) {
    auto agentIt = agentMap.find(agentKey);
    if(agentIt != agentMap.end()) {
        agentIt->second->subscribe(listener);
    }
}

void AgentController::initializeThreads() {
    for (const auto& pair : agentMap){
        threads.emplace_back([this, &pair]() { loopAgent(pair.first); });
    }
    std::cout << "Threads initialized: " << threads.size() << std::endl;
}
void AgentController::loopAgent(const std::string &key) {
    std::unique_lock lock(agentsMutex, std::defer_lock);
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    lock.lock();
    int fps =  agentMap[key]->getFPS();
    lock.unlock();
    while(!stopSign.load()) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if(fps == 0) {
            fps = 144; //TODO: solução temporaria ate achar o erro de pq o FPS as vezes fica como lixo
        }

        if(elapsed > 1000/fps) {
            lock.lock();
            agentMap[key]->execute();
            lock.unlock();
            start = std::chrono::high_resolution_clock::now();
        }
        end = std::chrono::high_resolution_clock::now();
    }
}

nlohmann::json AgentController::loadConfig() {
    std::ifstream file(std::filesystem::current_path().parent_path() / "config" / configFile);
    if(!file.is_open()) {
        throw std::runtime_error("Could not open config file");
    }
    nlohmann::json jObject;
    file >> jObject;
    if(jObject.find("agents") == jObject.end()) {
        throw std::runtime_error("Missing 'agents' key in main_settings.json");
    }
    return jObject;
}


void AgentController::initializeAgents() {
    nlohmann::json jObject = loadConfig();
    for (auto& element : jObject.at("agents").items()) {
        if(element.value().find("implementation") == element.value().end()) {
            throw std::runtime_error("Missing 'agents.implementation' key in main_settings.json");
        }
        setAgent(element.key(), element.value().at("implementation"), element.value().at("fps"));
    }
    for (auto& element : jObject.at("agents").items()) {
        if(element.value().find("subscriptions") == element.value().end()) {
            throw std::runtime_error("Missing 'agents.subscriptions' key in main_settings.json");
        }
        for (auto& publisher : element.value().at("subscriptions").items()) {
            subscribeAgentPair(publisher.value(), element.key());
        }
    }
}

AgentController::~AgentController() {
    std::cout << "Destroying AgentController" << std::endl;
    stopSign.store(true);
    std::unique_lock lock(agentsMutex);
    agentMap.clear();
    lock.unlock();
    for(auto& thread : threads) {
        thread.join();
    }
}
} // core
} // phoenixpp