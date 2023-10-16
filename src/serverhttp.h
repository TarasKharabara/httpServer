#ifndef SERVERHTTP_H
#define SERVERHTTP_H

#include <string>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <queue>
#include <memory>

#include "requestdispatcher.h"

constexpr uint16_t BUFFER_SIZE = 1024;

//!  A ServerHTTP class.
/*!
  socket, connection creator, will start the separate thread for listening
*/
class ServerHTTP
{
public:
    ServerHTTP() = delete;
    ServerHTTP(std::uint16_t port);
    ServerHTTP(ServerHTTP &) = delete;
    ~ServerHTTP();

    void start();
    void stop();
private:
    void createSocket();
    void bindSocet();
    void startListening();
    void acceptConnection();

    int serverFd, clientSocket;
    struct sockaddr_in mAddress;
    int mOpt = 1;
    int mAddrlen = sizeof(mAddress);
    char mBuffer[BUFFER_SIZE] = { 0 };
    int mPort = 0;

    bool isRunning = false;

    std::thread listenerThread;
    RequestDispatcher requestDisp;
};

#endif // SERVERHTTP_H
