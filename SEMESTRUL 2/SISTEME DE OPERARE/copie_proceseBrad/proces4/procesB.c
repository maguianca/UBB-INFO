#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main(int argc, char* argv[])
{
        if(argc!=2)
        {
                perror("nr insuf de argm");
                perror("mod utilizare: argc[1]:fifo");

        }
        char* fifo_name=argv[1];
        int fd=open(fifo_name,O_RDONLY);
        char a;
        if(read(fd,&a,sizeof(char))<0){perror("error");close(fd);exit(1);}        
	printf("[B] ascii code of %c: %d",a,a);
        close(fd);
        return 0;
}

