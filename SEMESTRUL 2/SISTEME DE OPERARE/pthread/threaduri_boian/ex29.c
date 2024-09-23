#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#define MAX_NUM 10000
int numere[MAX_NUM],MAX_THR,NR;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;
void* do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	int x=rand()%11+10;
	numere[id]=x;
	pthread_barrier_wait(&barr);
	//pthread_mutex_lock(&mtx);
	while(1){
		pthread_mutex_lock(&mtx);
		if(numere[id]<=0){pthread_mutex_unlock(&mtx);break;}
		int ok=0;
		for(int i=0;i<NR;i++)
			if(i!=id && numere[i]>0){ok=1;numere[i]--;}
		pthread_mutex_unlock(&mtx);
		if(ok==0)break;
	}
	//pthread_mutex_unlock(&mtx);
	return NULL;
}
int main(int argc,char**argv)
{
	printf("introduceti un n\n");
	scanf("%d",&NR);
	pthread_t tid[NR];
	pthread_barrier_init(&barr,NULL,NR);
	for(int i=0;i<NR;i++)
	{
		int*id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	for(int i=0;i<NR;i++)
		pthread_join(tid[i],NULL);
	pthread_barrier_destroy(&barr);
	for(int i=0;i<NR;i++)
		printf("numere[%d]=%d\n",i,numere[i]);
	return 0;
}
