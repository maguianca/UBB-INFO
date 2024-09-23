#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX_THR 100
#define MAX_NUM 80000
int NR,numere[MAX_NUM];
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;
int medie,frecventa[10],min=INT_MAX,sum;
void* doWork(void*arg)
{
        int frecv[10]={0};
        int id=*(int*)arg;
        free(arg);
        for(int i=0;i<NR;i++)
        {
		if(numere[i]%10==id)
		{
			pthread_mutex_lock(&mtx);
			frecventa[id]++;
			pthread_mutex_unlock(&mtx);
		}
                //pthread_mutex_lock(&mtx);
                //frecventa[numere[i]%10]++;
                //frecv[numere[i]%10]++;
                //pthread_mutex_unlock(&mtx);

        }
	pthread_mutex_lock(&mtx);
	printf("[thread %d] frecventa:%d \n",id,frecventa[id]);
	sum+=frecventa[id];
	pthread_mutex_unlock(&mtx);
        pthread_barrier_wait(&bar);
        medie=sum/10;
	pthread_mutex_lock(&mtx);
	if(abs(medie-frecventa[id])<min)min=abs(medie-frecventa[id]);
	pthread_mutex_unlock(&mtx);
        printf("[thread %d] medie:%d  min:%d \n",id,medie,min);
        return NULL;
}
int main(int argc,char**argv)
{
        printf("Introduceti n");
        scanf("%d",&NR);
        srandom(time(NULL));
	int fd=open("random",O_RDONLY);
	if(fd==-1){perror("open");exit(1);}
        for(int i=0;i<NR;i++)
        {
                read(fd,&numere[i],sizeof(int));
		//printf("%d:  %d\n",i,numere[i]);
        }
        pthread_t tid[NR];
        pthread_barrier_init(&bar,NULL,10);
        for(int i=0;i<10;i++)
        {
                int*p=(int*)malloc(sizeof(int));
                *p=i;
                pthread_create(&tid[i],NULL,doWork,p);
        }
        for(int i=0;i<10;i++)
        {
                pthread_join(tid[i],NULL);
        }
        pthread_barrier_destroy(&bar);
	for(int i=0;i<=9;i++)
                if(abs(medie-frecventa[i])==min)
                        printf("%d are frecventa %d\n",i,frecventa[i]);
        return 0;
}
