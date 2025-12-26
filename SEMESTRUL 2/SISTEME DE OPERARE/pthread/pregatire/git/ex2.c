#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
char cuvinte[6][100],count[6],ap[6],NR,MAX_THR,numere[100][20],x=0;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;
void*do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	pthread_mutex_lock(&mtx);
		for(int i=0;i<=4;i++){
				int ok=0;
				for(int j=0;j<strlen(numere[id]);j++)
				{
					if(numere[id][j]=='a'+i)
					{
						printf("thread %d %s\n",id,numere[id]);
						if(ok==0){
							strcat(cuvinte[i],numere[id]);
							strcat(cuvinte[i]," ");
							count[i]++;
							ap[i]++;
							ok=1;
						}
						else ap[i]++;
					}
				}
	}
	pthread_mutex_unlock(&mtx);
	pthread_barrier_wait(&barr);
	return NULL;
}
int main(int argc,char**argv)
{
	if(argc<2){printf("argv insuf");exit(1);}
	MAX_THR=argc-1;
	pthread_barrier_init(&barr,NULL,MAX_THR);
	//memset(numere,0,2000);
	int size=0;
	for(int i=1;i<MAX_THR+1;i++){
		strcpy(numere[i-1],argv[i]);
	}
	for(int i=0;i<MAX_THR;i++)
		printf("%s\n",numere[i]);
	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int *id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	for(int i=0;i<MAX_THR;i++)
		pthread_join(tid[i],NULL);
	//pthread_barrier_wait(&barr);
	for(int i=0;i<=4;i++)
	{
		printf("%c: aparitii %d,cuvinte %d => %s\n",'A'+i,ap[i],count[i],cuvinte[i]);
	}

	return 0;
}
