#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H
#include <atomic>
#include "../components/base_component.h"
#include "../components/implementations/logic/test_logic/test_logic.h"
#include "../components/implementations/vision/test_vision/test_vision.h"
#include "../components/implementations/vision/udp_vision/grsim_vision.h"
#include "../components/implementations/vision/udp_vision/real_game_vision.h"
#include "../components/implementations/communicator/udp_communicator/udp_communicator.h"
#include "../components/dummy_component.h"

class ComponentFactory {
private:
    atomic<bool> &stop;
    shared_ptr<BaseComponent> createVisionComponent(string implementation, double fps);
    shared_ptr<BaseComponent> createLogicComponent(string implementation, double fps);
    shared_ptr<BaseComponent> createRefereeComponent(string implementation, double fps);
    shared_ptr<BaseComponent> createFeedbackComponent(string implementation, double fps);
    shared_ptr<BaseComponent> createCommunicatorComponent(string implementation, double fps);
public:
    ComponentFactory(atomic<bool> &stop);
    shared_ptr<BaseComponent> createComponent(string type, string implementation, double fps);
};

#endif // COMPONENT_FACTORY_H
