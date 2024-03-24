#include "cli.h"
#include <ncurses.h>
#include <unistd.h> // For UNIX system calls

using namespace std;

Cli::Cli() : BaseUi(){
}

void Cli::eloMecTester(unique_lock<mutex> &components_lock){
    mutex mtx;
    condition_variable cv, cv2;
    bool chrReady;
    thread curThread;
    char chr, chr2;
    unique_lock<mutex> lock(mtx, defer_lock);
    char keys[] = {'w', 'a', 's', 'd', 'q', 'e', ' '};
    system("stty raw");
    chr2 = 0;
    chrReady = false;
    curThread = thread([&chr, &chrReady, &cv](){
            read(STDIN_FILENO, &chr, 1);
            chrReady = true;
            cv.notify_all();
        });
    while (true) {
        lock.lock();
        if (cv.wait_for(lock, chrono::milliseconds(20), [&chrReady]{return chrReady;})) {
            if (chr == 27) { // ESC KITA
                lock.unlock();
                curThread.join();
                cerr << "\r";
                break;
            }
            else if (chr2 != chr){
                //cerr << "\r";
                components_lock.lock();
                for(int i=0;i<sizeof(keys)/sizeof(keys[0]);i++){
                    if(keys[i] == chr){
                        components["navigation"]->setParameter(string(1, chr), true);
                    }
                }
                //cerr << any_cast<bool>(components["navigation"]->getParameter("w")) << endl;
                components_lock.unlock();
            }
            lock.unlock();
            curThread.join();
            cerr << "\r";
            this_thread::sleep_for(chrono::milliseconds(5));
            chr2 = chr;
            chrReady = false;
            curThread = thread([&chr, &chrReady, &cv](){
                read(STDIN_FILENO, &chr, 1);
                chrReady = true;
                cv.notify_all();
            });
            continue;
        }
        else if(chr2 != 0){
            //cerr << "\r";
            components_lock.lock();
            for(int i=0;i<sizeof(keys)/sizeof(keys[0]);i++){
                components["navigation"]->setParameter(string(1, keys[i]), false);
            }
            components_lock.unlock();
            chr2 = 0;
        }
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(5));
    }
    // Reset terminal settings
    system("stty cooked");
}

void Cli::loop(){
    long long period = (long long)(1000.0 / fps);
    while (!stop.load()){
        execute();
        this_thread::sleep_for(chrono::milliseconds(period));
    }
}

void Cli::execute(){
    char chr, chr2;
    string str, key, type, imp;
    int num;
    vector<double> vec;
    cout << "show environment: (e);\nshow robot commands: (r);\nstop: (s)\nchange component: (c)\nelo mec tester: (m)\n";
    cin >> chr;
    shared_ptr<BaseComponent> ptr = nullptr;
    unique_lock<mutex> lock(component_mtx, defer_lock);
    switch (chr){
        case 'm':
            eloMecTester(lock);
            break;
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
            cout << "ui component_mtx locked"<< endl;
            lock.lock();
            if (!componentIsValid("logic")) break;
            components["logic"]->setParameter("oi.key1", string("olá"));
            components["logic"]->setParameter("oi.key2", (int)2);
            components["logic"]->setParameter("oi.array", vector<double>({1.1, 1.2}));
            lock.unlock();
            cout << "ui component_mtx locked"<< endl;
            break;    
        case 'p':
            cout << "ui component_mtx locked"<< endl;
            lock.lock();
            if (!componentIsValid("logic")) break;
            str = any_cast<string>(components["logic"]->getParameter("oi.key1"));
            num = any_cast<int>(components["logic"]->getParameter("oi.key2"));
            vec = any_cast<vector<double>>(components["logic"]->getParameter("oi.array"));
            lock.unlock();
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
    try{
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
    } catch(exception&){}
    TransmittedCommands transmitted;
    {
        lock_guard<mutex> lock(component_mtx);
        if (!componentIsValid("communicator")) return;
        try{
            transmitted = components["communicator"]->getMessage<TransmittedCommands>();
        } catch(exception&){
            return;
        }
    }
    cout << "transmitted: " << transmitted.transmitted << endl;
}

void Cli::showRobotCommands(){
    RobotCommands robotCommands;
    {
        lock_guard<mutex> lock(component_mtx);
        if (!componentIsValid("blueLogic")) return;
        try{
            robotCommands = components["blueLogic"]->getMessage<RobotCommands>();
        } catch(exception&){
            return;
        }
    }
    //cout << "timestamp: " << robotCommands.timestamp << endl;
    cout << "vel_tang: " << robotCommands.robotCommands[0].veltangent << endl;
    cout << "vel_norm: " << robotCommands.robotCommands[0].velnormal<< endl;
    cout << "vel_ang: " << robotCommands.robotCommands[0].velangular << endl;
}
