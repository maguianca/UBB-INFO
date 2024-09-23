#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>
#define MAX_NUM 80000
int NR,MAX_THR,numere[MAX_NUM],k,kontor;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
void*citire(void*argv)
{
	int fd=open("file",O_RDONLY);
	if(fd==-1){perror("");exit(1);};
	for(int i=0;i<NR;i++)
		read(fd,&numere[i],2);
	close(fd);
	return NULL;
}
void* do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	int contor=0;
	int st=id*NR/MAX_THR;
	int dr=st+NR/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		if(numere[i]%k==0)
		{
			pthread_mutex_lock(&mtx);
			contor++;
			pthread_mutex_unlock(&mtx);
		}

	}
	pthread_mutex_lock(&mtx);
	kontor+=contor;
	pthread_mutex_unlock(&mtx);
	printf("thread %d  contor %d\n",id,contor);
	return NULL;
}
int main(int argc,char**argv)
{
	printf("introduceti k\n");
	scanf("%d",&k);
	printf("introduceti n\n");
	scanf("%d",&NR);
	MAX_THR=NR/2000;
	pthread_t tid[MAX_THR],cititor;
	pthread_create(&cititor,NULL,citire,NULL);
	pthread_join(cititor,NULL);
	for(int i=0;i<MAX_THR;i++)
	{
		int *id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	for(int i=0;i<MAX_THR;i++)
		pthread_join(tid[i],NULL);
	printf("K contor %d\n",kontor);
	return 0;
}
