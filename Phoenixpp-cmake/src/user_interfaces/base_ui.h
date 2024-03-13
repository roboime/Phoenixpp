#ifndef BASE_UI_H
#define BASE_UI_H
#include <atomic>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <utility>
#include "../components/base_component.h"
#include "../factories/component_factory.h"

using namespace std;

class BaseUi {
protected:
    mutex component_mtx;
    atomic<bool> stop;
    double fps;
    unordered_map<string, shared_ptr<BaseComponent>> components;
    ComponentFactory factory;
    bool componentIsValid(string key);
public:
    BaseUi(double fps);
    void setComponent(string key, shared_ptr<BaseComponent> new_component);
    void start();
    void loopComponent(string key, double fps);
    virtual void execute() = 0;
    ~BaseUi();
};

#endif // BASE_UI_H
