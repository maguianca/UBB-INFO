#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<limits.h>
#define MAX_NUM 9000000
int numere[MAX_NUM],NR,MAX_THR,dif_min=INT_MAX;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
void*citire(void*argv)
{
	int fd=open("file",O_RDONLY);
	if(fd==-1){perror("error");exit(1);}
	for(int i=0;i<NR;i++)
		read(fd,&numere[i],2);
	close(fd);
	return NULL;
}
void* do_work(void*argv)
{
	int s_p=0,s_i=0,dif=0;
	int id=*(int*)argv;
	free(argv);
	int st= id*NR/MAX_THR;
	int dr=st+NR/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		pthread_mutex_lock(&mtx);
		if(numere[i]%2==0)s_p+=numere[i];
		else s_i+=numere[i];
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_lock(&mtx);
	dif=abs(s_p-s_i);
	if(dif_min>dif)dif_min=dif;
	pthread_mutex_unlock(&mtx);
	printf("thread %d  pare=%d impare=%d dif=%d\n",id,s_p,s_i,dif);
	return NULL;
}
int main(int argc,char**argv)
{
	printf("introduceti nr n:\n");
	scanf("%d",&NR);
	MAX_THR=NR/2000;
	pthread_t tid[MAX_THR],cititor;
	pthread_create(&cititor,NULL,citire,NULL);
	pthread_join(cititor,NULL);
	for(int i=0;i<MAX_THR;i++)
	{
		int*id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	for(int i=0;i<MAX_THR;i++)
        {
                pthread_join(tid[i],NULL);
        }
	printf("dif minima= %d\n",dif_min);
	return 0;
}
