// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"
#include "FileOperator.h"
#include "comm.h"


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


const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
	if ( ! Socket::send ( s ) )
	{
		throw SocketException ( "Could not write to socket." );
	}

	return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string&  s ) const
{
	if ( ! Socket::recv ( s ) )
	{
		throw SocketException ( "Could not read from socket." );
	}

	return *this;
}

void ClientSocket::SendFile(const std::string& fileName)
{
    FileOperator fileOperator;
    fileOperator.Open(fileName.c_str(),"rb");
    std::string buffer;

    int readBytes;
    send("File");

    while((readBytes = fileOperator.ReadFromFile(buffer))>0)
    {
        if(send(buffer)<0)
        {
            perror("failed to send file");
            break;
        }
    }

}
void *getLine(void* arg)
{
	 //转化回来 
    std::string* message=static_cast<std::string*>(arg);
	while(1){
	  std::cout  <<"Send :" ;
	 //被阻塞到这里了  被上边代码设定为输入非阻塞模式了
      getline(std::cin,message);
      usleep(500);
  }
  return ((void *)0);


}