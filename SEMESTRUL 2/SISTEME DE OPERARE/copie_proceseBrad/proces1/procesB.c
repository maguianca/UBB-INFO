#include "common.h"
void divizori(int num)
{
    printf("[P2] Divizorii lui %d:\n", num);
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}
void handler(int sig)
{
	wait(0);


}
int main(int argc, char* argv[])
{
        if(argc!=2)
        {
                perror("nr insuf de argm");
                perror("mod utilizare: argc[1]:fifo");                exit(1);
        }
	signal(SIGCHLD,handler);
        char* fifo_name=argv[1];
	int fd=open(fifo_name,O_RDONLY);
	if(fd==-1)
	{	perror("error on fifo");exit(1);
	}
	int p[2];
	int r=pipe(p);
	if(r==-1)
	{
		perror("error pipe()");close(p[0]);close(p[1]);exit(1);
	}
	int f1=fork();
	if(f1==-1){
		  perror("error fork1()");close(p[0]);close(p[1]);exit(1);
	}else if(f1==0){
		//in P1
		close(p[0]);
		int sum=0;
		char c;
		while(read(fd,&c,1)>0)
		{
			sum+=(c-'0');
		}
                printf("[P1] suma este %d\n",sum);
		if(write(p[1],&sum,sizeof(int))<0)
		{
			perror("error on p");close(p[1]);close(fd);exit(1);
		}
		close(fd);
		close(p[1]);
		exit(0);	
	}
	//suntem in P2
	close(p[1]);
	int sum;
	if(read(p[0],&sum,sizeof(int))<0){
		perror("error on read");close(p[1]);close(fd);exit(1);}
	divizori(sum);
	wait(0);
	close(p[0]);
	if(unlink(fifo_name)<0){
		perror("error deleting");
		exit(1);
	}
	return 0;
}
