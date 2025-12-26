#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<signal.h>
#include<string.h>
#define SHM_KEY 9876
#define SHM_SIZE 200
char* data=(char *)(-1);
int shmid=0;
void handler(int sig)
{
	if(data!=(char *)(-1)){
		if(shmdt(data)==-1){perror("error on det");exit(1);}
	}
	if(shmid>0){
		if(shmctl(shmid,IPC_RMID,0)==-1){perror("error on det");}
	}
	exit(0);
}
int main(int argc,char* argv[])
{
	int k;
	char buf[100];
	signal(SIGINT,handler);
	if((shmid=shmget(SHM_KEY,SHM_SIZE,IPC_CREAT|0644))==-1){
		perror("error()");exit(1);}
	data=shmat(shmid,NULL,0);
	if(data==(char*)(-1)){perror("error on at");exit(1);}
	while(1){
		if((k=read(0,buf,100*sizeof(char)))<0){
			perror("error read");exit(1);
		}
		buf[k-1]=0;
		strcpy(data,buf);
	}
	return 0;
}

