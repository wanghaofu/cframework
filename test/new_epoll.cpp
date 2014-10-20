#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 3000
#define INFTIM 1000

typedef struct task_t
{
    int fd;
    char buffer[100];
    int n;
}task_t;

int CreateWorker(int nWorker)
{
    if (0 < nWorker)
    {
        bool bIsChild;
        pid_t nPid;

        while (!bIsChild)
        {
            if (0 < nWorker)
            {
                nPid = ::fork();
                if (nPid > 0)
                {
                    bIsChild = false;
                    --nWorker;
                }
                else if (0 == nPid)
                {
                    bIsChild = true;
                    printf("create worker %d success!\n", ::getpid());
                }
                else
                {
                    printf("fork error: %s\n", ::strerror(errno));
                    return -1;
                }
            }
            else 
            {
                int nStatus;
                if (-1 == ::wait(&nStatus))
                {
                    ++nWorker;
                }
            }
        }
    }

    return 0;
}

void setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }   
}

int main()
{
    int i, maxi, listenfd, connfd, sockfd,epfd,nfds;
    ssize_t n;
    char line[MAXLINE];
    socklen_t clilen;
    struct epoll_event ev,events[20];

    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    char *local_addr="127.0.0.1";
    inet_aton(local_addr,&(serveraddr.sin_addr));//htons(SERV_PORT);
    serveraddr.sin_port=htons(SERV_PORT);
    // 地址重用
    int nOptVal = 1;
    socklen_t nOptLen = sizeof(int);
    if (-1 == ::setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &nOptVal, nOptLen))
    {
        return -1;
    }    
    setnonblocking(listenfd);
    bind(listenfd,(sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(listenfd, LISTENQ);    

    CreateWorker(5);

    //把socket设置为非阻塞方式

    //生成用于处理accept的epoll专用的文件描述符
    epfd=epoll_create(256);    
    //设置与要处理的事件相关的文件描述符
    ev.data.fd=listenfd;
    //设置要处理的事件类型
    ev.events=EPOLLIN|EPOLLET;
    //ev.events=EPOLLIN;
    //注册epoll事件
    epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);

    //CreateWorker(5);

    maxi = 0;

    task_t task; 
    task_t *ptask;
    while(true) 
    {
        //等待epoll事件的发生
        nfds=epoll_wait(epfd,events,20,500);
        //处理所发生的所有事件     
        for(i=0;i<nfds;++i)
        {
            if(events[i].data.fd==listenfd)
            {                
                connfd = accept(listenfd,NULL, NULL);
                if(connfd<0){                    
                    printf("connfd<0, listenfd = %d\n", listenfd);
                    printf("error = %s\n", strerror(errno));
                    exit(1);
                }
                setnonblocking(connfd);

                //设置用于读操作的文件描述符
                memset(&task, 0, sizeof(task));
                task.fd = connfd;
                ev.data.ptr = &task;
                //设置用于注册的读操作事件
                ev.events=EPOLLIN|EPOLLET;
                //ev.events=EPOLLIN;
                //注册ev
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }
            else if(events[i].events&EPOLLIN)
            {
                cout << "EPOLLIN" << endl;
                ptask = (task_t*)events[i].data.ptr;  //转化为task_t 的指针类型
                sockfd = ptask->fd;  //same as *ptask.fd ??

                if ( (ptask->n = read(sockfd, ptask->buffer, 100)) < 0) {
                    if (errno == ECONNRESET) {
                        close(sockfd);
                        events[i].data.ptr = NULL;
                    } else
                        std::cout<<"readline error"<<std::endl;
                } else if (ptask->n == 0) {
                    close(sockfd);
                    events[i].data.ptr = NULL;
                }
                ptask->buffer[ptask->n] = '\0';
                cout << "read " << ptask->buffer << endl;

                //    ev.data.fd = sockfd;
                //设置用于写操作的文件描述符                                
                ev.data.ptr = ptask;
                //设置用于注测的写操作事件
                ev.events=EPOLLOUT|EPOLLET;

                //修改sockfd上要处理的事件为EPOLLOUT
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
            }
            else if(events[i].events&EPOLLOUT)
            {   
                cout << "EPOLLOUT" << endl;
                ptask = (task_t*)events[i].data.ptr;
                sockfd = ptask->fd;

                write(sockfd, ptask->buffer, ptask->n);

                //设置用于读操作的文件描述符              
                ev.data.ptr = ptask;
                //   ev.data.fd = sockfd;   
                ev.events=EPOLLIN|EPOLLET;
                //修改sockfd上要处理的事件为EPOLIN
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
                // epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,&ev);
                cout << "write: " << ptask->buffer <<endl;
                // memset(ptask, 0, sizeof(*ptask));
                string action;
                action = ptask->buffer; //this is  good
                // ptask->buffer = action.c_str(); //this is good
                // ptask->buffer = action //this is not run have a error ok 
                if(strcmp(ptask->buffer,"quit") == 0 )
                { 
                    cout << "One client quit! " << endl;
                    epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,&ev);
                    memset(ptask, 0 , sizeof(*ptask));
                    close(sockfd);
                }
                if( action == "init" )
                {
                    cout << "Client init one user" << endl;
                    write(sockfd,"You init one user", 100);
                }
            }
        }
    }
    return 0;
}
