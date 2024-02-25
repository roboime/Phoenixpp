#ifndef CLI_H
#define CLI_H
#include <atomic>
#include <memory>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "../../../utils/components/base_ui.h"
#include "../../../src/factories/component_factory.h"
#include "../../logic/test_logic/test_logic.h"
#include "../../vision/test_vision/test_vision.h"

using namespace std;
using json = nlohmann::json;

class Cli : public BaseUi{
private:
    json config;
    void showEnvironment();
    void showRobotCommands();
public:
    Cli(json, double fps);
    void execute() override;
    ~Cli() {}
};

#endif // CLI_H
