// Implementation of the ServerSocket class
#include <errno.h>
#include "ServerSocket.h"
#include "SocketException.h"
#include "FileOperator.h"
#include "comm.h"

ServerSocket::ServerSocket ( const int port )
{
    if ( ! Socket::create() )
    {
        throw SocketException ( "Could not create server socket." );
    }
    if( !Socket::bind ( port ))
    {
        throw SocketException("could not bind to port.");
    }
    if(!Socket::listen())
    {
        throw SocketException( "Could not listen to socket.");
    }
}

ServerSocket::~ServerSocket()
{
    list<Socket*>::iterator iter;
    for(iter=clientSockets.begin();iter!=clientSockets.end();iter++)
        delete (*iter);
}

const ServerSocket& ServerSocket::operator << (  const std::string& s ) const
{
    if ( ! Socket::send( s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }
    return *this;
}

const ServerSocket& ServerSocket::operator >> ( std::string&  s ) const
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
void ServerSocket::accept ( ServerSocket& sock )
{
    if ( ! Socket::accept ( sock ) )
    {
        throw SocketException ( "Could not accept socket .");
    }
}

/**
支持epoll的版本
**/
bool ServerSocket::accept()
{
    Socket* clientSocket=new Socket;
    accept(*clientSocket);
    AddClient(clientSocket);

    //create new thread for a new client
    pthread_t newThread;
    int result=pthread_create(&newThread,NULL,ProcessMessage,static_cast<void*>(clientSocket));
    if(result!=0)
        return false;

    //detach the newThread
    //so when newThread exits it can release it's resource
    result=pthread_detach(newThread);
    if(result!=0)
        perror("Failed to detach thread");

    return true;
}

void ServerSocket::Run()
{
    while(serviceFlag)
    {
        if(clientSockets.size()>=static_cast<unsigned int>(MAXCONNECTION))
            serviceFlag=false;
        else
            serviceFlag=Accept();
        sleep(1);
    }
}

void* ServerSocket::ProcessMessage(void* arg)
{
    std::string message;
    Socket* clientSocket=static_cast<Socket*>(arg);

    send(*clientSocket,"Welcome!");

    while(serviceFlag)
    {
        Receive(*clientSocket,message);
        if(message=="exit")
        {
            send(*clientSocket,"user_exit");
            DeleteClient(clientSocket);
            break;
        }
        else
            SendMsgToAllUsers(message);
        sleep(1);
    }
    pthread_exit(NULL);
    return NULL;
}


void ServerSocket::AddClient(Socket* socket)
{
    if(readWriteLock.SetWriteLock())
    {
        clientSockets.push_back(socket);

        std::cout<<"Now "<<clientSockets.size()<<" users..";
        std::cout<<"New User: "<<socket->GetAddress()<<" "<<socket->GetPort()<<"\n";

        readWriteLock.UnLock();
    }
    else
        serviceFlag=false;
}

void ServerSocket::DeleteClient(Socket* socket)
{
    if(readWriteLock.SetWriteLock())
    {
        list<Socket*>::iterator iter;
        for(iter=clientSockets.begin();iter!=clientSockets.end();iter++)
            if((*iter)->GetAddress()==socket->GetAddress()
               && (*iter)->GetPort()==socket->GetPort())
            {
                //delete socket* in list
                delete (*iter);
                clientSockets.erase(iter);
                std::cout<<"Now "<<clientSockets.size()<<" users..\n";
                break;
            }
        readWriteLock.UnLock();
    }
    else
        serviceFlag=false;
}

void ServerSocket::RecvFile(Socket* clientSocket)
{
    std::string message;
    FileOperator fileOperator;
    //using IP address to name received file
    fileOperator.Open(clientSocket->GetAddress().c_str(),WRITE_CREATE_MODE);

    int recvBytes;
    int writeBytes;

    while((recvBytes=Socket::Receive(*clientSocket,message))>0)
    {
        std::cout<<"message length: "<<message.size()<<"\n";
        writeBytes=fileOperator.WriteToFile(message);
        std::cout<<"writeBytes: "<<writeBytes<<"\n";

        if(writeBytes<recvBytes)
        {
            perror("write to file failed");
            Socket::send(*clientSocket,"Error when server receiving file.");
            return;
        }

        //if all bytes has been wrote
        if(recvBytes==0 || recvBytes!=MAXRECEIVE)
            break;

    }

    if(recvBytes >=0 )
        Socket::send(*clientSocket,"server has received your file.");
}