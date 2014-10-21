#ifndef DAEMONIZE
#define DAEMONIZE
// sigset_t    mask;

extern int already_running(void);
#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

extern int lockfile(int);

class daemonize
{
public:
    static void runDaemon();
};
#endif