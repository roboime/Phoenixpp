#include "cli.h"

using namespace std;

Cli::Cli(json config, double fps) : BaseUi(fps), config(config){
    try{
        shared_ptr<AnyBaseComponent> component;
        // cout << config["vision"] << " " << config["referee"] << " " << config["feedback"] << " " << config["blueLogic"] << " " << config["yellowLogic"] << " " << config["communicator"] << endl;
        components["vision"] = factory.createComponent("vision", config["vision"], 70);
        components["referee"] = factory.createComponent("referee", config["referee"], 70);
        components["feedback"] = factory.createComponent("feedback", config["feedback"], 70);

        components["blueLogic"] = factory.createComponent("logic", config["blueLogic"], 70);;
        if(components["blueLogic"] != nullptr){
            components["blueLogic"]->setComponent("vision", components["vision"]);
            components["blueLogic"]->setComponent("referee", components["referee"]);
            components["blueLogic"]->setComponent("feedback",components["feedback"]);
        }

        components["yellowLogic"] = factory.createComponent("logic", config["yellowLogic"], 70);
        if(components["yellowLogic"] != nullptr){
            components["yellowLogic"]->setComponent("vision", components["vision"]);
            components["yellowLogic"]->setComponent("referee",components["referee"]);
            components["yellowLogic"]->setComponent("feedback", components["feedback"]);
        }

        components["communicator"] = factory.createComponent("communicator", config["communicator"], 70);
        if(components["communicator"] != nullptr){
            components["communicator"]->setComponent("blueLogic", components["blueLogic"]);
            components["communicator"]->setComponent("yellowLogic", components["yellowLogic"]);
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
                std::lock_guard<std::mutex> lock(component_mtx);
                cout << "ui component_mtx locked"<< endl;
                if (!componentIsValid("logic")) break;
                components["logic"]->setParameter("oi.key1", string("olá"));
                components["logic"]->setParameter("oi.key2", (int)2);
                components["logic"]->setParameter("oi.array", vector<double>({1.1, 1.2}));
            }
            cout << "ui component_mtx locked"<< endl;
            break;    
        case 'p':
            {
                std::lock_guard<std::mutex> lock(component_mtx);
                cout << "ui component_mtx locked"<< endl;
                if (!componentIsValid("logic")) break;
                str = any_cast<string>(components["logic"]->getParameter("oi.key1"));
                num = any_cast<int>(components["logic"]->getParameter("oi.key2"));
                vec = any_cast<vector<double>>(components["logic"]->getParameter("oi.array"));
            }
            cout << "ui component_mtx unlocked"<< endl;
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
        lock_guard<mutex> lock(component_mtx);
        if (!componentIsValid("vision")) return;
        env = components["vision"]->getMessage<Environment>();
    }
    //cout << env.rawData << "\n";
    //cout << env.rawData.length() << "\n";
    cout << "received: " << env.received << endl;
    cout << "field lenght: " << env.field.field_length << endl;
    cout << "field width: " << env.field.field_width << endl;
    cout << "ball x: " << env.ball.x << endl;
    cout << "ball y: " << env.ball.y << endl;
}

void Cli::showRobotCommands(){
    RobotCommands robotCommands;
    {
        lock_guard<mutex> lock(component_mtx);
        if (!componentIsValid("blueLogic")) return;
        robotCommands = components["blueLogic"]->getMessage<RobotCommands>();
    }
    cout << "timestamp: " << robotCommands.timestamp << endl;
    //cout << "vel_tang: " << robotCommands.vel_tang << endl;
}
