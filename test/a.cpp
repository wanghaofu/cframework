#include "apue.h"
#include <pthread.h>
#include <stdio.h>

pthread_t ntid;

void printids(const char *s)
{

    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u (OX%X\n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}


void *thr_fn(void *arg)
{
    printids("new thread:" );
}

int main(void)
{
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);

    //if(err !=0 )
    printids("main thread:");
    sleep(1);
    exit(0);
}