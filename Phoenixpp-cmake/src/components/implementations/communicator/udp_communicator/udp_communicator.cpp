#include "udp_communicator.h"

UdpCommunicator::UdpCommunicator(atomic<bool>& stop, double fps) : BaseComponent("udpcommunicator", stop, fps) {
    parameters.load();
    string multicastAddress = any_cast<string>(parameters.get("multicastAddress"));
    string port = any_cast<string>(parameters.get("port"));
    bufferSizeMax = any_cast<int>(parameters.get("bufferSizeMax"));
    queueSizeMax = any_cast<int>(parameters.get("queueSizeMax"));

    udpSender = make_shared<UdpSender>(stop, bufferQueue, bufferQueue_mtx, multicastAddress, port, bufferSizeMax, queueSizeMax);
}

void UdpCommunicator::start(){
    udpSender->start();
}

RobotCommands UdpCommunicator::update(RobotCommands){
    return RobotCommands();
}

void UdpCommunicator::execute(){
    {
        lock_guard<mutex> lock(component_mtx);
        if (!isComponentValid("blueLogic")) return;
        RobotCommands commands = components["blueLogic"]->getMessage();
    }

    grSim_Commands protobufMessage;
    protobufMessage.set_timestamp(commands.timestamp);
    protobufMessage.set_isteamyellow(commands.isteamyellow);

    for (const auto& robotCommand : commands.robotCommands) {
        grSim_Robot_Command* robotProto = protobufMessage.add_robot_commands();
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
    {
        lock_guard<mutex> lock(bufferQueue_mtx);
        if(bufferQueue.size() == queueSizeMax) return;
        const int size = protobufMessage.ByteSizeLong();
        char * ptr = new char[size]; // espaco sera deletado pelo destrutor ou pelo udoSender ao da pop na fila
        if(protobufMessage.SerializeToArray(ptr, size)){
            bufferQueue.push(make_pair(ptr,size));
        }
    }

    
}

UdpCommunicator::~UdpCommunicator(){
    cout << "destruindo udp communicator" << endl;
    udpSender = nullptr;

    while(!bufferQueue.empty()){
        char* frontStr = bufferQueue.front().first;
        bufferQueue.pop();
    }
    cout << "done udp communicator" << endl;
    //BaseComponent::~BaseComponent();
}
