#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/stat.h>
void handler(int sig)
{
	wait(0);
}
int main( int argc, char* argv[])
{
        if(argc<2){
                perror("nr argc invalid argv[1]:fifo name");
                exit(1);
	}
	signal(SIGCHLD,handler);
	char* fifo_name=argv[1];
	int fd=open(fifo_name,O_RDONLY);
	int p[2];
	int r=pipe(p);
	if(r==-1){perror("error pipe");close(p[0]);close(p[1]);close(fd);exit(1);}
	int f=fork();
	if(f==-1)
	{ perror("error fork");close(p[0]);close(p[1]);close(fd);exit(1);}
	else if(f==0){
		//P1
		close(p[0]);
		int n,i;
		if(read(fd,&n,sizeof(int))<0){
			 perror("error read");close(p[1]);close(fd);exit(1);}
		for(i=1;i<=n;i++)
			if(n%i==0){
				if(write(p[1],&i,sizeof(int))<0)
				{	perror("error write");close(p[1]);close(fd);exit(1);
				}
				printf("[p1] a trimis %d\n",i);
				}
	close(p[1]);
	exit(0);
	}
	//P2
	close(p[1]);
	int n,len=1;
	printf("[P2] divizorii sunt\n:");
	while(len>0)
	{
		if((len=read(p[0],&n,sizeof(int)))<0)
		{ perror("error read"),close(p[0]);close(fd);exit(1);}
		printf("[P2] %d\n",n); 
	}
	close(p[0]);
	wait(0);
	if(unlink(fifo_name)<0){perror("error inchidere");exit(1);}
	return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>

int main(int argc, char *argv[]) {
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    int i;
    // the semaphore can be used to synchronized processes, not just threads
    // the condition is that the same semaphore can be accessed by all the processes
    // since after fork, the child process has copies of everything the parent had until the fork, we can't simply create a semaphore and use it
    // we will instead create a shared memory segment in the parent and place the semaphore there
    // the child processes will inherit copies of the shared memory ID, but the shared memory space will remain the same
    // se we can safely say that the semaphore placed inside the shared memory segment is the same for all processes
    sem_t *sem;
    // generate a key first so we can create a shared memory segment
    // ftok creates a key based on a file path and a number
    // the file has to exist on the system where the program is run, and the same combination of filepath + number must be provided by all the processes that want to access the same shared memory segment
    key_t shmkey = ftok("/dev/null", 24);
    // using the generated key, we create a shared memory segment big enough to contain one semaphore
    // we also grant read permissions to everyone
    // the IPC_CREAT flag indicates that the shared memory segment must be created if it does not exist
    int shmid = shmget(shmkey, sizeof(sem_t), 0644|IPC_CREAT);
    // we now link the shared memory segment to the previously declared pointer
    sem = (sem_t*) shmat(shmid, NULL, 0);
    // from here on, we treat this semaphore pointer as we would treat a regular semaphore pointer that is declared on the heap
    sem_init(sem, 1, 1);

    // we create processes
    for (i = 0; i < 10; i++) {
        int f = fork();
        if (f < 0) {
            perror("Oh no! Anyway...");
        } else if (f == 0) {    
            // each child locks the semaphore before sleeping
            sem_wait(sem);
            sleep(1);
            // and unlocks it once it is done
            sem_post(sem);
            exit(0);
        }
    }

    for (i = 0; i < 10; i++) {
        wait(0);
    }
    // destroy the semaphore
    sem_destroy(sem);
    // remove the link between the semaphore pointer and the shared memory space
    shmdt(sem);
    // delete the shared memory segment, so that memory can be used by other processes freely
    shmctl(shmid, IPC_RMID, 0);
    gettimeofday(&tv2, NULL);
    printf("Total time = %f seconds\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

    return 0;
}
