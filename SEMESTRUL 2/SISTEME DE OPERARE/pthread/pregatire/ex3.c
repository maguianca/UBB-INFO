#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<time.h>
#include<unistd.h>
#define MAX_THR 100
#define MAX_NUM 80000
int NR,numere[MAX_NUM],min=INT_MAX,medie;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;
int frecventa[105],suma;
void* doWork(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	int st=id*NR/MAX_THR;
	int dr=st+NR/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		pthread_mutex_lock(&mtx);
		if(numere[i]<=100 && numere[i]%2==0 && numere[i]>=2)
		{	frecventa[numere[i]]++;
			suma++;
		}
		pthread_mutex_unlock(&mtx);
	}
	pthread_barrier_wait(&bar);
	pthread_mutex_lock(&mtx);
	//for(int i=2;i<=100;i+=2){
	//	suma+=frecventa[i];
	//}
	medie=suma/50;
	printf("media %d\n",medie);
	//pthread_mutex_lock(&mtx);
	for(int i=2;i<=100;i+=2)
		if(abs(frecventa[i]-medie)<min)min=abs(frecventa[i]-medie);
	pthread_mutex_unlock(&mtx);
	return NULL;
}
int main(int argc,char*argv[])
{
	srandom(time(NULL));
	int fd=open("random",O_RDONLY);
	if(fd==-1){perror("open");exit(1);}
	printf("introduceti n:");
	scanf("%d",&NR);
	//NR=10000;
	for(int i=0;i<NR;i++){
		//if(read(fd,&numere[i],sizeof(int))<0){perror("error");exit(1);}
		numere[i]=rand()%1000;
	}
	//close(fd);
	pthread_t tid[MAX_THR];
	pthread_barrier_init(&bar,NULL,MAX_THR);
	for(int i=0;i<MAX_THR;i++)
	{
		int*p=(int*)malloc(sizeof(int));
		*p=i;
		pthread_create(&tid[i],NULL,doWork,p);
	}
	for(int i=0;i<MAX_THR;i++){
		pthread_join(tid[i],NULL);
	}
	pthread_barrier_destroy(&bar);
	 for(int i=2;i<=100;i+=2)
        {
                if(abs(frecventa[i]-medie)==min)
                        printf("%d are frecventa %d\n",i,frecventa[i]);
        }
	return 0;
}
