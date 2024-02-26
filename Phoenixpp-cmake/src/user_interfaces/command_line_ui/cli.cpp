#include "cli.h"

using namespace std;

Cli::Cli(json config, double fps) : BaseUi(fps), config(config){
    try{
        shared_ptr<AnyBaseComponent> component;
        // cout << config["vision"] << " " << config["referee"] << " " << config["feedback"] << " " << config["blueLogic"] << " " << config["yellowLogic"] << " " << config["communicator"] << endl;
        component = factory.createComponent("vision", config["vision"], 70);
        if(component != nullptr){
            cerr << "setting vision component" << endl;
            components["vision"] = component;
        }
        component = factory.createComponent("referee", config["referee"], 70);
        if(component != nullptr){
            components["referee"] = component;
        }
        component = factory.createComponent("feedback", config["feedback"], 70);
        if(component != nullptr){
            components["feedback"] = component;
        }
        component = factory.createComponent("logic", config["blueLogic"], 70);
        if(component != nullptr){
            components["blueLogic"] = component;
            components["blueLogic"]->setComponent("vision", components.count("vision")?components["vision"]:nullptr);
            components["blueLogic"]->setComponent("referee", components.count("referee")?components["referee"]:nullptr);
            components["blueLogic"]->setComponent("feedback", components.count("feedback")?components["feedback"]:nullptr);
        }
        component = factory.createComponent("logic", config["yellowLogic"], 70);
        if(component != nullptr){
            components["yellowLogic"] = component;
            components["yellowLogic"]->setComponent("vision", components.count("vision")?components["vision"]:nullptr);
            components["yellowLogic"]->setComponent("referee", components.count("referee")?components["referee"]:nullptr);
            components["yellowLogic"]->setComponent("feedback", components.count("feedback")?components["feedback"]:nullptr);
        }
        component = factory.createComponent("communicator", config["communicator"], 70);
        if(component != nullptr){
            components["communicator"] = component;
            components["communicator"]->setComponent("blueLogic", components.count("blueLogic")?components["blueLogic"]:nullptr);
            components["communicator"]->setComponent("yellowLogic", components.count("yellowLogic")?components["yellowLogic"]:nullptr);
        }
    }
    catch (exception ex){
        cerr << "Error instanciating components: " << ex.what() << endl;
        const std::type_info& typeInfo = typeid(ex);
        std::cerr << "Exception type: " << typeInfo.name() << std::endl;
        std::cerr << "Function: " << __PRETTY_FUNCTION__ << std::endl;
    }
}

void Cli::execute(){
    char chr, chr2;
    string str, key, type, imp;
    int num;
    vector<double> vec;

    cout << "show environment: (e);\nshow robot commands: (r);\nstop: (s)" << endl;
    cin >> chr;
    shared_ptr<AnyBaseComponent> ptr = nullptr;
    switch (chr){
        case 'c':
            cin >> key;
            cin >> imp;
            if(key == "blueLogic" || key == "yellowLogic") type = "logic";
            else type = key;
            setComponent(key, factory.createComponent(type, imp, 70));
            break;
        case 'e':
            cerr << "show environment" << endl;
            showEnvironment();
            break;
        case 'r':
            showRobotCommands();
            break;
        case 's':
            stop.store(true);
            break;
        case 't':
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!componentIsValid("logic")) break;
                components["logic"]->setParameter("oi.key1", string("olá"));
                components["logic"]->setParameter("oi.key2", (int)2);
                components["logic"]->setParameter("oi.array", vector<double>({1.1, 1.2}));
            }
            break;    
        case 'p':
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!componentIsValid("logic")) break;
                str = any_cast<string>(components["logic"]->getParameter("oi.key1"));
                num = any_cast<int>(components["logic"]->getParameter("oi.key2"));
                vec = any_cast<vector<double>>(components["logic"]->getParameter("oi.array"));
            }
            cout << str << "\n";
            cout << num << "\n";
            for(auto el : vec) cout << el << " ";
            cout << "\n";
            break;
        default:
            break;
    }
}

void Cli::showEnvironment(){
    Environment env;
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (!componentIsValid("vision")) return;
        env = components["vision"]->getMessage<Environment>();
    }
    cout << env.rawData << "\n";
    // cout << "field lenght: " << env.field_lenght << endl;
    // cout << "field width: " << env.field_width << endl;
}

void Cli::showRobotCommands(){
    RobotCommands robotCommands;
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (!componentIsValid("blueLogic")) return;
        robotCommands = components["blueLogic"]->getMessage<RobotCommands>();
    }
    cout << "vel_norm: " << robotCommands.vel_norm << endl;
    cout << "vel_tang: " << robotCommands.vel_tang << endl;
}