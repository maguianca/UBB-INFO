#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc, char* argv[])
{
        if(argc!=2)
        {
                perror("nr insuf de argm");
                perror("mod utilizare: argc[1]:fifo");
	
	}
	char* fifo_name=argv[1];
	int fd=open(fifo_name,O_RDONLY);
	int sum;
	if(read(fd,&sum,sizeof(int))<0){perror("error");close(fd);exit(1);}
	printf("[B] suma: %d",sum);
	close(fd);
	return 0;
}
