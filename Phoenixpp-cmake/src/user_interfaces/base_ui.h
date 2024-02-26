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
    mutex mtx;
    atomic<bool> stop;
    double fps;
    unordered_map<string, shared_ptr<AnyBaseComponent>> components;
    ComponentFactory factory;
public:
    BaseUi(double fps);
    bool componentIsValid(string key);
    void setComponent(string key, shared_ptr<AnyBaseComponent> new_component);
    void start();
    void loopComponent(string key, double fps);
    virtual void execute() = 0;
    ~BaseUi();
};

#endif // BASE_UI_H
