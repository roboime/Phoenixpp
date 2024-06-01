#include <iostream>
#include "game_event.pb.h"
#include "Phoenixpp/base_component.h"
#include "Phoenixpp/vision/udp_vision.h"
#include "Phoenixpp/base_ui.h"

namespace roboime{

class Cli : public roboime::BaseUi{
public:
    Cli() : roboime::BaseUi::BaseUi(){}
    void execute() override {

    }
};

} //roboime
template<typename T>
class Teste {

};

int main()
{
    roboime::Cli cli;
    roboime::UdpVision udp_vision(1,2);
    roboime::BaseComponent base;
    SSL_Referee_Game_Event sla;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
