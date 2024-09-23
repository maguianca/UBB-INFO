#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX_THR 100
#define MAX_NUM 100

int sum=0;
int local=0;
int d;
int fd;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
void*f(void*a)
{
	int k=*(int*)a;
	free(a);
	printf("[thread %d]starting.. \n",k);
	pthread_mutex_lock(&mtx);
	int i=0;
	local=0;
	while(i<MAX_NUM)
	{
		read(fd,&d,2);
		i++;
		local+=d;
	}
	//pthread_mutex_lock(&mtx);
	sum+=local;
	pthread_mutex_unlock(&mtx);
	printf("[thread %d]finished.. \n",k);
	return NULL;
}
int main(int argc,char*argv[])
{
	fd=open("random.bin",O_RDONLY);
	if(fd<0)
	{
		perror("open()");
		exit(1);
	}
	pthread_t th[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int *k=(int*)malloc(sizeof(int));
		*k=i;
		pthread_create(&th[i],NULL,f,k);
	}
	for(int i=0;i<MAX_THR;i++)
		pthread_join(th[i],NULL);
	printf("Sum: %d\n",sum);
	close(fd);
	return 0;

}
