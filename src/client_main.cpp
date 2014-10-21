#include "ClientSocket.h"
#include "SocketException.h"
//#include "http_client.h"
#include <iostream>
#include <string>
#include <pthread.h>
#include "comm.h"
//#include <cstring>
using namespace std;

const bool DEBUG = true;

pthread_mutex_t *mute;


// string message;
//int main ( int argc, int argv[] )
int main( int argc, char **)
{
 

    try
    {
        //设置输入设备为非阻塞模式
        // fcntl( 0, F_SETFL, O_NONBLOCK);  //注意一下这个方法 第一个参数！
        ClientSocket client_socket ( "localhost", 30000 );
        //   HttpClient vote( "127.0.0.1",80);
      //  string reply;

        //message="This client String";

        client_socket.run();
        sleep(60);

    }
    catch ( SocketException &e )
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


