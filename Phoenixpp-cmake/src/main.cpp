#include "cli.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include "game_event.pb.h"

using json = nlohmann::json;

int main(){
    std::ifstream file("../configurations/settings.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    json config;
    file >> config;

    std::string ui = config["ui"];
    if (ui == "cli"){
        Cli cli;
        cli.start();
    }
    else{
        cout << "unrecognized UI configuration";
    }
    return 0;
}
