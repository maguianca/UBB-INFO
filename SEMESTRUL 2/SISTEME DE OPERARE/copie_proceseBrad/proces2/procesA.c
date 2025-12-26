#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
void make_fifo(char* fifo_name)
{
	if(mkfifo(fifo_name,0600)<0){perror("error fifo");exit(1);}
}
int cmmdc(int a,int b)
{
	if(a==0||b==0)
		return 1;
	return cmmdc(b,a%b);

}
int main( int argc, char* argv[])
{
	if(argc<2){
		perror("nr argc invalid argv[1]:fifo name");
		exit(1);
	}
	char* fifo_name=argv[1];
	make_fifo(fifo_name);
	int fd=open(fifo_name,O_WRONLY);
	int a,b,rez;
	printf("introduceti primul numar: ");
	scanf("%d",&a);
	printf("introduceti al doilea numar: ");
        scanf("%d",&b);
	rez=a*b;
	rez=rez/cmmdc(a,b);
	printf("cmmdc al lui %d si %d este: %d",a,b,rez);
	if(write(fd,&rez,sizeof(int))<0){perror("error writing");close(fd);exit(1);}
	close(fd);
	return 0;
}
