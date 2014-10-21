#ifndef MESSAGE
#define MESSAGE

#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>




#include <sys/types.h>       /* some systems still require this */
#include <sys/stat.h>
#include <sys/termios.h>     /* for winsize */
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif
#include <stdio.h>     /* for convenience */
#include <stdlib.h>    /* for convenience */
#include <stddef.h>    /* for offsetof */
#include <string.h>    /* for convenience */
#include <unistd.h>    /* for convenience */
#include <signal.h>    /* for SIG_ERR */
//#include "apue.h"
#include <syslog.h>
#include <sys/resource.h>

#include "daemonize.h"
#include "ThreadReadWriteLock.h"
#include "RWLock.h"

#include "Protocol.h"

using namespace std;
struct message
{
    int type;
    char data[1000];
};


#endif

