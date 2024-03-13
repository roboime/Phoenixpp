#ifndef DUMMY_COMPONENT_H
#define DUMMY_COMPONENT_H
#include "base_component.h"
#include "./messages/dummy_message.h"

class DummyComponent : public TBaseComponent<DummyMessage> {
public:
    DummyComponent(atomic<bool>& stop, double fps);
    void start() override {};
    DummyMessage update(DummyMessage message) override;
    ~DummyComponent() {}
};

#endif // DUMMY_COMPONENT_H
