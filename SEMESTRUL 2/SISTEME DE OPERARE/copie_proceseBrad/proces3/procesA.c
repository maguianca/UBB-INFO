#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void make_fifo(char* fifo_name)
{
        if(mkfifo(fifo_name,0600)<0)
        {
                perror("error on fifo");
                exit(1);
        }
}
void handler(int sig)
{
	wait(0);
}
int main(int argc, char* argv[])
{
        if(argc!=3)
        {
                perror("nr insuf de argm");
                perror("mod utilizare: argc[1]:fifo argv[2]: filename");                exit(1);
        }
	signal(SIGCHLD,handler);
        char* fifo_name=argv[1];
        char* file_name=argv[2];
        make_fifo(fifo_name);
        int fd=open(fifo_name,O_WRONLY);
        if(fd<0){perror("error fifo writing");exit(1);}
        FILE* file=fopen(file_name,"r");
        if(file==NULL){
                perror("error opening file");
                close(fd);
                exit(1);
                }
	int p[2];
	int r=pipe(p);
	if(r==-1){perror("error"); fclose(file);close(fd);exit(1);}
	int f=fork();
	if(f==-1){perror("error"); fclose(file);close(fd);exit(1);}
	else if(f==0){
	//P1
	close(p[0]);
        int n;
	printf("introduceti n: ");
	scanf("%d",&n);
	 if(write(p[1],&n,sizeof(int))<0)
                    {perror("error"); fclose(file);close(fd);exit(1);}
        for(int i=0;i<n;i++)
	{
		int a;
		if(fscanf(file,"%d",&a)<0){
			perror("error fscanf");fclose(file);close(fd);exit(1);
		}
		if(write(p[1],&a,sizeof(int))<0)
                    {perror("error"); fclose(file);close(fd);exit(1);}
		printf("[p1] trimite %d\n",a);

	}
	close(p[1]);
	exit(0);
	}
	//P2
	close(p[1]);
	int sum=0,n;
	if(read(p[0],&n,sizeof(int))<0){perror("error");close(p[0]);close(fd);exit(1);}
	 for(int i=0;i<n;i++)
        {
                int a;
                if(read(p[0],&a,sizeof(int))<0)
                    {perror("error"); fclose(file);close(fd);exit(1);}                
		printf("[p2] a primit %d\n",a);
		if(a%2==0)
			sum+=a;
        }
	wait(0);
	close(p[0]);
	fclose(file);
	if(write(fd,&sum,sizeof(int))<0){perror("error");close(fd);exit(1);}
	printf("[p2] a trimis la b %d",sum);
	if(unlink(fifo_name)<0){perror("error close");exit(1);}
	return 0;
}
