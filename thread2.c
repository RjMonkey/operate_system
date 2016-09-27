//Author：郭仁杰
//time：2016 9 20 0点
//description：这是我第一次学习线程之后用c写的，计算π的，我好开心。
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define NUMBER_OF_THREADS 10
//公示中的N
const int  N =  10000000000;
//最后计算累加的
double SUM = 0;

//分段计算pi的
void *caculate_pi(void *tid)
{
	/* This function prints the threads identifier and then exits. */
	//printf("Hello World. Greetings from thread %d\n", (int)tid);
    int temp_id = (int)tid;
    int start_i = temp_id * (N / NUMBER_OF_THREADS);
    int end_i = (temp_id + 1) * (N / NUMBER_OF_THREADS);
    if(end_i == N){
        end_i = N + 1;
    }
    //printf("%d\n", start_i);
    double temp_sum = 0;
    for (start_i; start_i < end_i; start_i++){
        double num  = ((double)start_i + 0.5) / N; 
        double temp = 4 / (1 + num * num);
        temp_sum += temp;
    }
    //printf("%d\n", start_i);
    SUM = SUM + temp_sum;
	pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
	/* The main program creates 10 threads and then exits. */
    //计算时间的
	time_t start = clock();
	
	pthread_t threads[NUMBER_OF_THREADS];
	int status, i;
	
	for(i=0; i < NUMBER_OF_THREADS; i++) {
		status = pthread_create(&threads[i], NULL, caculate_pi,(void *)i);
		if (status != 0) {
			printf("Oops. pthread create returned error code %d\n", status);
			exit(-1);
		}
	}
	for(i=0; i < NUMBER_OF_THREADS; i++) {
		pthread_join(threads[i], NULL);
	} 
    double pi = SUM / N;
    
	time_t end = clock();
	printf("Hello, My pi is %f\n", pi);
	printf("the running time is : %f\n", (double)(end - start)/CLOCKS_PER_SEC);
	exit(0);
}
