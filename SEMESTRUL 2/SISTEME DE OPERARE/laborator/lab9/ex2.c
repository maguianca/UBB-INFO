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
		if(pid==-1)
		{
			perror("fork()");
			exit(1);
		}
		if(pid==0)
		{
			//copil
			FILE*fd=fopen("numere.txt","r");
			if(fd==NULL)
			{
				perror("f2open()");
				exit(1);
			}
			FILE*fd2=fopen("tmp.txt","w");
                        if(fd2==NULL)
                        {
                                perror("1fopen()");
                                exit(1);
                        }
			int nr=0;
			while(fscanf(fd,"%d",&nr)>0)
			{
				printf("[child] am citit %d\n",nr);
				if(nr%i!=0 || nr==i)
				{
					fprintf(fd2,"%d\n",nr);
				}
			}
			fclose(fd);
			fclose(fd2);
				//trb inchisi descriptorii
			remove("numere.txt");
			rename("tmp.txt","numere.txt");
			exit(0);
		}
		wait(NULL);
	}
	return 0;
}
