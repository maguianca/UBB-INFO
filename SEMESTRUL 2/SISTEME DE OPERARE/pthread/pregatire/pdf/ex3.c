#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX_NUM 100000
#define MAX_THR 100
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<limits.h>
int T,NR,numere[MAX_NUM],medie,suma,frecventa[100],count,dif=INT_MAX;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;
void*do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	int st=id*NR/MAX_THR;
	int dr=st+NR/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		if(numere[i]%2==0)
		{
			printf("thread %d numar %d\n",i,numere[i]);
			pthread_mutex_lock(&mtx);
			suma+=numere[i];
			frecventa[numere[i]]++;
			count++;
			pthread_mutex_unlock(&mtx);
		}

	}
	pthread_barrier_wait(&barr);
	pthread_mutex_lock(&mtx);
	medie=suma/count;
	pthread_mutex_unlock(&mtx);
	for(int i=0;i<100;i++)
		if(dif>abs(frecventa[i]-medie))
		{
			pthread_mutex_lock(&mtx);
			dif=abs(frecventa[i]-medie);
			printf("dif %d pthread %d numere%d frecventa %d\n",dif,id,numere[i],frecventa[i]);
			pthread_mutex_unlock(&mtx);
		}
	return NULL;
}
int main(int argc,char**argv)
{
	int fd=open("random-file",O_RDONLY);
	if(fd<0){perror("error");exit(1);}
	printf("introduceti n\n");
	scanf("%d",&NR);
	for(int i=0;i<NR;i++){
		read(fd,&numere[i],sizeof(int));
		numere[i]=abs(numere[i]%100);
	}
	T=NR/MAX_THR;
	pthread_barrier_init(&barr,NULL,T);
	pthread_t tid[T];
	for(int i=0;i<T;i++)
	{
		int*id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	for(int i=0;i<T;i++)
		pthread_join(tid[i],NULL);
	printf("medie %d   dif %d\n",medie,dif);
	for(int i=0;i<100;i+=2)
		if(frecventa[i]>0)
		printf("%d are frecv %d\n",i,frecventa[i]);
	for(int i=0;i<100;i++)
		if(dif==abs(medie-frecventa[i]))
			printf("numarul %d are frecv %d\n",i,frecventa[i]);
	pthread_barrier_destroy(&barr);
	return 0;
}
