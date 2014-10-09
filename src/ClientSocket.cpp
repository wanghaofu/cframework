// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"


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
    Send("File");

    while((readBytes = fileOperator.ReadFromFile(buffer))>0)
    {
        if(Send(buffer)<0)
        {
            perror("failed to send file");
            break;
        }
    }

}
