#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
void handler(int sig)
{
	wait(0);
}
int main(int argc,char** argv)
{
	if(argc<2){perror("mod utilizare argv[1]:fifo");exit(1);}
	char* fifo_name=argv[1];
	int fd=open(fifo_name, O_RDONLY);
	if(fd==-1){perror("fifo error");exit(1);};
	signal(SIGCHLD,handler);
	int p[2];
	int r=pipe(p);
	if(r==-1){perror("error pipe");close(fd);exit(1);}
	int f=fork();
	if(f==-1){perror("error fork");close(fd);close(p[0]);close(p[1]);exit(1);}
	else if(f==0){
	//suntem in P1
	close(p[0]);
	int n,sum=0,i=0;
	if(read(fd,&n,sizeof(int))<0){perror("error reading");close(p[1]);close(fd);exit(1);}
	while(i!=n){
			if(read(fd,&i,sizeof(int))<0)
				{perror("error writing");close(fd);close(p[1]);exit(1);}
			sum+=i;
		    }
	if(write(p[1],&sum,sizeof(int))<0){perror("error pipe");close(fd);close(p[1]);exit(1);}
	printf("P1 sending P2 sum %d\n",sum);
	close(p[1]);
	exit(0);
	}
	//suntem in P2
	close(p[1]);
	int sum;
	if(read(p[0],&sum,sizeof(int))<0){perror("error read");close(fd);close(p[1]);exit(1);}
	printf("[p2] suma este %d\n",sum);
	wait(0);
	if(unlink(fifo_name)<0){perror("error unlinking");exit(1);}
	return 0;
}
