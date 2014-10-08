#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
int main ( int argc, char ** )


{
//  message data={1,"body"};
  std::cout << "running....\n";


  try
  {
    // Create the socket
    ServerSocket server ( 3000 );
    //HttpClient vote (50000);
    while ( true )
    {
      ServerSocket new_sock;
      //HttpClient new_client;
      server.accept ( new_sock );
      //vote.accept (new_client);

      try
      {
        while ( true )
        {
          std::string data;
          data="this is server test";
          new_sock >> data;
//          cout << "client message is :" << &data << endl;
          new_sock << data ;
        }
      }
      catch ( SocketException& ) {}
    }
  }
  catch ( SocketException& e )
  {
    std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }

  return 0;
}


