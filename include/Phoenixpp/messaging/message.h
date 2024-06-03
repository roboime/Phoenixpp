//
// Created by ebert on 6/1/2024.
//

#ifndef MESSAGE_H
#define MESSAGE_H



namespace roboime{
namespace messaging {

class MessageListener;

class Message {
public:
    virtual void accept(MessageListener *listener) = 0;
    virtual ~Message() = default;
};

} // messaging
}// roboime

#endif //MESSAGE_H
