// Definition of the ClientSocket class

#ifndef ClientSocket_class
#define ClientSocket_class

#include "Socket.h"
#include "comm.h"
#include "ThreadReadWriteLock.h"
class ClientSocket : public Socket
{
public:

    ClientSocket ( std::string host, int port );
    virtual ~ClientSocket() {};

    const ClientSocket &operator << ( const std::string &) const;
    const ClientSocket &operator >> ( std::string &) const;
    void SendFile(const std::string &fileName);
    void run();


private:
    //pthread1
    static void *getLine(void *arg);
    //pthread 2
    static void *iRecv(void *arg);
    static void *sendMessage(void *arg);
    static void *view(void *arg);
    
    pthread_t pth1,pth2,pth3,pth4;

    static pthread_mutex_t mute,condMute;
    static pthread_cond_t cond;
    
    RWLock  lock;
    string message;
    string reply;
       //  static string message;
    //static ThreadReadWriteLock readWriteLock;
};


#endif


