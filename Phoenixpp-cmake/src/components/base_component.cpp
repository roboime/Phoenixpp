// BaseComponent.cpp
#include "base_component.h"

template <typename T>
T AnyBaseComponent::getMessage() {
    BaseComponent<T>* typedComponent = dynamic_cast<BaseComponent<T>*>(this);
    if (typedComponent) {
        return typedComponent->getMessage();
    } else {
        throw std::runtime_error("Invalid type conversion at BaseComponent");
    }
}

template <typename T>
BaseComponent<T>::BaseComponent(string component, atomic<bool>& stop, double fps) : stop(stop), parameters(component), fps(fps){
}

template <typename T>
void BaseComponent<T>::execute(){
    T message = update(getMessage());
    {
        unique_lock<shared_mutex> lock(message_mtx);
        this->message = message;
    }
}

template <typename T>
T BaseComponent<T>::getMessage(){
    shared_lock<shared_mutex> lock(message_mtx);
    return message;
}
template <typename T>
void BaseComponent<T>::setComponent(string key, shared_ptr<AnyBaseComponent> newComponent) {
    std::lock_guard<std::mutex> lock(component_mtx);
    components[key] = newComponent;
}

template <typename T>
unordered_map<string, shared_ptr<AnyBaseComponent>> BaseComponent<T>::getComponents(){
    std::lock_guard<std::mutex> lock(component_mtx);
    return components;
}

template <typename T>
bool BaseComponent<T>::isComponentValid(string key) {
    return components.count(key) && components[key] != nullptr;
}
template <typename T>
bool BaseComponent<T>::isComponentPresent(string key) {
    std::lock_guard<std::mutex> lock(component_mtx);
    return components.count(key);
}
template <typename T>
void BaseComponent<T>::setParameter(std::string key, std::any value){
    parameters.set(key, value);
}
template <typename T>
any BaseComponent<T>::getParameter(std::string key){
    return parameters.get(key);
}
template <typename T>
void BaseComponent<T>::saveParameters(){
    parameters.save();
}
template <typename T>
void BaseComponent<T>::loadParameters(){
    parameters.load();
}
template <typename T>
BaseComponent<T>::~BaseComponent(){
    cout << "destruindo base component" << endl;
    for(auto &pair : components){
        pair.second = nullptr;
    }
    components.clear();
    cout << "done base component" << endl;
}
template class BaseComponent<Environment>;
template class BaseComponent<RefereeCommands>;
template class BaseComponent<RobotCommands>;
template class BaseComponent<RobotFeedbackData>;
template class BaseComponent<TransmittedCommands>;
template Environment AnyBaseComponent::getMessage<Environment>();
template RefereeCommands AnyBaseComponent::getMessage<RefereeCommands>();
template RobotCommands AnyBaseComponent::getMessage<RobotCommands>();
template RobotFeedbackData AnyBaseComponent::getMessage<RobotFeedbackData>();
template TransmittedCommands AnyBaseComponent::getMessage<TransmittedCommands>();
