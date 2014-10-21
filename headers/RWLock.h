#ifndef RWLOCK
#define RWLOCK
#include <string>
#include "comm.h"


class RWLock
{

public:
    RWLock();
    ~RWLock();
    //    RWLock &operator= (const RWLock &);


    void  lock();
    void unLock();

    void condLock();
    void condWait();
    void condUnLock();
    void condSignal();

private:
    pthread_mutex_t mutex, condMutex;
    pthread_cond_t icondLock;
    //    int rd_cnt, wr_cnt;
};
#endif