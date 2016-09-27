/* 
 * hello.c - Pthreads "hello, world" program 
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *thread(void *vargp);

int main() 
{
    pthread_t tid;

    printf("Hello World fron the main thread!\n");
    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);
    exit(0);
}

void *thread(void *vargp) /* thread routine */
{
    printf("Hello World from a thread created by the main thread!\n"); 
    return NULL;
}

