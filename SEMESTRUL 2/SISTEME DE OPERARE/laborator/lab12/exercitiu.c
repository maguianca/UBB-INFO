//se dau 100000 de numere.Folosind un nr potrivit de threaduri sa se 
//determine cea mai mica diferenta dintre 2 numere din fiecare intreval de 2000 de numere 
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<limits.h>
#include<time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#define MAX_NUM 100000
#define MAX_TR 50
int numere[MAX_NUM],minDif=INT_MAX;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
void* doDif(void*arg){
	int id=*(int*)arg;
	free(arg);
	int st=id*MAX_NUM/MAX_TR;
	int dr=st+MAX_NUM/MAX_TR;
	int dif=INT_MAX;
	for(int i=st;i<dr-1;i++){
		for(int j=i+1;j<dr;j++)
		{
			int x=abs(numere[i]-numere[j]);
			if(dif>x)
				dif=x;

		}
	}
	printf("[Thread %d] Diferenta:%d\n",id,dif);
	pthread_mutex_lock(&mtx);
	if(dif<minDif) minDif=dif;
	pthread_mutex_unlock(&mtx);
	return NULL;
}
int main(int argc,char**argv)
{
	//generare 100000 de numere aleatoare
	//srand(time(NULL));
	//for(int i=0;i<MAX_NUM;i++)
	//{
	//		numere[i]=rand();
	//}
	//citesc 100000 de nr aleatoare
	int fd=open("file.bin",O_RDONLY);
	if(fd==-1){perror("open()");exit(1);}
	for(int i=0;i<MAX_NUM;i++)
		if(read(fd,&numere[i],sizeof(int))<0){perror("read");exit(1);}
	close(fd);
	pthread_t tid[MAX_TR];
	for(int i=0;i<MAX_TR;i++)
	{
		int *id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,doDif,id);
	}
	 for(int i=0;i<MAX_TR;i++)
        {
                pthread_join(tid[i],NULL);
        }
	printf("Diferenta:%d\n",minDif);
	//close(fd);
	return 0;
}
