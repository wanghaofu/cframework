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
    //设置输入设备为非阻塞模式
      // fcntl( 0, F_SETFL, O_NONBLOCK);  //注意一下这个方法 第一个参数！

       ClientSocket client_socket ( "localhost", 30000 );

 //   HttpClient vote( "127.0.0.1",80);
    string reply;
    string clientMessage;
    string* message;
    
    *message="This client String";

    client_socket.readConsle(message);
    

    clientMessage = *message;


     while(2)
   {
     

       

      if(!clientMessage.empty())
        {
        //发送信息
        client_socket << clientMessage;
        }
      
	      
	      //    vote << "GET //html/58/n-58.html HTTP/1.0\r\nAccept:*.*\r\nAccept-Language:zh-cn\r\nAccept-Encoding: gzip, deflate\r\nUser-Agent: Mozilla/4.0(compatible;MSIE 6.0;Windows NT 5.1;SV!; .NET CLR 2.0.50727)\r\nHost:www.china-shufaijia.com\r\nConnection:Keep-Alive\r\n\r\n";
	      //接受的信息
	      client_socket >> reply;
        if(!reply.empty())
        {
	      std::cout << "Server: " << reply << endl;
        }
       
        if( clientMessage == "quit")
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


