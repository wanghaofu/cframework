#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>

void printPid()
{
	printf("\nsid is %d, pgid is %d, ppid is %d, pid is %d\n",getsid(getpid()),getpgrp(),getppid(),getpid());
}


//only get the deamon process 
void init_daemon(void)
{
	int pid;
	int i;
	//退出主进程
	printPid();
	if(pid=fork())
	{
		printPid();
		exit(0);//是父进程，结束父进程
	}else if(pid<0)
		exit(1);//fork失败，退出
	printPid();
	//是第一子进程，后台继续执行
	//This  is import
	setsid();//第一子进程成为新的会话组长和进程组长
	//并与控制终端分离
	printPid();
if(pid=fork())
	{	
  		printPid();
		//exit(0);//是第一子进程，结束第一子进程
	}	else if(pid<0)
		exit(1);//fork失败，退出

	printPid();
	//是第二子进程，继续
	//第二子进程不再是会话组长
	for(i=0;i<NOFILE;++i)//关闭打开的文件描述符
		close(i);
	chdir("/tmp");//改变工作目录到/tmp

	// this is must write!
	umask(0);//重设文件创建掩模
	return;
}
