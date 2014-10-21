// Definition of the Socket class

#ifndef Socket_class
#define Socket_class


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "comm.h"

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 400000;
const int MAXRECV = 500000;

class Socket
{
public:
    Socket();
    virtual ~Socket();

    // Server initialization
    bool create();
    bool bind ( const int port );
    bool listen() const;
    bool accept ( Socket &) const;

    // Client initialization
    bool connect ( const std::string host, const int port );

    // Data Transimission
    bool send ( const std::string ) const;
    int recv ( std::string &) const;

    //!!! change
    bool send(Socket &socket, const std::string &message) const;
    int receive(Socket &socket, std::string &message)const;


    void set_non_blocking ( const bool );

    bool is_valid() const
    {
        return m_sock != -1;
    }
    int getSocketfd();
    void erase(int sockfd);

    int getPort();
    std::string getAddress();

   

private:

    int m_sock;


    string address;
    int port;

    sockaddr_in m_addr;
};


#endif


