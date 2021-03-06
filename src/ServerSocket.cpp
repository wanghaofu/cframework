// Implementation of the ServerSocket class
#include <errno.h>
#include "ServerSocket.h"
#include "SocketException.h"
#include "FileOperator.h"
#include "ThreadReadWriteLock.h"
#include <string>
#include <list>
#include <semaphore.h>
#include "comm.h"
//what means ?
list<Socket *> ServerSocket::clientSockets;
//means  ServerSocket::readWriteLock  ReadWriteLock是ThreadReadWriteLock的class 这里是初始化ServerSocket的静态变量readWriteLock 也就是这里已经初始化了！
ThreadReadWriteLock ServerSocket::readWriteLock;

//初始化静态变量！
bool ServerSocket::serviceFlag = true;

ServerSocket::ServerSocket ( const int port )
{

    if ( ! Socket::create() )
    {
        throw SocketException ( "Could not create server socket." );
    }
    if ( !Socket::bind ( port ))
    {
        throw SocketException("could not bind to port.");
    }
    if (!Socket::listen())
    {
        throw SocketException( "Could not listen to socket.");
    }
}

ServerSocket::~ServerSocket()
{
    list<Socket *>::iterator iter;
    for (iter = clientSockets.begin(); iter != clientSockets.end(); iter++)
        delete (*iter);
}

const ServerSocket &ServerSocket::operator << (  const std::string &s ) const
{
    if ( ! Socket::send( s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }
    return *this;
}

const ServerSocket &ServerSocket::operator >> ( std::string  &s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket.");
    }
    return *this;
}
/**
old
**/
bool ServerSocket::accept(Socket &socket )
{
    if ( ! Socket::accept ( socket ) )
    {
        return false;
        // throw SocketException ( "Could not accept socket .");
    }
    else
    {
        return true;
    }
}

/**
支持epoll的版本
**/
bool ServerSocket::accept()
{
    // ? !
    Socket *clientSocket = new Socket;
    bool status;
    status = accept(*clientSocket);
    if (status == false)
    {
        return false;
    }
    cout << "accept status" << status << endl;
    AddClient(clientSocket);

    //create new thread for a new client
    pthread_t newThread; //这里的线程创建没有特定的名字 ，怎么退出这个线程
    //! 多线程启动  //在这里对单个连接生成一个线程！
    int result = pthread_create(&newThread, NULL, processMessage, static_cast<void *>(clientSocket));
    if (result != 0)
        return false;

    //detach the newThread
    //so when newThread exits it can release it's resource
    result = pthread_detach(newThread);
    if (result != 0)
        perror("Failed to detach thread");

    return true;
}

void ServerSocket::run()
{
    while (serviceFlag)
    {
        if (clientSockets.size() >= static_cast<unsigned int>(MAXCONNECTIONS))
            serviceFlag = false;
        else
            serviceFlag = accept();  //一直在循环运行 所以每一个新用户创建一个新的线程
        sleep(1);
    }
}
void ServerSocket::sendMsgToAllUsers(const std::string &message)
{
    if (readWriteLock.SetWriteLock())
    {
        list<Socket *>::iterator iter;
        for (iter = clientSockets.begin(); iter != clientSockets.end(); iter++)
        {

            std::cout << "Now " << " users.." << message << std::endl;
            (*iter)->send(message);
        }
    }
    else
        serviceFlag = false;

    readWriteLock.UnLock();

}
//信息首发函数 why not server arg是个Socket的指针对象！
//这个参数传递什么？ 由accept调用 是私有方法
void *ServerSocket::processMessage(void *arg)
{
    std::string message;
    //转化回来
    Socket *clientSocket = static_cast<Socket *>(arg);

    //在父类Socket中定义的方法 都到整整的对象


    while (serviceFlag)
    {
        //当客户端实效
        if (clientSocket->recv(message) == -1)
        {
            DeleteClient(clientSocket);
            pthread_exit(NULL); //必须在这里退出否则就退不出去
            break;
        }
        if (message.empty())
        {
            continue;
        }
        std::cout << "Client :" << message << std::endl;
        if (message == "exit")
        {

            clientSocket->send("has exit");
            DeleteClient(clientSocket);
            pthread_exit(NULL); //必须在这里退出否则就退不出去

            //这里必须
            break;
        }
        else
        {
            //clientSocket->send(message);
            //向所有用户发送消息 //该方法暂时没有写 需要便利已连接的list端口进行逐个发送
            sendMsgToAllUsers(message);
        }
        sleep(1);
    }

    return NULL;
}


void ServerSocket::AddClient(Socket *socket)
{
    if (readWriteLock.SetWriteLock())
    {
        //clientSockets是一个列表 保存已连接socket pubsh_back是list的一个方法
        clientSockets.push_back(socket);

        std::cout << "Now " << clientSockets.size() << " users..";
        std::cout << "New User: " << socket->getAddress() << " " << socket->getPort() << "\n";

        readWriteLock.UnLock();
    }
    else
        serviceFlag = false;
}

void ServerSocket::DeleteClient(Socket *socket)
{
    if (readWriteLock.SetWriteLock())
    {
        list<Socket *>::iterator iter; //this hase question

        for (iter = clientSockets.begin(); iter != clientSockets.end(); iter++)
            if ((*iter)->getAddress() == socket->getAddress()
                    && (*iter)->getPort() == socket->getPort())
            {

                //delete socket* in list
                //delete socket* in list
                delete (*iter); //删除指针的内容 释放空间
                clientSockets.erase(iter);  //clientSockets 为list类型的ServerSocket成员变量 删除元素这里！
                //why delete and erase!? because iter is a point ? may be!
                // //this has question !
                std::cout << "Now " << clientSockets.size() << " users..\n";
                break;
            }
        readWriteLock.UnLock();
    }
    else
        serviceFlag = false;
}

void ServerSocket::RecvFile(Socket *clientSocket)
{
    std::string message;
    FileOperator fileOperator;
    //using IP address to name received file
    fileOperator.Open(clientSocket->getAddress().c_str(), WRITE_CREATE_MODE);

    int recvBytes;
    int writeBytes;

    while ((recvBytes = Socket::receive(*clientSocket, message)) > 0)
    {
        std::cout << "message length: " << message.size() << "\n";
        writeBytes = fileOperator.WriteToFile(message);
        std::cout << "writeBytes: " << writeBytes << "\n";

        if (writeBytes < recvBytes)
        {
            perror("write to file failed");
            Socket::send(*clientSocket, "Error when server receiving file.");
            return;
        }

        //if all bytes has been wrote
        if (recvBytes == 0 || recvBytes != MAXRECV)
            break;

    }

    if (recvBytes >= 0 )
        Socket::send(*clientSocket, "server has received your file.");
}

