#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
int*aparitii;
int frecventa[10];
#define MAX_THR 100
char fisiere[MAX_THR][30];
char caractere[MAX_THR][2],NR;
void*do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	FILE*fd=fopen(fisiere[id],"r");
	if(fd==NULL){printf("error fopen");exit(1);}
	char ch[2],c;
	strcpy(ch,caractere[id]);
	int contor=0,ok=0;
	while(fscanf(fd,"%c",&c)!=EOF)
	{
		if(c>='0'&&c<='9')
		{
			pthread_mutex_lock(&mtx);
			frecventa[c-'0']++;
			pthread_mutex_unlock(&mtx);
		}
		if(c==ch[0]&& ok==0)
		{
			ok=1;
			pthread_mutex_lock(&mtx);
			aparitii[id]=contor;
			pthread_mutex_unlock(&mtx);
		}
		contor++;

	}
	if(ok==0){
		pthread_mutex_lock(&mtx);
                        aparitii[id]=-1;
                        pthread_mutex_unlock(&mtx);
	}
	return NULL;
}
int main(int argc,char**argv)
{
	if(argc<2 || argc%2==0){printf("error");exit(1);}
	NR=(argc-1)/2;
	for(int i=0;i<NR*2;i+=2)
	{
		strcpy(fisiere[i/2],argv[i+1]);
		printf("fisiere %d %s\n",i,fisiere[i/2]);
		strcpy(caractere[i/2],argv[i+2]);
		  printf("caracter %d %s\n",i,caractere[i/2]);

	}
	aparitii=malloc(NR*sizeof(int));
	pthread_t*tid=malloc(sizeof(pthread_t)*NR);
	for(int i=0;i<NR;i++)
	{
		int *id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	for(int i=0;i<NR;i++)
		pthread_join(tid[i],NULL);
	for(int i=0;i<NR;i++)
	{
		printf("fisierul %s : caracterul %s apare pe poz %d\n",fisiere[i],caractere[i],aparitii[i]);
	}
	for(int i=0;i<10;i++)
		printf("frecventa %d este %d\n",i,frecventa[i]);

	free(aparitii);
	return 0;
}
