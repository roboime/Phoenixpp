#include "udp_receiver.h"

UdpReceiver::UdpReceiver(atomic<bool>& stop, queue<pair<char*,int>> &bufferQueue, mutex &bufferQueue_mtx,
                         string multicastAddress, string port, int bufferSizeMax, int queueSizeMax) :
    stop(stop), bufferQueue(bufferQueue), bufferQueue_mtx(bufferQueue_mtx), socket(Poco::Net::MulticastSocket()),
    received(false), multicastAddress(multicastAddress), port(port), stopReceiver(false),
    bufferSizeMax(bufferSizeMax), queueSizeMax(queueSizeMax) {
        buffer = new char[bufferSizeMax];
}

void UdpReceiver::start(){
    reconnect();
    /*
    Poco::Net::ReadableNotification readableNotification(&reactor);
    reactor.addEventHandler(socket, Poco::Observer<UdpReceiver, Poco::Net::ReadableNotification>(*this, &UdpReceiver::onReadable));
    reactor.addEventHandler(socket, Poco::Observer<UdpReceiver, Poco::Net::TimeoutNotification>(*this, &UdpReceiver::onTimeout));
    reactor.setTimeout(Poco::Timespan(chrono::milliseconds(500)));
    */
    receiveThread = thread([this]{ receivePacket(); });
    //reactorThread = thread([this]{ reactor.run(); });
}

void UdpReceiver::reconnect(){
    try{
        Poco::Net::SocketAddress group(multicastAddress, port);
        socket.bind(Poco::Net::SocketAddress("0.0.0.0", port));
        socket.joinGroup(group.host());
        socket.setReceiveTimeout(Poco::Timespan(1, 0));
    }
    catch (Poco::Exception& e) {
        //cerr << "Error trying to reconnect to multicast group: " << e.displayText() << endl;
    }
}

void UdpReceiver::receivePacket() {
    Poco::Net::SocketAddress sender;
    Poco::Net::SocketImpl* socketImpl;
    while (!stop.load() && !stopReceiver.load()) {
        socketImpl = socket.impl();
        if (!socketImpl || !socketImpl->initialized()){
            cerr << (bool)socketImpl << " " << socketImpl->initialized() << endl;
            reconnect();
        }
        if (socket.available() >= 0){
            try{
                int size = socket.receiveFrom(buffer, bufferSizeMax, sender);
                received.store(true);
                //cerr << "received\n";
                {
                    unique_lock<mutex> lock(bufferQueue_mtx);
                    if((int)bufferQueue.size() <= queueSizeMax){
                        char* buffer_ptr = new char[size];
                        memcpy(buffer_ptr, buffer, (size_t)size);
                        bufferQueue.push(make_pair(buffer_ptr, size));
                        //cout << "size: " << size << endl;
                        //for(int i=0;i<size;i++) cout << i << " " << (int)buffer_ptr[i] << endl;
                    }
                }
            } catch (const Poco::TimeoutException& e) {
                received.store(false);
                reconnect();
                //cerr << "Receive timeout: " << e.displayText() << "\n";
            } catch (const Poco::Exception& e) {
                received.store(false);
                //cerr << "Error while receiving: " << e.displayText() << "\n";
            }
        }
    }
    //reactor.stop();
    socket.close();
    //this_thread::sleep_for(chrono::seconds(500));
}

bool UdpReceiver::getReceived(){
    return received.load();
}

UdpReceiver::~UdpReceiver(){
    cout << "destruindo udp receiver" << endl;
    stopReceiver.store(true);
    if(receiveThread.joinable()) receiveThread.join();
    //if(reactorThread.joinable()) reactorThread.join();
    delete [] buffer;
    cout << "done udp receiver" << endl;
}
