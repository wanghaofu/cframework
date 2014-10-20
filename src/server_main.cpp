#include "ServerSocket.h"
#include "SocketException.h"
#include "ThreadReadWriteLock.h"

#include <string>
#include <iostream>
#include <cstdlib>

#include <errno.h>
#include <string>
#include <list>
#include <semaphore.h>

using namespace std;



void signServer()
{

    try
    {
        // Create the socket
        ServerSocket server ( 30000 );

        ServerSocket new_sock; //这种是多链接模式 会把连接符保存起来
        server.accept ( new_sock );
        try
        {
            while ( true )
            {
                string data;
                new_sock >> data;  //用已连接描述符进行调用
                cout << "Recv data :" << data << endl;
                new_sock << data;
            }
        }
        catch ( SocketException &) {}

    }
    catch ( SocketException &e )
    {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
}
void mutileServer()
{
    try
    {
        ServerSocket server(30000);
        server.run();
    }
    catch (SocketException &e)
    {
        std::cout << "Exception was caught:" << e.description() << "\nExting.\n";
    }
}

void epollMutileServer()
{

}

int main ( int argc, char **)
{

    cout << "Running server ..." << endl;
    // signServer();
    mutileServer();
    return 0;

    /** cout<<"Running server..."<<endl;
    try
    {
    ServerSocket server(8080);

    while(true)
    {
    Socket newSocket;
    server.Accept(newSocket);

    try
    {
    string message;
    server.receive(newSocket,message);
    cout<<"Receive message: "<<message<<endl;
    message="Here is server";
    server.send(newSocket,message);
    }
    catch(SocketException&){}
    }
    }
    catch(SocketException& ex)
    {
    cout << "Exception was caught:" << ex.Description() << "\nExiting.\n";
    }
    return 0;
     **/
}


