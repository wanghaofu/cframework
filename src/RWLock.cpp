#include "comm.h"

// RWLock::RWLock():rd_cnt(0),wr_cnt(0)
// {
//     pthread_mutex_init(&cnt_mutex, NULL);
//     //   pthread_cond_init(&rw_cond, NULL);
// }


RWLock::RWLock()
{
    pthread_mutex_init(&mutex, NULL);
    //   pthread_cond_init(&rw_cond, NULL);
}


void RWLock::lock()
{
    pthread_mutex_lock(&mutex);
}
void RWLock::unLock()
{
    pthread_mutex_unlock(&mutex);
}


RWLock::~RWLock()
{
    pthread_mutex_destroy(&mutex);
    // pthread_cond_destroy(&rw_cond);
}

void RWLock::condLock()
{
    pthread_mutex_lock(&condMutex);
}
void RWLock::condUnLock()
{
    pthread_mutex_unlock(&condMutex);
}

void RWLock::condWait()
{
     pthread_cond_wait(&icondLock, &condMutex);
}

void RWLock::condSignal()
{
     pthread_cond_signal(&icondLock);
}



