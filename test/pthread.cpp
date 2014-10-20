#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
//条件锁的实例！ 包含互斥锁 呼哧所好理解 ， 条件锁不好理解！！
using namespace std;
pthread_mutex_t count_lock;
pthread_cond_t count_nonzero;
unsigned count = 0; //全局变量

//pthread one
void *decrement_count(void *arg)
{
    pthread_mutex_lock (&count_lock);
    printf("1\n");
    cout << "hello this is decrement count" << endl;
    while (count == 0) //in here loop cant't out
    {
        printf("count is in a2:%d \n",count);
        printf("2\n");
        pthread_cond_wait( &count_nonzero, &count_lock);  //解锁锁 from here step out 从这里跳出去了 执行另外一个线程 就是这里等待了
        //pthread_cond_wait()

        printf("3\n");
    }
    count = count - 1;
    printf("count is int a %d \n",count);
    pthread_mutex_unlock (&count_lock);
}

//pthread second
void *increment_count(void *arg)
{
    pthread_mutex_lock(&count_lock);
    printf("4\n");
    cout << "hello this is increment count" << endl;
    if (count == 0) //when condition is ok then 
        {
             printf("count is in a1:%d \n",count);
        printf("5\n");
        pthread_cond_signal(&count_nonzero);  //释放！  ？ 从这里没有跳出！ 这里做了什么 signal做了什么
        printf("6\n");
    }
    count = count + 1;
    printf("count is in b :%d \n",count);
    pthread_mutex_unlock(&count_lock);
}

int main(void)
{
    pthread_t tid1, tid2;
    pthread_mutex_init(&count_lock, NULL); //condition mutex
    pthread_cond_init(&count_nonzero, NULL);
    pthread_create(&tid1, NULL, decrement_count, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, increment_count, NULL);
    sleep(1);
    
    pthread_exit(0); //exit !

    return 0;
}
