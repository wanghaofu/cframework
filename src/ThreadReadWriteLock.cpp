#include "ThreadReadWriteLock.h"
#include <pthread.h>
#include <iostream>
using namespace std;

ThreadReadWriteLock::ThreadReadWriteLock()
{
 if (pthread_rwlock_init(&readWriteLock, NULL))  
        cout<<"cannot create reader/writer lock"<<endl;  
}
//to not ok
ThreadReadWriteLock::~ThreadReadWriteLock()
{
	pthread_rwlock_destroy(&readWriteLock);  

}

//todo not ok  写加锁非阻塞
bool ThreadReadWriteLock::SetWriteLock()
{
	//return  pthread_rwlock_wrlock(readWriteLock);
	 int rc = pthread_rwlock_trywrlock(&readWriteLock);  
    if (rc == 0)  
        return true;  
    else if (rc == EBUSY)  
        return false;  
    else  
        cout<<"cannot lock reader/writer lock"<<endl;  
    return false;  
}

//todo not ok
void ThreadReadWriteLock::UnLock()
{
	  if (pthread_rwlock_unlock(&readWriteLock))  
        cout<<"cannot unlock reader/writer lock"<<endl;  
}
//todo not ok 读加锁非阻塞
bool ThreadReadWriteLock::SetReadLock()
{
	//pthread_rwlock_unlock() //return true;
	 int rc = pthread_rwlock_tryrdlock(&readWriteLock);  
    if (rc == 0)  
        return true;  
    else if (rc == EBUSY)  
        return false;  
    else  
        cout<<"cannot lock reader/writer lock"<<endl;  
  
    return false;  
}