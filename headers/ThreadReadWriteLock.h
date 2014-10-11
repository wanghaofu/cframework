#ifndef THREADREADWRITELOCK_H
#define THREADREADWRITELOCK_H

#include <pthread.h>

class ThreadReadWriteLock
{
    public:
        ThreadReadWriteLock();
        ~ThreadReadWriteLock();

        bool SetReadLock();
        bool SetWriteLock();
        void UnLock();

    private:
        pthread_rwlock_t readWriteLock;
        pthread_mutex_t mutex;

};

#endif