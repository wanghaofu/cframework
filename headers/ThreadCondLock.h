#include "comm.h"


class RWLock
{

public:
    ThreadCondLock();
    ~ThreadCondLock();
    static void mutexInit();
    static void pthreadJoin();
    static void pthreadMutexLock();
    static void pthreadMutexUnlock();
private:
    pthread_mutex_t mutex;
    pthread_cond_t condLock;




}