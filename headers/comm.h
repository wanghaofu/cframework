#ifndef MESSAGE
#define MESSAGE

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
struct message {
  int type;
  char data[1000];
};


#endif

