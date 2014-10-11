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
int main ( int argc, char ** )
{

	cout << "Running server ..." << endl;
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
				new_sock.server >> data;  //用已连接描述符进行胡同
				new_sock.server << data;
			}
		}
		catch ( SocketException& ) {}

	}
catch ( SocketException& e )
{
	std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
}

return 0;
/** cout<<"Running server..."<<endl;
  try
  {
  ServerSocket server(8080);

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


