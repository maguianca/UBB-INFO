#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#define MAX_NUM 90000
#define MAX_THR 100
int numere[MAX_NUM],NR;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
int prim(int x)
{
	if(x<2)return 0;
	if(x%2==0)return 0;
	for(int d=3;d*d<=x;d+=2)
		if(x%d==0)return 0;
	return 1;
}
void* do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	int medie=0,count=0,frecventa[100]={0},sum=0;
	int st=id*NR/MAX_THR;
	int dr=st+NR/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		if(numere[i]<=100 && prim(numere[i]))
		{
			pthread_mutex_lock(&mtx);
			sum+=numere[i];
			count++;
			frecventa[numere[i]]++;
			pthread_mutex_unlock(&mtx);
		}	
	}
	pthread_mutex_lock(&mtx);
	if(count!=0){
		medie=sum/count;
	for(int i=2;i<=97;i++)
		if(prim(i) && frecventa[i]<medie)
			printf("thread: %d %d apare de %d ori medie=%d\n",id,i,frecventa[i],medie);
	}
	pthread_mutex_unlock(&mtx);
	return NULL;
}
int main(int argc,char**argv)
{
	printf("introduceti n:\n");
	scanf("%d",&NR);
	int fd=open("rand.txt",O_RDONLY);
for(int i=0;i<NR;i++){
		read(fd,&numere[i],1);
		//printf("%d\n",numere[i]);
	}
	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int* id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);

	}
	for(int i=0;i<MAX_THR;i++)
        {
                pthread_join(tid[i],NULL);

        }
	return 0;
}
