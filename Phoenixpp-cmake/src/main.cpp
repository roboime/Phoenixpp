#include "user_interfaces/command_line_ui/cli.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
//#include "game_event.pb.h"
// #include "../implementations/logic/test_logic/test_logic.h"

using json = nlohmann::json;
using namespace std;

int main(){
    ifstream file("../configurations/main_settings.json");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    json config;
    file >> config;

    string ui = config["ui"];
    if (ui == "cli"){
        Cli cli(config, 70);
        cli.start();
    }
    else{
        cout << "unrecognized UI configuration";
    }
    return 0;
}
