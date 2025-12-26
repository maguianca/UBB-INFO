#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc,char** argv)
{

    int pid = fork();
    if (pid == -1)                      // fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)                       
    {
        close(pd[1]);
	int n;
	n=0;
	read(pd[0],&n,sizeof(int));
	printf("[COPIL] am citit %d\n",n);//face flush il obliga sa faca goleasca bufferul 
	close(pd[0]);
	exit(0);
    }
    else                                
    {
        close(pd[0]);
	int n=5;
	write(pd[1],&n,sizeof(int));
	close(pd[1]);
	int status;
	wait(&status);

    }

    return 0;int pid = fork();
    if (pid == -1)                      // fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)                       // in child process
    {
        printf("[In CHILD]\tMy PID is %d\tParent PID is %d\n", getpid(), getppid());
    }
    else                                // in parent process
    {
        printf("[In PARENT]\tMy PID is %d\tChild PID is %d\n", getpid(), pid);
    }

    return 0;
}
