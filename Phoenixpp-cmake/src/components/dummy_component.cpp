#include "dummy_component.h"

DummyComponent::DummyComponent(atomic<bool>& stop, double fps) : TBaseComponent("dummy", stop, fps)
{

}
DummyMessage DummyComponent::update(DummyMessage message){
    return message;
}
