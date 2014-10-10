#ifndef EPOLLSERVERSOCKET_H
#define EPOLLSERVERSOCKET_H

#include "Socket.h"
#include "Epoll.h"
#include <map>

class EpollServerSocket:public Socket
{
    public:
        EpollServerSocket(const int port);
        virtual ~EpollServerSocket();

        void run();

    private:
        //when using the EPOLLET flag,
        //need to continuously read/write a file descriptor until EAGAIN,
        //so we write these two functions for read/write
        void sendMessage(Socket& clientSocket,const std::string& message) const;
        void receiveMessage(Socket& clientSocket,std::string& message);

        void processMessage(Socket& clientSocket);
        void sendToAllUsers(const std::string& message) const;
        //add event to epoll
        bool addNewClient(Socket& clientSocket);
        //delete client from map clientSockets
        void deleteClient(int sockfd);

        //map 用于存储链接队列 very good
        std::map<int,Socket*> clientSockets;
        
        Epoll epoll;
};

#endif