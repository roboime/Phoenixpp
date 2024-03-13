#include "component_factory.h"

ComponentFactory::ComponentFactory(atomic<bool> &stop) : stop(stop) {}

shared_ptr<BaseComponent> ComponentFactory::createComponent(string type, string implementation, double fps){
    if (implementation == "none"){
        return make_shared<DummyComponent>(stop, fps);
    }
    if(type == "vision"){
        return createVisionComponent(implementation, fps);
    }
    else if(type == "logic"){
        return createLogicComponent(implementation, fps);
    }
    else if(type == "referee"){
        return createRefereeComponent(implementation, fps);
    }
    else if(type == "feedback"){
        return createFeedbackComponent(implementation, fps);
    }
    else if(type == "communicator"){
        return createCommunicatorComponent(implementation, fps);
    }
    else{
        return nullptr;
    }
}

shared_ptr<BaseComponent> ComponentFactory::createVisionComponent(string implementation, double fps){
    if (implementation == "testVision"){
        return make_shared<TestVision>(stop, fps);
    }
    else if (implementation == "grsimVision"){
        return make_shared<UdpVision>(stop, fps);
    }
    else if (implementation == "realGameVision"){
        return make_shared<RealGameVision>(stop, fps);
    }
    else {
        return make_shared<DummyComponent>(stop, fps);
    }
}
shared_ptr<BaseComponent> ComponentFactory::createLogicComponent(string implementation, double fps){
    if (implementation == "testLogic"){
        return make_shared<TestLogic>(stop, fps);
    }
    else {
        return make_shared<DummyComponent>(stop, fps);
    }
}
shared_ptr<BaseComponent> ComponentFactory::createRefereeComponent(string implementation, double fps){
    return make_shared<DummyComponent>(stop, fps);
}
shared_ptr<BaseComponent> ComponentFactory::createFeedbackComponent(string implementation, double fps){
    return make_shared<DummyComponent>(stop, fps);
}
shared_ptr<BaseComponent> ComponentFactory::createCommunicatorComponent(string implementation, double fps){
    if (implementation == "udpCommunicator"){
        return make_shared<UdpCommunicator>(stop, fps);
    }
    else {
        return make_shared<DummyComponent>(stop, fps);
    }
}
