#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#define MAX_THR  10
int var=1,numere[10000],count=0;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
int contine2(int x)
{
	if(x%2==0)return 1;
	int n=x;
	while(n>0)
	{
		if(n%10==2)return 1;
		n=n/10;
	}
	return 0;
}
void*do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	while(1){
		pthread_mutex_lock(&mtx);
		if(var==55)break;
		var++;
		if(contine2(var)){
			numere[count++]=var;
		printf("thread %d a adaugat %d\n",id,var);	
		}
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx);
	return NULL;

}
int main(int argc,char**argv)
{
	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int*id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	for(int i=0;i<MAX_THR;i++)
		pthread_join(tid[i],NULL);
	for(int i=0;i<count;i++)
		printf("numere[%d]=%d\n",i,numere[i]);
	return 0;
}
