#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#define MAX_THR 100
int numere[MAX_THR],litere[MAX_THR],NR;
char arg[MAX_THR][30];
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
void* do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	char c;
	FILE*fd=fopen(arg[id],"r");
	if(fd==NULL){printf("error fopen\n");exit(1);}
	while(fscanf(fd,"%c",&c)!=EOF)
	{
		if(c>='A' && c<='Z')
		{
			pthread_mutex_lock(&mtx);
			litere[id]++;
			pthread_mutex_unlock(&mtx);
		}
		else if(c>='0'&& c<='9')
		{
			pthread_mutex_lock(&mtx);
			numere[id]+=c-'0';
			pthread_mutex_unlock(&mtx);
		}
	}
	fclose(fd);
	return NULL;
}
int main(int argc,char**argv)
{
	if(argc<2){printf("eroare");exit(1);}
	NR=argc-1;
	for(int i=0;i<NR;i++)
		strcpy(arg[i],argv[i+1]);
	pthread_t *t=malloc(NR*sizeof(pthread_t));
	for(int i=0;i<NR;i++)
	{
		int *id=malloc(sizeof(int));
		*id=i;
		pthread_create(&t[i],NULL,do_work,id);
	}
	for(int i=0;i<NR;i++)
		pthread_join(t[i],NULL);
	free(t);
	for(int i=0;i<NR;i++){
		printf("suma pt fisier %d este %d\n",i,numere[i]);
		printf("nr de litere din fisier %d este %d\n\n",i,litere[i]);
	}
	return 0;

}
