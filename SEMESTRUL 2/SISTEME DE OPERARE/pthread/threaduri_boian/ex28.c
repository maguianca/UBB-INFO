#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#define MAX_NUM 100000
int MAX_THR,NR,numere[MAX_NUM];
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;
void*do_work(void*argv)
{
	while(1){
	int ok=0;
	pthread_mutex_lock(&mtx);
        for(int i=0;i<NR-1;i++)
        {
                if(numere[i+1]<numere[i])
                        ok=1;
        }
	//pthread_mutex_unlock(&mtx);
        if(ok==0)break;
	pthread_mutex_unlock(&mtx);
	int i=rand()%NR;
	int j=rand()%NR;
	if(i<j){
		pthread_mutex_lock(&mtx);
		if(numere[i]<numere[j])
		{	//pthread_mutex_lock(&mtx);
			int aux=numere[i];
			numere[i]=numere[j];
			numere[j]=aux;
			//pthread_mutex_unlock(&mtx);
		}
		pthread_mutex_unlock(&mtx);
	}else
	{
		pthread_mutex_lock(&mtx);
		if(numere[i]>numere[j])
                {       //pthread_mutex_lock(&mtx);
                        int aux=numere[i];
                        numere[i]=numere[j];
                        numere[j]=aux;
                        //pthread_mutex_unlock(&mtx);
                }
		pthread_mutex_unlock(&mtx);
	}
	}
	pthread_mutex_unlock(&mtx);
	pthread_barrier_wait(&barr);
	return NULL;
}
void*print(void*argv)
{

	pthread_barrier_wait(&barr);
	for(int i=0;i<NR;i++)
		printf("numere[%d]=%d\n",i,numere[i]);
	return NULL;
}
int main(int argc,char**argv)
{
	printf("introduceti un nr n\n");
	scanf("%d",&NR);
	MAX_THR=NR;
	srand(time(NULL));
	for(int i=0;i<NR;i++)
		numere[i]=rand()%1001;
	pthread_t tid[MAX_THR],printer;
	pthread_barrier_init(&barr,NULL,MAX_THR+1);
	for(int i=0;i<MAX_THR;i++)
	{
		//int*id=malloc(sizeof(int));
		//*id=i;
		pthread_create(&tid[i],NULL,do_work,NULL);
	}
	 for(int i=0;i<MAX_THR;i++)
        {
                pthread_join(tid[i],NULL);
        }
	pthread_create(&printer,NULL,print,NULL);
	pthread_join(printer,NULL);
	pthread_barrier_destroy(&barr);
	return 0;
}
