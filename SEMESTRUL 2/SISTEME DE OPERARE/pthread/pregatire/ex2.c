#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#define MAX_THR 100
#define MAX_NUM 80000
int NR,numere[MAX_NUM];
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;
int medie,frecventa[10];
void* doWork(void*arg)
{
	int frecv[10]={0};
	int id=*(int*)arg;
	free(arg);
	int st=id*NR/MAX_THR;
	int dr=st+NR/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		pthread_mutex_lock(&mtx);
		frecventa[numere[i]%10]++;
		frecv[numere[i]%10]++;
		pthread_mutex_unlock(&mtx);

	}
	pthread_barrier_wait(&bar);
	for(int i=0;i<=9;i++)
		medie+=frecventa[i];
	medie=medie/10;
	printf("[thread %d] medie:%d \n",id,medie);
	for(int i=0;i<=9;i++)
		printf("[thread %d] frecv[%d]=%d: \n",id,i,frecv[i]);
	return NULL;
}
int main(int argc,char**argv)
{
	printf("Introduceti n");
	scanf("%d",&NR);
	srandom(time(NULL));
	for(int i=0;i<NR;i++)
	{
		numere[i]=rand()%2000;
	}
	pthread_t tid[NR];
	pthread_barrier_init(&bar,NULL,MAX_THR);
	for(int i=0;i<MAX_THR;i++)
	{
		int*p=(int*)malloc(sizeof(int));
		*p=i;
		pthread_create(&tid[i],NULL,doWork,p);
	}
	for(int i=0;i<MAX_THR;i++)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_barrier_destroy(&bar);
	int min=30000,max;
	for(int i=0;i<=9;i++)
		if(abs(frecventa[i]-medie)<min)
			min=abs(frecventa[i]-medie);
	max=medie+min;
	min=medie-min;
	for(int i=0;i<=9;i++)
		if(frecventa[i]==min||frecventa[i]==max)
			printf("%d are frecventa %d\n",i,frecventa[i]);
	return 0;
}
