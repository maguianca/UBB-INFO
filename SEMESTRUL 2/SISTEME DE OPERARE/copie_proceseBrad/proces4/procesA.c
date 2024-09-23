#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<ctype.h>
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
                perror("mod utilizare: argc[1]:fifo argv[2]: filename");exit(1);
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
	char a;
        printf("introduceti n: ");
        scanf("%d",&n);       
	for(int i=0;i<n-1;i++)
        	{
                if(fscanf(file,"%c",&a)<0){
                        perror("error fscanf");fclose(file);close(fd);exit(1);}
		}
		if(fscanf(file,"%c",&a)<0){
                        perror("error fscanf");fclose(file);close(fd);exit(1);}
                if(write(p[1],&a,1)<0)
                    {perror("error"); fclose(file);close(fd);exit(1);}                
		printf("[p1] trimite %c\n",a);

        close(p[1]);
        exit(0);
        }
        //P2
        close(p[1]);
	char a;
	if(read(p[0],&a,1)<0){perror("error");close(p[0]);close(fd);fclose(file);exit(1);}
	printf("[p2] primeste %c\n",a);
        if(isalpha(a))
		printf("[p2] %c este litera\n",a);
	else if(isdigit(a))
		printf("[p2] %c este cifra\n",a);
	else if(isspace(a))
		printf("[p2] %c este spatiu\n",a);
	else 
		printf("[p2] %c este altceva\n",a);
        wait(0);
        close(p[0]);
        fclose(file);
        if(write(fd,&a,1)<0){perror("error");close(fd);exit(1);}        
	printf("[p2] a trimis la B %c\n",a);
        if(unlink(fifo_name)<0){perror("error close");exit(1);}
        return 0;
}
