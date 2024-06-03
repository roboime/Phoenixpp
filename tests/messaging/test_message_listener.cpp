//
// Created by ebert on 6/1/2024.
//
#include <gtest/gtest.h>
#include "Phoenixpp/messaging/message_listener.h"
#include "Phoenixpp/messaging/message_publisher.h"

class EnvironmentListener : public roboime::messaging::MessageListener{
private:
    roboime::messaging::Environment env;
public:
    void updateVisit(roboime::messaging::Environment env) override {
        this->env = env;
        std::cout << "env update\n";
    }
};

class MessageListenerTest : public ::testing::Test{
protected:
    EnvironmentListener listener;
};

TEST_F(MessageListenerTest, UpdateVisit) {
    listener.updateVisit(roboime::messaging::Environment{});
}

class MessagePublisherTest : public ::testing::Test {
protected:
    roboime::messaging::MessagePublisher<roboime::messaging::Message> publisher;
};

TEST_F(MessagePublisherTest, NotifyListeners) {
}

TEST_F(MessagePublisherTest, SubscribeUnsubscribe) {
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
