#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main( int argc, char** argv)
{
	int n=15;
	for(int i=2;i<n/2;i++)
	{
		int pid=fork();
		if(pid==-1){perror("fork");exit(1);}
		else if(pid==0){
			FILE*fd=fopen("fisier.txt","r");
			if(fd==NULL){perror("fopen()");exit(1);}
			FILE*fd1=fopen("tmp.txt","w");
		        if(fd1==NULL){perror("fopen()");exit(1);}
			int x;
			while(fscanf(fd,"%d",&x)>0){
				if(x%i!=0|| x==i)
				{
					fprintf(fd1,"%d\n",x);
				}

			}
			fclose(fd);
			fclose(fd1);
			remove("fisier.txt");
			rename("tmp.txt","fisier.txt");
			exit(0);
		}else wait(0);

	}return 0;}

