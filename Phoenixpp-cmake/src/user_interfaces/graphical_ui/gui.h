#ifndef GUI_H
#define GUI_H
#include <atomic>
#include <memory>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "../base_ui.h"
#include "../../factories/component_factory.h"

using namespace std;
using json = nlohmann::json;

class Gui : public BaseUi {
public:
    Gui();
    void execute() override;
    ~Gui();
};

#endif // GUI_H
