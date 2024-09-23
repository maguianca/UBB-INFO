#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
#define MAX_NUM 10000
int MAX_THR, NR,numere[MAX_NUM],frecventa[11];
void*do_work(void*argv)
{
	int id=*(int*)argv;
	id=id+1;
	free(argv);
	int n=numere[id];
	while(n>0)
	{
		pthread_mutex_lock(&mtx);
		frecventa[n%10]++;
		n=n/10;
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}
int main(int argc,char**argv)
{
	if(argc<2){printf("nr argv insuf");exit(1);}
	MAX_THR=argc-1;
	for(int i=0;i<argc;i++)
		numere[i]=atoi(argv[i]);
	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR;i++){
		int*id=malloc(sizeof(int));
		*id=i;	
		pthread_create(&tid[i],NULL,do_work,id);
	}
	for(int i=0;i<MAX_THR;i++)
                pthread_join(tid[i],NULL);
	for(int i=0;i<10;i++)
	printf("%d apare de %d\n",i,frecventa[i]);
	return 0;
}
