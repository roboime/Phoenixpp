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
    ifstream file("../configurations/main_settings.json");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    json config;
    file >> config;

    Cli cli(config, 70);
    cli.start();

    return 0;
}
