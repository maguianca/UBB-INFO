#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#define MAX_NUM 100000
char buffer[MAX_NUM],nou[MAX_NUM],NR;
#define MAX_THR 10
FILE*fd;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;
void* do_work(void*argv)
{
	int size=0;
	char*buf_loc=malloc(sizeof(char)*1000);
	while(!feof(fd)){
		pthread_barrier_wait(&barr);
		pthread_mutex_lock(&mtx);
		int rep=rand()%3+1;
		char w[21];
		for(int i=0;i<rep;i++)
		{
			if(feof(fd)){pthread_mutex_unlock(&mtx);break;}
			if(fscanf(fd,"%s",w)!=1)
			{	
				pthread_mutex_unlock(&mtx);
				pthread_barrier_wait(&barr);
				free(buf_loc);
				return NULL;
			}
			int count=strlen(w);
			sprintf(buf_loc+count,"%s",w);
			size+=count;

		}
		pthread_mutex_unlock(&mtx);
		pthread_barrier_wait(&barr);

	}
	buf_loc[size]=0;
	return buf_loc;
}
int main(int argc,char**argv)
{
	if(argc!=3){printf("nr argv insuf");exit(1);}
	NR=atoi(argv[1]);
	fd=fopen(argv[2],"r");
	printf(" %d   %s\n",NR,argv[2]);
	pthread_t tid[NR];
	pthread_barrier_init(&barr,NULL,NR);
	for(int i=0;i<NR;i++)
	{
		pthread_create(&tid[i],NULL,do_work,NULL);
	}
	for(int i=0;i<NR;i++)
        {
		char*result;
                if(pthread_join(tid[i],(void**)&result)==0){
			if(result!=NULL)
			{
				printf("thread %d  %s \n",i,result);
				free(result);
			}
		}else printf("error join");
        }
	pthread_barrier_destroy(&barr);
	return 0;
}
