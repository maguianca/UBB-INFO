#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<limits.h>
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER; 
pthread_barrier_t bar;
#define  MAX_NUM 900000
int numere[MAX_NUM],NR,MAX_THR,fd,dif_min=INT_MAX;
void* citire(void*argv)
{
	fd=open("file",O_RDONLY);
	if(fd==-1){perror("error()");exit(1);}
	for(int i=0;i<NR;i++)
		read(fd,&numere[i],sizeof(int));
	close(fd);
	return NULL;
}
void* do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	int m=rand()%257;
	int medie=0,suma=0,dif;
	int st=id*NR/MAX_THR;
	int dr=st+NR/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		pthread_mutex_lock(&mtx);
		suma+=numere[i];
		pthread_mutex_unlock(&mtx);
	}
	medie=suma/3000;
	dif=abs(medie-m);
	printf("[thread %d] m: %d, medie: %d,  dif:%d\n",id,m,medie,dif);
	pthread_mutex_lock(&mtx);
	if(dif_min>dif)dif_min=dif;
	pthread_mutex_unlock(&mtx);
	return NULL;

}
int main(int argc,char**argv)
{
	srand(time(NULL));
	printf("introduceti n:\n");
	scanf("%d",&NR);
	MAX_THR=NR/3000;
	pthread_barrier_init(&bar,NULL,MAX_THR);
	pthread_t tid[MAX_THR],cititor;
	pthread_create(&cititor,NULL,citire,NULL);
	pthread_join(cititor,NULL);
	for(int i=0;i<MAX_THR;i++)
	{
		int* id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	 for(int i=0;i<MAX_THR;i++)
        {
                pthread_join(tid[i],NULL);
        }
	pthread_barrier_destroy(&bar);
	printf("diferenta minima\n dif_min:%d\n",dif_min);
	return 0;
}
