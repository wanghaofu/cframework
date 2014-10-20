#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
void *myThread(void *arg);
int main()
{
	int ret;
	pthread_t mythread;

	ret = pthread_create(*mythread,NULL,myThread,NULL);

	if ( ret!=0)
	{
		printf("Cant create pthread(%s)\n",strerror(errno));
	}

	exit(-1)
}

return 0;
}
void *myThread(void *arg)
{
	printf("thread run\n");
	pthread_exit(arg);
}
