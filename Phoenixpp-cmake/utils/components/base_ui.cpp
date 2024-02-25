#include "base_ui.h"
#include <vector>
#include <thread>

using namespace std;

BaseUi::BaseUi(double fps) : stop(false), fps(fps), factory(stop) {}

void BaseUi::start(){
    vector<thread> threads;
    for (const auto& pair : components){
        threads.push_back(thread([this, &pair]() { loopComponent(pair.first, 70); }));
    }
    cerr << "number of threads: " << threads.size() << endl;
    long long period = (long long)(1000.0 / fps);
    while (!stop.load()){
        execute();
        this_thread::sleep_for(chrono::milliseconds(period));
    }
     for (auto& thread : threads) {
        thread.join();
    }
}

void BaseUi::setComponent(string key, shared_ptr<AnyBaseComponent> new_component){
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& pair : components){
        if(pair.first != key && pair.second->isComponentPresent(key)){
            cerr << "found one\n";
            pair.second->setComponent(key, new_component);
        }
    }
    if (new_component != nullptr){
        // migrating derived components of the old component to the new
        unordered_map<string, shared_ptr<AnyBaseComponent>> derivedComponents = components[key]->getComponents();
        components[key] = new_component;
        for(const auto& pair : derivedComponents){
            components[key]->setComponent(pair.first, pair.second);
        }
    }
    else{
        components[key] = new_component;
    }
}

bool BaseUi::componentIsValid(string key){
    return components.count(key) && components[key] != nullptr;
}

void BaseUi::loopComponent(string key, double fps){
    if(components.count(key)){
        components[key]->start();
    }
    long long period = (long long)(1000.0 / fps);
    while (!stop.load()) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if(componentIsValid(key)){
                components[key]->execute();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(period));
    }
}

BaseUi::~BaseUi() {}