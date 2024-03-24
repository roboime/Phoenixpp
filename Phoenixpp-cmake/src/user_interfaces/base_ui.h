#ifndef BASE_UI_H
#define BASE_UI_H
#include <atomic>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <nlohmann/json.hpp>
#include "../components/base_component.h"
#include "../factories/component_factory.h"

using namespace std;
using json = nlohmann::json;

class BaseUi {
protected:
    vector<thread> threads;
    json config;
    mutex component_mtx;
    atomic<bool> stop;
    double fps;
    unordered_map<string, shared_ptr<BaseComponent>> components;
    ComponentFactory factory;
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

#endif // BASE_UI_H
