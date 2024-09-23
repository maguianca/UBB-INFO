#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
int f;
void child_handler(int sig){
	printf("procesul copil terminat\n");
	exit(0);
}
void parent_handler(int sig){
        printf("procesul parinte terminat\n");
	kill(f,SIGUSR1);
	wait(0);
        exit(0);
}
void zombie_handler(int sig){
	printf("parintele asteapta sa termine copilul");
	wait(0);
}
int main(int argc,char**argv){
	f=fork();
	if(f==-1){
		perror("Error on fork");
		exit(1);
	}
	if(f==0){
		signal(SIGUSR1,child_handler);
	printf("[child],chld Pid: %d, ParentPid: %d\n", getpid(),getppid());
	while(1){
		printf("child working");
		sleep(3);
	}
	exit(0);
	}
	signal(SIGUSR1,parent_handler);
	signal(SIGCHLD, zombie_handler);
	printf("[parent],chld Pid: %d, ParentPid: %d\n", f,getpid());	
	  while(1){
                printf("parent working");
                sleep(3);
        }
	return 0;
}
