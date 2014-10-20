#ifndef MESSAGE
#define MESSAGE

#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include "ThreadReadWriteLock.h"
#include "RWLock.h"
using namespace std;
struct message {
  int type;
  char data[1000];
};


#endif

