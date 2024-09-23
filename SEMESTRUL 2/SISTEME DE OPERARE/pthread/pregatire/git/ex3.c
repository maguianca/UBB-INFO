// Write a program that creates 7 threads and a global array of 10 integer 
// numbers, named SUM, storing the sum of numbers based on the remainder from 
// division with 10. Each thread generates random numbers between 0 and 100,
//  and adds each number n to SUM[x], where x is n mod 10. The threads stop when
//  there have been exactly 5 numbers generated with the last digit 5. 
// The main program prints the sums from the array SUM for each digit 
// (print SUM[x]=nr  for each x=0..9, where nr is the sum of all numbers 
// with remainder x from division by 10). Use efficient synchronisation 
// mechanisms and print also the numbers that make up the sums.
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<pthread.h>
#define MAX_THR 7
int sum[11],count=0;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;
void*do_work(void*argv)
{
	 int id=*(int*)argv;
        free(argv);
	while(1){
	int x=rand()%101;
	pthread_mutex_lock(&mtx);
	if(count==5)break;
	sum[x%10]+=x;
	if(x%10==5)count++;
	printf("thread %d  am generat %d\n",id,x);
	pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx);
	pthread_barrier_wait(&barr);
	return NULL;
}
int main(int argc,char**argv)
{
	srand(time(NULL));
	pthread_t tid[MAX_THR];
	pthread_barrier_init(&barr,NULL,MAX_THR+1);
	for(int i=0;i<MAX_THR;i++)
	{
		int*id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	pthread_barrier_wait(&barr);
	for(int i=0;i<MAX_THR;i++)
		pthread_join(tid[i],NULL);
	for(int i=0;i<10;i++)
		printf("sum[%d]=%d\n",i,sum[i]);
	pthread_barrier_destroy(&barr);
	return 0;
}
