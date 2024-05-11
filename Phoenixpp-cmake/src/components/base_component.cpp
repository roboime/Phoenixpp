#include "base_component.h"

template <typename T>
T BaseComponent::getMessage() {
    TBaseComponent<T>* typedComponent = dynamic_cast<TBaseComponent<T>*>(this);
    if (typedComponent) {
        return typedComponent->getMessage();
    } else {
        throw std::runtime_error("Invalid type conversion at BaseComponent");
    }
}

template <typename T>
TBaseComponent<T>::TBaseComponent(string component, atomic<bool>& stop, double fps) : stop(stop), parameters(component), fps(fps){
}

template <typename T>
void TBaseComponent<T>::execute(){
    T message = update(getMessage());
    {
        unique_lock<shared_mutex> lock(message_mtx);
        this->message = message;
    }
}

template <typename T>
T TBaseComponent<T>::getMessage(){
    shared_lock<shared_mutex> lock(message_mtx);
    return message;
}

template <typename T>
void TBaseComponent<T>::setComponent(string key, shared_ptr<BaseComponent> newComponent) {
    std::lock_guard<std::mutex> lock(component_mtx);
    components[key] = newComponent;
}

template <typename T>
unordered_map<string, shared_ptr<BaseComponent>> TBaseComponent<T>::getComponents(){
    std::lock_guard<std::mutex> lock(component_mtx);
    return components;
}

template <typename T>
bool TBaseComponent<T>::isComponentValid(string key) {
    return components.count(key) && components[key] != nullptr;
}
template <typename T>
bool TBaseComponent<T>::isComponentPresent(string key) {
    std::lock_guard<std::mutex> lock(component_mtx);
    return components.count(key);
}
template <typename T>
void TBaseComponent<T>::setParameter(std::string key, std::any value){
    parameters.set(key, value);
}
template <typename T>
any TBaseComponent<T>::getParameter(std::string key){
    return parameters.get(key);
}
template <typename T>
void TBaseComponent<T>::saveParameters(){
    parameters.save();
}
template <typename T>
void TBaseComponent<T>::loadParameters(){
    parameters.load();
}
template <typename T>
TBaseComponent<T>::~TBaseComponent(){
    cout << "destruindo base component" << endl;
    for(auto &pair : components){
        pair.second = nullptr;
    }
    components.clear();
    cout << "done base component" << endl;
}
template class TBaseComponent<RawEnvironment>;
template class TBaseComponent<Environment>;
template class TBaseComponent<RefereeCommands>;
template class TBaseComponent<RobotCommands>;
template class TBaseComponent<RobotFeedbackData>;
template class TBaseComponent<TransmittedCommands>;
template class TBaseComponent<DummyMessage>;
template RawEnvironment BaseComponent::getMessage<RawEnvironment>();
template Environment BaseComponent::getMessage<Environment>();
template RefereeCommands BaseComponent::getMessage<RefereeCommands>();
template RobotCommands BaseComponent::getMessage<RobotCommands>();
template RobotFeedbackData BaseComponent::getMessage<RobotFeedbackData>();
template TransmittedCommands BaseComponent::getMessage<TransmittedCommands>();
template DummyMessage BaseComponent::getMessage<DummyMessage>();
