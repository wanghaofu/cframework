// Implementation of the Socket class.


#include "Socket.h"
#include "string.h"
#include <string.h>
#include <string>
#include <errno.h>
#include <fcntl.h>
#include <iostream>


Socket::Socket() :
	m_sock ( -1 )
{

	memset ( &m_addr,0,sizeof ( m_addr ) );

}

Socket::~Socket()
{
	if ( is_valid() )
	 ::close ( m_sock );
}

bool Socket::create()
{
	m_sock = socket ( AF_INET,SOCK_STREAM,0 );

	if ( ! is_valid() )
	 return false;


	// TIME_WAIT - argh
	int on = 1;
	if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
	 return false;


	return true;

}

bool Socket::bind ( const int _port )
{
	port = _port;
	if ( ! is_valid() )
	{
		return false;
	}

	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = INADDR_ANY;
	m_addr.sin_port = htons ( _port );

	int bind_return = ::bind ( m_sock,
				( struct sockaddr * ) &m_addr,sizeof ( m_addr ) );


	if ( bind_return == -1 )
	{
		return false;
	}

	return true;
}


bool Socket::listen() const
{
	if ( ! is_valid() )
	{
		return false;
	}
	int listen_return = ::listen ( m_sock, MAXCONNECTIONS );


	if ( listen_return == -1 )
	{
		return false;
	}

	return true;
}


bool Socket::accept ( Socket& new_socket ) const
{
	int addr_length = sizeof ( m_addr );
	//m_sock 服务端listen连接符
	//new_socket.m_sock 一链接符！ 这里只有一个？！
	new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length ); //创建一个新的以连接资源

	if ( new_socket.m_sock <= 0 )
	 return false;
	else
	 return true;
}


bool Socket::send ( const std::string s ) const
{
    //linux 
	int status = ::send ( m_sock, s.c_str(), s.size(), MSG_NOSIGNAL );
    //in mac os
//    int status = ::send(m_sock,s.c_str(),s.size(),MSG_HAVEMORE);
	if ( status == -1 )
	{
		return false;
	}
	else
	{
		return true;
	}
}
// Data Transmission
bool Socket::send(Socket& socket,const std::string& message) const
{
	//?? ??!! 发送消息的方法貌似有问题！ 直接发送！ 这个send方法是哪里来的 是本地方法吗
    int result=::send(socket.m_sock,message.c_str(),message.length(),MSG_NOSIGNAL);
    if(result==-1)
        return false;
    return true;
}

//多个连接的时候使用  在服务端没有问题 这个是否应该server 部分 这里传递了连接符
int Socket::receive(Socket& socket,std::string& message) const
{
    char buffer[MAXRECV+1];
    message.clear();
    memset(buffer,0,MAXRECV+1);

    int numberRead=::recv(socket.m_sock,buffer,MAXRECV,0);
    if(numberRead==-1)
    {
        std::cout<<"error in Socket::Receive\n";
        return 0;
    }
    else if(numberRead==0)
        return 0;
    else
    {
        message=buffer;
        return numberRead;
    }

}
//单连接时候使用 在客户端没有问题
int Socket::recv ( std::string& s ) const
{

     char buf[MAXRECV + 1]; 
     s="";
     memset( buf, 0, MAXRECV +1 );

     int status = ::recv ( m_sock, buf, MAXRECV , 0 );

	if ( status == -1 )
	{
		std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
		return 0;
	}
	else if ( status == 0 )
	{
		return 0;
	}
	else
	{
                s = buf;
		return status;
	}
}



bool Socket::connect ( const std::string host, const int port )
{
	if ( ! is_valid() ) return false;

	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons ( port );

	int status = inet_pton ( AF_INET, host.c_str(), &m_addr.sin_addr );

	if ( errno == EAFNOSUPPORT ) return false;

	status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

	if ( status == 0 )
	 return true;
	else
	 return false;
}

void Socket::set_non_blocking ( const bool b )
{

	int opts;

	opts = fcntl ( m_sock,F_GETFL );

	if ( opts < 0 )
	{
		return;
	}

	if ( b )
	 opts = ( opts | O_NONBLOCK );
	else
	 opts = ( opts & ~O_NONBLOCK );

	fcntl ( m_sock, F_SETFL,opts );

}

int Socket::getSocketfd(){
	return m_sock;
}
/**
该方法需要修正 临时写的参数类型未必正确
**/
void Socket::erase(int socketfd)
{
	
}


int Socket::getPort()
{
	return port = ntohs(m_addr.sin_port);
}
std::string Socket::getAddress()
{
      char *ip;
      string Sip;
	  ip = inet_ntoa(m_addr.sin_addr);
	  Sip = ip;
	  return Sip;
}
