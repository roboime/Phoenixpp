#include "udp_communicator.h"

UdpCommunicator::UdpCommunicator(atomic<bool>& stop, double fps) : BaseComponent("udpcommunicator", stop, fps) {
    parameters.load();
    string multicastAddress = any_cast<string>(parameters.get("multicastAddress"));
    string port = any_cast<string>(parameters.get("port"));
    int bufferSizeMax = any_cast<int>(parameters.get("bufferSizeMax"));
    int queueSizeMax = any_cast<int>(parameters.get("queueSizeMax"));

    udpSender = make_shared<UdpSender>(stop, bufferQueue, bufferQueue_mtx, multicastAddress, port, bufferSizeMax, queueSizeMax);
}

void UdpCommunicator::start(){
    udpSender->start();
}

RobotCommands UdpCommunicator::update(RobotCommands message){
    lock_guard<mutex> lock(bufferQueue_mtx);
    //bufferQueue()
    pair<char*, int> buffer;
    char * buffer_ptr;
    int size;
    Ball ball;
    Field field;
    RobotCommands robotCommands = message;

    return robotCommands;
}

UdpCommunicator::~UdpCommunicator(){
    cout << "destruindo udp communicator" << endl;
    udpSender = nullptr;

    while(!bufferQueue.empty()){
        char* frontStr = bufferQueue.front().first;
        delete [] frontStr;
        bufferQueue.pop();
    }
    cout << "done udp communicator" << endl;
    //BaseComponent::~BaseComponent();
}
