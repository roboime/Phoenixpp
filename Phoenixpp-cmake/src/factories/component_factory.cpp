#include "component_factory.h"

ComponentFactory::ComponentFactory(atomic<bool> &stop) : stop(stop) {}

shared_ptr<AnyBaseComponent> ComponentFactory::createComponent(string type, string implementation, double fps){
    if (implementation == "none"){
        return nullptr;
    }
    if(type == "vision"){
        return createVisionComponent(implementation, fps);
    }
    if(type == "logic"){
        return createLogicComponent(implementation, fps);
    }
    if(type == "referee"){  
        return createRefereeComponent(implementation, fps);
    }
    if(type == "feedback"){
        return createFeedbackComponent(implementation, fps);
    }
    if(type == "comunicator"){
        return createCommunicatorComponent(implementation, fps);
    }
    else{
        return nullptr;
    }
}

shared_ptr<AnyBaseComponent> ComponentFactory::createVisionComponent(string implementation, double fps){
    if (implementation == "testVision"){
        return make_shared<TestVision>(stop, fps);
    }
    if (implementation == "udpVision"){
        return make_shared<UdpVision>(stop, fps);
    }
    else {
        return nullptr;
    }
}
shared_ptr<AnyBaseComponent> ComponentFactory::createLogicComponent(string implementation, double fps){
    if (implementation == "testLogic"){
        return make_shared<TestLogic>(stop, fps);
    }
    else {
        return nullptr;
    }
}
shared_ptr<AnyBaseComponent> ComponentFactory::createRefereeComponent(string implementation, double fps){
    return nullptr;
}
shared_ptr<AnyBaseComponent> ComponentFactory::createFeedbackComponent(string implementation, double fps){
    return nullptr;
}
shared_ptr<AnyBaseComponent> ComponentFactory::createCommunicatorComponent(string implementation, double fps){
    return nullptr;
}
