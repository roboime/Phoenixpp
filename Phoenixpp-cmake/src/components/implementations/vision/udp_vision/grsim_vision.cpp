#include "grsim_vision.h"

UdpVision::UdpVision(atomic<bool>& stop, double fps) : BaseComponent("grsimvision", stop, fps) {
    parameters.load();
    string multicastAddress = any_cast<string>(parameters.get("multicastAddress"));
    string port = any_cast<string>(parameters.get("port"));
    int bufferSizeMax = any_cast<int>(parameters.get("bufferSizeMax"));
    int queueSizeMax = any_cast<int>(parameters.get("queueSizeMax"));

    udpReceiver = make_shared<UdpReceiver>(stop, bufferQueue, bufferQueue_mtx, multicastAddress, port, bufferSizeMax, queueSizeMax);
}

void UdpVision::start(){
    udpReceiver->start();
}

Environment UdpVision::update(Environment message){
    SSL_WrapperPacket packet;
    lock_guard<mutex> lock(bufferQueue_mtx);
    pair<char*, int> buffer;
    char * buffer_ptr;
    int size;
    Ball ball;
    Field field;
    Environment env = message;
    for(int i=0;i<4;i++){
        if(bufferQueue.empty()){
            //cout << "queue empty\n";
            continue;
        }
        buffer = bufferQueue.front();
        bufferQueue.pop();
        //cout << "queue size: " << (int)bufferQueue.size() << endl;
        buffer_ptr = buffer.first;
        size = buffer.second;
        //for(int i=0;i<size;i++) cout << i << " " << (int)buffer_ptr[i] << endl;
        packet.Clear();
        packet.ParseFromArray(buffer_ptr, size);
        delete[] buffer_ptr;
        if(packet.has_detection()){
            SSL_DetectionFrame detection = packet.detection();
            if (detection.balls_size()){
                //cout << "camera id: " << detection.camera_id() << endl;
                //cout << "balls update: ";
                ball.x = detection.balls().Get(0).x();
                ball.y = detection.balls().Get(0).y();
                //cout << ball.x << " " << ball.y << "; ball size: " << detection.balls_size() << endl;
            }
            else{
                //cout << "no ball update" << endl;
                ball = env.ball;
            }
        }
        else{
            //cout << "no ball update 2" << endl;
            ball = env.ball;
        }
        if(packet.has_geometry()){
            //cout << "field update:" << endl;
            SSL_GeometryData geometry = packet.geometry();
            SSL_GeometryFieldSize fieldSize = geometry.field();
            field = {(double)fieldSize.field_length(), (double)fieldSize.field_width()};
        }
        else{
            //cout << "no field update" << endl;
            field = env.field;
        }
        env = {0, ball, field};
    }
    env.received = udpReceiver->getReceived();
    return env;
}

UdpVision::~UdpVision(){
    cout << "destruindo grsim vision" << endl;
    udpReceiver = nullptr;

    while(!bufferQueue.empty()){
        char* frontStr = bufferQueue.front().first;
        delete [] frontStr;
        bufferQueue.pop();
    }
    cout << "done grsim vision" << endl;
    //BaseComponent::~BaseComponent();
}
