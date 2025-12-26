#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
void handler(int sig){
	wait(0);
}
void make_fifo(char* fifo_name)
{
        if(mkfifo(fifo_name,0600)<0){
                perror("error creating fifo");
                exit(1);
                }
}
int main(int argc,char** argv)
{
        if(argc<2){perror("mod utilizare argv[1]:fifo");exit(1);}
	signal(SIGCHLD,handler);
        char* fifo_name=argv[1];
        make_fifo(fifo_name);
        int fd=open(fifo_name, O_WRONLY);
        if(fd==-1){perror("fifo error");exit(1);}
	int p[2];
	int r=pipe(p);
	if(r==-1){perror("error pipe");close(fd);exit(1);}
	int f=fork();
	if(f==-1){perror("error fork");close(p[0]);close(p[1]);close(fd);exit(1);}
	else if(f==0){
	//suntem in P1
	close(p[0]);
	char file[50];
	printf("introduceti path -ul: ");
	scanf("%s",file);
	if(write(p[1],file,strlen(file)+1)<0){perror("error write");
	close(p[1]);close(fd);exit(1);}
	printf("P1 ->P2 path: %s\n",file);
	close(p[1]);
	exit(1);
	}
	//suntem in P2
	char file[50];
	close(p[1]);
	if(read(p[0],file,sizeof(file))<0){perror("error read");
	close(p[0]);close(fd);exit(1);}
	int arr[6]={0};
	int count=0;
	char voc[]="AEIOU";
	for(int i=0;i<strlen(voc);i++)
	{
		count=0;
		for(int j=0;j<strlen(file);j++)
			if(file[j]==voc[i])
				count++;
		arr[i]=count;
	}
	for(int i=0;i<5;i++){
		if(write(fd,&arr[i],sizeof(int))<0){perror("error 2b");close(fd);close(p[0]);exit(1);}
		printf("P2->B voc[%c]: frecventa %d\n",voc[i],arr[i]);
	}
	close(p[0]);
	close(fd);
	wait(0);
	return 0;
}
