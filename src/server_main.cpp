#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
int main ( int argc, char ** )
{
   cout<<"Running server..."<<endl;
   /* try
    {
        ServerSocket server(8080);

        while(true)
        {
            Socket newSocket;
            server.Accept(newSocket);

            try
            {
                string message;
                server.Receive(newSocket,message);
                cout<<"Receive message: "<<message<<endl;
                message="Here is server";
                server.Send(newSocket,message);
            }
            catch(SocketException&){}
        }
    }
    catch(SocketException& ex)
    {
         cout << "Exception was caught:" << ex.Description() << "\nExiting.\n";
    }*/
    return 0;
}


