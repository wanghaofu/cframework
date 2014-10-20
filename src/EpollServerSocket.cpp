#include "EpollServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <errno.h>
#include <stdio.h>

#define DEBUG
/**
创建链接 利用
**/
EpollServerSocket::EpollServerSocket(const int port)
{
      if ( ! Socket::create() )
        {
          throw SocketException ( "Could not create server socket." );
        }

      if ( ! Socket::bind ( port ) )
        {
          throw SocketException ( "Could not bind to port." );
        }

      if ( ! Socket::listen() )
        {
          throw SocketException ( "Could not listen to socket." );
        }

      //set listener socket non-blocking!!
      Socket::set_non_blocking(true);

}

EpollServerSocket::~EpollServerSocket()
{
    std::map<int,Socket*>::iterator it;
    for(it=clientSockets.begin();it!=clientSockets.end();it++)
        delete it->second;
}
/**
重点
入口方法？！

**/
void EpollServerSocket::run()
{
    //add listener socketfd to epoll 监听套接字描述符
    if(epoll.Add(Socket::getSocketfd(),EPOLLIN)==false) //添加一链接描述符号
        return;

    int i;
    int eventNumber;
    Socket* clientSocket; //定义已连接变量

    while(true)
    {
        eventNumber=epoll.Wait();

        #ifdef DEBUG
            std::cout<<"eventNumbers: "<<eventNumber<<" ";
        #endif

        for(i=0;i<eventNumber;i++ )
        {
             if ((epoll.GetEvents(i) & EPOLLERR) ||
                 (epoll.GetEvents(i) & EPOLLHUP) ||
                 (!(epoll.GetEvents(i) & EPOLLIN)))
            {
                      /* An error has occured on this fd, or the socket is not
                         ready for reading (why were we notified then?) */
                      perror ("epoll error\n");
                      deleteClient(epoll.GetEventOccurfd(i));
                      continue;
            }

            //if event is triggered by listener socket what is this
            else if(epoll.GetEventOccurfd(i)==Socket::getSocketfd())
            {
                clientSocket=new Socket();
                if(addNewClient(*clientSocket)==false)
                    return;
                //获取链接！ ？ why 一个单独的socket来 负责一个客户！ 
                clientSockets[clientSocket->getSocketfd()]=clientSocket;

            }
            //else event is triggered by client sockets
            else
            {
                clientSocket=clientSockets[epoll.GetEventOccurfd(i)];
                processMessage(*clientSocket);
            }
        }
    }
}

/**
?? 用成员方法发送信息
！clientSockets! 是哪里来的！ 传递过来的某一个用户连接！ 这个是针对多个用户的所以保持了多个连接
**/
void EpollServerSocket::processMessage(Socket& clientSocket)
{
    std::string message;
    receiveMessage(clientSocket,message);

    if(message=="exit")
    {
        sendMessage(clientSocket,"user_exit");

        deleteClient(clientSocket.getSocketfd());
    }
    else
    {
        //可以发送给单个用户！ 这个以来与信息包的进一步扩展。client list 进行重构
        sendToAllUsers(message);
    }  
}

/**
将连接加入epoll  events 列表
**/
bool EpollServerSocket::addNewClient(Socket& clientSocket)
{
    if(Socket::accept(clientSocket)==false)
        return false;

    //set socket non-blocking!!
    clientSocket.set_non_blocking(true);

    if(epoll.Add(clientSocket.getSocketfd(),EPOLLIN | EPOLLET)==false)
        return false;

    #ifdef DEBUG
        std::cout<<"New user...\n";
    #endif

    return true;
}

/**
从epoll events 删除
**/
void EpollServerSocket::deleteClient(int sockfd)
{
    //epoll doesn't need to handle events from sockfd anymore

    epoll.Delete(sockfd);

    delete clientSockets[sockfd];
    
    clientSockets.erase(sockfd); //定义erase没有声明
}
//向所有连接发送信息
void EpollServerSocket::sendToAllUsers(const std::string& message) const
{
    std::map<int,Socket*>::const_iterator it;
    for(it=clientSockets.begin();it!=clientSockets.end();it++)
        sendMessage(*(it->second),message);
}
//发送信息ReceiveMessage
void EpollServerSocket::sendMessage(Socket& clientSocket,const std::string& message) const
{
    while(true)
    {
        if(Socket::send(clientSocket,message)==false)
        {
            //this means the socket can be wrote
            if(errno == EINTR)
                return;

            //this means the cache queue is full,
            //sleep 1 second and send again
            if(errno==EAGAIN)
            {
                sleep(1);
                continue;
            }
        }

        return;
    }
}
/**
接受信息！？ 
clientSocket ?! 接受某个特定链接的信息
message  具体的信息体

**/
void EpollServerSocket::receiveMessage(Socket& clientSocket,std::string& message)
{
    bool done=true;

    while(done)
    {
        int receiveNumber=Socket::receive(clientSocket,message); //调用父类的发送方法给接受该连接的信息到message
        if(receiveNumber==-1)
        {
            //if errno == EAGAIN, that means we have read all data.
            if (errno != EAGAIN)
            {
                perror ("ReceiveMessage error");
                deleteClient(clientSocket.getSocketfd());
            }
            return;
        }
        else if(receiveNumber==0)
        {
            // End of file. The remote has closed the connection.
            deleteClient(clientSocket.getSocketfd());
        }

        //if receiveNumber is equal to MAXRECEIVE,
        //maybe there is data still in cache,so it has to read again
        if(receiveNumber==MAXRECV)
            done=true;
        else
            done=false;
    }
}