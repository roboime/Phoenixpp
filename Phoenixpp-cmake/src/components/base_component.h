#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H
#include <string>
#include <memory>
#include <atomic>
#include <unordered_map>
#include <any>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include "../utils/parameters_manager.h"
#include "./messages/environment.h"
#include "./messages/referee_commands.h"
#include "./messages/robot_commands.h"
#include "./messages/robot_feedback_data.h"
#include "./messages/dummy_message.h"

using namespace std;

class BaseComponent{
public:
    template <typename T>
    T getMessage();
    virtual bool isComponentValid(string key) = 0;
    virtual bool isComponentPresent(string key) = 0;
    virtual void start() = 0;
    virtual void execute() = 0;
    virtual void setComponent(string key, shared_ptr<BaseComponent> newComponent) = 0;
    virtual void setParameter(std::string key, std::any value) = 0;
    virtual any getParameter(std::string key) = 0;
    virtual unordered_map<string, shared_ptr<BaseComponent>> getComponents() = 0;
    virtual void saveParameters() = 0;
    virtual void loadParameters() = 0;
    virtual ~BaseComponent() {};
};

template <typename T>
class TBaseComponent : public BaseComponent{
protected:
    T message;
    shared_mutex message_mtx;
    mutex component_mtx;
    atomic<bool> &stop;
    unordered_map<string, shared_ptr<BaseComponent>> components;
    ParametersManager parameters;
    double fps;
public:
    TBaseComponent(string component, atomic<bool>& stop, double fps);
    bool isComponentValid(string key);
    bool isComponentPresent(string key);
    T getMessage();
    void execute() override;
    virtual T update(T message) = 0;
    unordered_map<string, shared_ptr<BaseComponent>> getComponents() override;
    void setComponent(string key, shared_ptr<BaseComponent> newComponent) override;
    void setParameter(std::string key, std::any value) override;
    any getParameter(std::string key) override;
    void saveParameters() override;
    void loadParameters() override;
    ~TBaseComponent();
};

#endif // BASE_COMPONENT_H
