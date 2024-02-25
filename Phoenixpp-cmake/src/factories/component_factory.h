#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H
#include <atomic>
#include "../../utils/components/base_component.h"
#include "../../implementations/logic/test_logic/test_logic.h"
#include "../../implementations/vision/test_vision/test_vision.h"

class ComponentFactory {
private:
    atomic<bool> &stop;
    shared_ptr<AnyBaseComponent> createVisionComponent(string implementation, double fps);
    shared_ptr<AnyBaseComponent> createLogicComponent(string implementation, double fps);
    shared_ptr<AnyBaseComponent> createRefereeComponent(string implementation, double fps);
    shared_ptr<AnyBaseComponent> createFeedbackComponent(string implementation, double fps);
    shared_ptr<AnyBaseComponent> createCommunicatorComponent(string implementation, double fps);
public:
    ComponentFactory(atomic<bool> &stop);
    shared_ptr<AnyBaseComponent> createComponent(string type, string implementation, double fps);
};

#endif // COMPONENT_FACTORY_H
