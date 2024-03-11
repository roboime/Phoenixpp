#include "user_interfaces/graphical_ui/gui.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

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

    Gui gui(config, 70);
    gui.start();
    return 0;
}
