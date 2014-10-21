#include "comm.h";

SysLog::SysLog()
{

    
}

SysLog::~SysLog()
{

}

static void SysLog::log(string message)
{
   openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2 )
    {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);

    }
}