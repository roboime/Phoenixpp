#include "user_interfaces/command_line_ui/cli.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
//#include <QCoreApplication>
//#include <QApplication>
// #include "game_event.pb.h"
// #include "../implementations/logic/test_logic/test_logic.h"

using json = nlohmann::json;
using namespace std;

int main(int argc, char**argv){
    Cli cli;
    cli.start();
    cli.loop();
    cli.finish();
    return 0;
}
