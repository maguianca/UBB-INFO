#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#define MAX_THR 100
#define MAX_NUM 100
int count=0;
int buf[MAX_NUM];
int fd;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
void*f (void*a){

	int k=*(int*)a;
	free(a);
	memset(buf,0,sizeof(int)*MAX_NUM);
	printf("[thread %d] start reading..\n",k);
	pthread_mutex_lock(&mtx);
	int i=0;
	//int local=0;
	while(i<MAX_NUM)
	{
		read(fd,&buf[i],2);
		if(buf[i]%5==0)
		{	
			count++;
			printf("%d e div cu 5 count: %d \n",buf[i],count);
		}
		i++;
	}
	//pthread_mutex_lock(&mtx);
	//count=count+local;
	pthread_mutex_unlock(&mtx);
	return NULL;
}
int main(int argc,char*argv[])
{
	fd=open("rand",O_RDONLY);
	if(fd<0){perror("open");exit(1);}
	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int*p=(int*)malloc(sizeof(int));
		*p=i;
		pthread_create(&tid[i],NULL,f,p);
	}
	for(int i=0;i<MAX_THR;i++)
		pthread_join(tid[i],NULL);
	printf("Count: %d\n",count);
	return 0;
}
