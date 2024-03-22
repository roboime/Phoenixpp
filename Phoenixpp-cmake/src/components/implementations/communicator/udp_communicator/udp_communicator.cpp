#include "udp_communicator.h"

UdpCommunicator::UdpCommunicator(atomic<bool>& stop, double fps) : TBaseComponent("udpcommunicator", stop, fps) {
    parameters.load();
    string multicastAddress = any_cast<string>(parameters.get("localAddress"));
    string port = any_cast<string>(parameters.get("port"));
    bufferSizeMax = any_cast<int>(parameters.get("bufferSizeMax"));
    queueSizeMax = any_cast<int>(parameters.get("queueSizeMax"));

    udpSender = make_shared<UdpSender>(stop, bufferQueue, bufferQueue_mtx, multicastAddress, port, bufferSizeMax, queueSizeMax);
}

void UdpCommunicator::start(){
    udpSender->start();
}

void UdpCommunicator::pushRobotCommand(string logic){
    RobotCommands commands;
    {
        lock_guard<mutex> lock(component_mtx);
        if (!isComponentValid("navigation")){
            //cerr << "blueLogic not valid\n";
            return;
        }
        try{
            commands = components["navigation"]->getMessage<RobotCommands>();
        } catch(exception&){
            return;
        }

    }
    grSim_Packet packetMessage;
    grSim_Commands commandsMessage;
    commandsMessage.set_timestamp(commands.timestamp);
    commandsMessage.set_isteamyellow(commands.isteamyellow);

    for (const auto& robotCommand : commands.robotCommands) {
        grSim_Robot_Command* robotProto = commandsMessage.add_robot_commands();
        robotProto->set_id(robotCommand.id);
        robotProto->set_kickspeedx(robotCommand.kickspeedx);
        robotProto->set_kickspeedz(robotCommand.kickspeedz);
        robotProto->set_veltangent(robotCommand.veltangent);
        robotProto->set_velnormal(robotCommand.velnormal);
        robotProto->set_velangular(robotCommand.velangular);
        robotProto->set_spinner(robotCommand.spinner);
        robotProto->set_wheelsspeed(robotCommand.wheelsspeed);
        if (robotCommand.wheelsspeed) {
            robotProto->set_wheel1(robotCommand.wheel1);
            robotProto->set_wheel2(robotCommand.wheel2);
            robotProto->set_wheel3(robotCommand.wheel3);
            robotProto->set_wheel4(robotCommand.wheel4);
        }
    }
    *(packetMessage.mutable_commands()) = commandsMessage;
    {
        lock_guard<mutex> lock(bufferQueue_mtx);
        if(bufferQueue.size() == queueSizeMax){
            //cerr << "queue full\n";
            //delete commandsMessage;
            return;
        }
        const int size = packetMessage.ByteSizeLong();
        char * ptr = new char[size]; // espaco sera deletado pelo destrutor ou pelo udoSender ao da pop na fila

        if(packetMessage.SerializeToArray(ptr, size)){
            bufferQueue.push(make_pair(ptr,size));
        } else{
            cerr << "Error serializing array\n";
        }
        //cerr << "communicator queue size: " << bufferQueue.size() << "/" << queueSizeMax << endl;
    }
}

TransmittedCommands UdpCommunicator::update(TransmittedCommands old_transmitted){
    TransmittedCommands transmitted = { udpSender->getReceived() };
    pushRobotCommand("blueLogic");
    //pushRobotCommand("yellowLogic");
    /*
    grSim_Replacement replacement;
    grSim_BallReplacement ball;
    ball.set_x(0);
    ball.set_y(0);
    ball.set_vx(0);
    ball.set_vy(0);
    *(replacement.mutable_ball()) = ball;
    *(packetMessage.mutable_replacement()) = replacement;
    */

    //delete commandsMessage;
    return transmitted;
}

UdpCommunicator::~UdpCommunicator(){
    cout << "destruindo udp communicator" << endl;
    udpSender = nullptr;

    while(!bufferQueue.empty()){
        char* frontStr = bufferQueue.front().first;
        bufferQueue.pop();
        delete frontStr;
    }
    cout << "done udp communicator" << endl;
    //BaseComponent::~BaseComponent();
}
