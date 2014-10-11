#include "ClientSocket.h"
#include "SocketException.h"
//#include "http_client.h"
#include <iostream>
#include <string>
//#include <cstring>
using namespace std;

const bool DEBUG=true;
//int main ( int argc, int argv[] )
int main( int argc, char **)
{

  try
  {
       ClientSocket client_socket ( "localhost", 30000 );

 //   HttpClient vote( "127.0.0.1",80);
    string reply;
    string res;
    string message;
     while(2)
   {
      cout  <<"Send :" ;

      getline(cin,message);

      if(message.empty())
        {
        continue;
        }
      
	      //发送信息
	      client_socket << message;
	      //    vote << "GET //html/58/n-58.html HTTP/1.0\r\nAccept:*.*\r\nAccept-Language:zh-cn\r\nAccept-Encoding: gzip, deflate\r\nUser-Agent: Mozilla/4.0(compatible;MSIE 6.0;Windows NT 5.1;SV!; .NET CLR 2.0.50727)\r\nHost:www.china-shufaijia.com\r\nConnection:Keep-Alive\r\n\r\n";
	      //接受的信息
	      client_socket >> reply;
	      std::cout << "Server: " << reply << endl;
    
       
        if( message == "quit")
        {
  	      cout << "I will quit Bye!" << endl;
  	      return 0;
        }
      
    }
  }
  catch ( SocketException& e )
  {
	  std::cout << "Exception was caught:" << e.description() << "\n";
  }

  return 0;

  /** cout<<"Running client...."<<endl;
    try
    {
    ClientSocket clientSocket("127.0.0.1",8080);
    clientSocket.Send("Hello,here is client");
    string message;
    clientSocket.Receive(message);
    cout<<"Response from server: "<<message<<endl;
    }
    catch(SocketException& ex)
    {
    cout << "Exception was caught:" << ex.Description() << "\n";
    }
    return 0;
   **/
}


