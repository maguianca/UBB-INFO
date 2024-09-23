#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>
#define MAX_NUM 1100000
int NR,MAX_THR,numere[MAX_NUM],sum,NR2;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
void* do_work(void*argv)
{
        int id=*(int*)argv;
        free(argv);
        int contor=0;
        int st=id*NR2/MAX_THR;
        int dr=st+NR2/MAX_THR;
        for(int i=st;i<dr;i++)
        {
                        pthread_mutex_lock(&mtx);
                        sum+=numere[i];
                        pthread_mutex_unlock(&mtx);

        }
        return NULL;
}
int main(int argc,char**argv)
{
        
        FILE*fd=fopen("testmatrix","r");
        //if(fd==-1){perror("");exit(1);};
	fscanf(fd,"%d",&NR);
	printf("NR %d\n",NR);
	fscanf(fd,"%d",&MAX_THR);
        printf("MAX_THR %d\n",MAX_THR);
	int c=0; 
	NR2=MAX_THR*NR;
        for(int i=0;i<NR;i++)
		for(int j=0;j<MAX_THR;j++)
                	fscanf(fd,"%d",&numere[c++]);
        pthread_t tid[MAX_THR];
        for(int i=0;i<MAX_THR;i++)
        {
                int *id=malloc(sizeof(int));
                *id=i;
                pthread_create(&tid[i],NULL,do_work,id);
        }
        for(int i=0;i<MAX_THR;i++)
                pthread_join(tid[i],NULL);
        printf("suma %d\n",sum);
        return 0;
}
