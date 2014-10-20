#include <stdio.h>
#include <time.h>
void init_daemon(void);//守护进程初始化函数
main()
{
	FILE *fp;
	time_t t;
	init_daemon();//初始化为Daemon
	while(1)//每隔一分钟向test.log报告运行状态
	{
		sleep(60);//睡眠一分钟
		if((fp=fopen("test.log","a"))>=0)
		{
			t=time(0);
			fprintf(fp,"I'm here at %s\n",asctime(localtime(&t)) );
			fclose(fp);
		}
	}
}

