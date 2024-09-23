#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "header.h"
int main(int argc,char**argv){
	if(mkfifo(myfifo1,0600)<0){
		perror("error fifo");
		exit(1);
	}
	if(mkfifo(myfifo2,0600)<0){
		 perror("error fifo");
                exit(1);
	}
	int fd_write=open(myfifo1,O_WRONLY);
	if(fd_write==-1){
		perror("error opening fifo1");
		exit(1);
	}
	int fd_read=open(myfifo2,O_RDONLY);
        if(fd_write==-1){
                perror("error opening fifo2");
		close(fd_write);
                exit(1);
        }
	srandom(time(0));
	int nr=0;
	while(nr!=10){
		nr=random()%10+1;
		if(write(fd_write,&nr,sizeof(int))<0){
			perror("eroare");
			break;}
		printf("[A] trimite:%d\n",nr);
		if(read(fd_read,&nr,sizeof(int))<0){
                        perror("eroare");
                        break;}
                printf("[A] primeste:%d\n",nr);
	}
	close(fd_read);
	close(fd_read);
	if(unlink(myfifo1)<0){perror("error");}
	if(unlink(myfifo2)<0){perror("error");}
	return 0;
}









