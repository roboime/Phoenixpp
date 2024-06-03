#include <iostream>
#include "game_event.pb.h"
// #include "Phoenixpp/base_component.h"
#include "Phoenixpp/vision/udp_vision.h"
// #include "Phoenixpp/base_ui.h"
#include <Phoenixpp/messaging/message_wrapper.h>

#include "Phoenixpp/messaging/message_listener.h"

namespace roboime{

// class Cli : public roboime::BaseUi{
// public:
//     Cli() : roboime::BaseUi::BaseUi(){}
//     void execute() override {
//
//     }
// };

} //roboime
template<typename T>
class Teste {

};

int main()
{
    roboime::messaging::MessageListener m;
    roboime::messaging::Environment env;
    roboime::messaging::MessageWrapper<roboime::messaging::Environment> oi(env);
    std::cout << oi.getMessage().a << std::endl;
    // roboime::Cli cli;
    //roboime::UdpVision udp_vision(1,2);
    // roboime::BaseComponent base;
    SSL_Referee_Game_Event sla;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
