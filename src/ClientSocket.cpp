// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"
#include "FileOperator.h"
#include "comm.h"
#include "ThreadReadWriteLock.h"



ClientSocket::ClientSocket ( std::string host, int port )
{

    if ( ! Socket::create() )
    {
        throw SocketException ( "Could not create client socket." );
    }

    if ( ! Socket::connect ( host, port ) )
    {
        throw SocketException ( "Could not bind to port." );
    }

}


const ClientSocket &ClientSocket::operator << ( const std::string &s ) const
{
    if ( ! Socket::send ( s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }

    return *this;

}


const ClientSocket &ClientSocket::operator >> ( std::string  &s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}

void ClientSocket::SendFile(const std::string &fileName)
{
    FileOperator fileOperator;
    fileOperator.Open(fileName.c_str(), "rb");
    string buffer;

    int readBytes;
    send("File");

    while ((readBytes = fileOperator.ReadFromFile(buffer)) > 0)
    {
        if (send(buffer) < 0)
        {
            perror("failed to send file");
            break;
        }
    }

}
void ClientSocket::run()
{
    //转化回来

    pthread_create(&pth1, NULL, getLine, static_cast<void *>(this));
    sleep(1);
    pthread_create(&pth2, NULL, iRecv, static_cast<void *>(this));
    pthread_create(&pth3, NULL, sendMessage, static_cast<void *>(this));
    pthread_create(&pth4, NULL, view, static_cast<void *>(this));
    pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);
    pthread_join(pth3, NULL);
    pthread_join(pth4, NULL);


}

void *ClientSocket::sendMessage(void *arg)
{
    //转化回来
    ClientSocket *client = static_cast<ClientSocket *>(arg);

    // fcntl(0, F_SETFL, O_NONBLOCK); //设置键盘非阻塞状态  设置之后就不好拿到数据了
    while (1)
    {

        //  client->lock.lock();

        if (!client->message.empty())
        {
            //发送信息
            *client << client->message;
        }

        if ( client->message == "quit")
        {
            cout << "I will quit Bye!" << endl;
            // pthread_exit();
            return ((void *)0);
        }
        // client->lock.unLock();
        sleep(1);
    }

    return ((void *)0);

}

void *ClientSocket::view(void *arg)
{
    return ((void *)0);
    ClientSocket *client = static_cast<ClientSocket *>(arg);

    // client->lock.condLock();

    while (1)
    {
        if (client->message.empty() && client->reply.empty())
        {
             sleep(1);
            //  client->lock.condWait();
        }
        // if ( true == !client->message.empty() )
        // {
        //     cout << "send: " << client->message << endl;
        //     client->message= "";
        // }
        // if ( true == !client->reply.empty() )
        // {
        //     cout << "recv: " << client->reply << endl;
        //     client->reply="";
        // }
        sleep(1);
    }
    //  client->lock.condUnLock();
    return ((void *)0);
}


void *ClientSocket::getLine(void *arg)
{
    ClientSocket *client = static_cast<ClientSocket *>(arg);

    while (1)
    {
        //  cout << "send: " ;
        getline(std::cin, client->message);

        if ( !client->message.empty() )
        {
 cout << "send: " << client->message << endl;
            //client->lock.condSignal();
        }
        //client->message="hello";

        sleep(1);
    }
    return ((void *)0);
}
//读取！
void *ClientSocket::iRecv(void *arg)
{
    ClientSocket *client = static_cast<ClientSocket *>(arg);
    while (1)
    {
        // client->lock.lock();
        // cout << "I am iRecv" << endl;
        //    client->lock.lock();
        // client->lock.condLock();
        *client >> client->reply;
        // while (client->reply.empty())
        // {
        //     cout << "I am recv wait..." << endl;
        //  client->lock.condWait();
        // }
        if ( !client->reply.empty())
        {
             cout << "recv: " << client->reply << endl;
        }
        //  client->lock.unLock();
        sleep(1);
    }
    return ((void *)0);
    //   pthread_mutex_unlock(&mute);

}

