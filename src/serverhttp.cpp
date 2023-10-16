#include "serverhttp.h"
#include "request.h"
#include <iostream>

using namespace std;

ServerHTTP::ServerHTTP(std::uint16_t port):
    mPort(port)
{
    createSocket();
}

ServerHTTP::~ServerHTTP()
{
    isRunning = false;
}

void ServerHTTP::createSocket()
{
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    bindSocet();
}
void ServerHTTP::bindSocet()
{
    if (setsockopt(serverFd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &mOpt,
                   sizeof(mOpt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    mAddress.sin_family = AF_INET;
    mAddress.sin_addr.s_addr = INADDR_ANY;
    mAddress.sin_port = htons(mPort);

    if (bind(serverFd, (struct sockaddr*)&mAddress,
             sizeof(mAddress))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void ServerHTTP::startListening()
{
    if (listen(serverFd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    listenerThread = std::thread(&ServerHTTP::acceptConnection,this);
}

void ServerHTTP::acceptConnection()
{
    cout << "Server is running on localhost::8000 ..." << endl;
    isRunning = true;
    while(isRunning)
    {
        if ((clientSocket
             = accept(serverFd, (struct sockaddr*)&mAddress,
                      (socklen_t*)&mAddrlen))
            < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        int valread = read(clientSocket, mBuffer, BUFFER_SIZE);
        if(valread > 0)
        {
            string responceString = requestDisp.handleIt(std::make_shared<Request>(Request(std::string(mBuffer))));
            send(clientSocket, responceString.data(), strlen(responceString.data())+1, 0);
        }

        close(clientSocket);
        memset(mBuffer,0,BUFFER_SIZE);
    }
    shutdown(serverFd, SHUT_RDWR);
}


void ServerHTTP::start()
{
    startListening();
    if(listenerThread.joinable())
    {
        listenerThread.join();
    }
};

void ServerHTTP::stop()
{
     isRunning = false;
};

