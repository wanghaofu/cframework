// Definition of the ClientSocket class

#ifndef ClientSocket_class
#define ClientSocket_class

#include "Socket.h"
#include "comm.h"

class ClientSocket : public Socket
{
  public:

    ClientSocket ( std::string host, int port );
    virtual ~ClientSocket(){};

    const ClientSocket& operator << ( const std::string& ) const;
    const ClientSocket& operator >> ( std::string&  ) const;
    void SendFile(const std::string& fileName);
    static void readConsle(str::string*);
   private:
    static void *getLine(void* arg);
};


#endif


