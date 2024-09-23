#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
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
        char* fifo_name=argv[1];
        make_fifo(fifo_name);
        int fd=open(fifo_name, O_WRONLY);
        if(fd==-1){perror("fifo error");exit(1);}
        int n;
        printf("introduceti un nr n: ");
        scanf("%d",&n);
	if(write(fd,&n,sizeof(int))<0)
                                {perror("error writing");close(fd);exit(1);}
        printf("[A] sending B %d\n",n);
        for(int i=1;i<=n;i++)
                if(n%i==0)
                        { if(write(fd,&i,sizeof(int))<0)
                                {perror("error writing");close(fd);exit(1);}
                                printf("[A] sending B %d\n",i);
                        }
        close(fd);
        return 0;
}


