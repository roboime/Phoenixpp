//
// Created by ebert on 5/30/2024.
//

#ifndef BASE_UI_H
#define BASE_UI_H
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "base_component.h"

using json = nlohmann::json;
using std::vector, std::thread, std::mutex, std::atomic, std::string, std::shared_ptr;

namespace roboime {

class BaseUi {
protected:
    vector<thread> threads;
    json config;
    mutex component_mtx;
    atomic<bool> stop;
    double fps;
    std::unordered_map<string, shared_ptr<BaseComponent>> components;
    //ComponentFactory factory;
    bool componentIsValid(string key);
public:
    BaseUi();
    void setComponent(string key, shared_ptr<BaseComponent> new_component);
    void start();
    void finish();
    void loopComponent(string key, double fps);
    virtual void execute() = 0;
    ~BaseUi();
};

} // roboime

#endif //BASE_UI_H
