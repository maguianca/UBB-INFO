#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#define SHM_KEY 9876
#define SHM_SIZE 200
char* data=(char *)(-1);
char voc[]="aeiouAEIOU";
int main(int argc, char* argv[])
{
	int shmid=shmget(SHM_KEY,SHM_SIZE,0);
	int arr[11]={0},count=0;
	data=shmat(shmid,NULL,0);
	if(data==(char*)(-1)){perror("error");exit(1);}
	for(int  i=0;i<strlen(voc);i++)
	{
		count=0;
		for(int j=0;j<strlen(data);j++)
			if(voc[i]==data[j])count++;
		arr[i]=count;
	}
	for(int i=0;i<11;i++)
		printf(" arr[%c]: frecv %d\n",voc[i],arr[i]);
	if(shmdt(data)==-1){perror("error");exit(1);}
	return 0;
}
