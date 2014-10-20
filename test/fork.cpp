#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
//fork lib
#include <unistd.h>
#include <sys/types.h>
// signal 
#include <signal.h>

using namespace std;
int main()
{
    /*
       printf("Running ps with system\n");
       system("ps ax");
       printf("Done.\n");
       exit(0);
       */

    pid_t new_pid;
    int exit_code;
    int n;
  const  char *message;


    new_pid = fork();

    if (new_pid == -1)
    {
        cout << "error";
    }
    if (new_pid == 0 )
    {
        // cout << "I am is child" << endl;
        message = "This is the child";
        n = 5;
        exit_code = 37;
    }
    if ( new_pid != 0)
    {
        message = " This is parent";
        n = 3;
        exit_code = 0;

    }
    for (; n > 0; n--)
    {
        puts(message);
        sleep(1);
    }
    if (new_pid > 0 )
    {
        //cout << "I am is parent process segment"<< endl;
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);

        printf("Child has finished: PID = %d\n", child_pid);
        if (WIFEXITED(stat_val))
        {
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        }
    }
    exit(exit_code);


}
