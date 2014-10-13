#ifndef MESSAGE
#define MESSAGE

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
struct message {
  int type;
  char data[1000];
};


#endif

