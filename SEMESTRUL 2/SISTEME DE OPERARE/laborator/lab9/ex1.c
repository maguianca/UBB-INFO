#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#define MAX_SIZE 100
//pipe trb sa fie inainte de fork daca nu nu mosteneste copilul 
//ordinea: pipe() fork()
int main(int argc, char** argv)
{
	char sir[]="aeiouBaeiouCghghaqquu";
	char vocale[]="aeiouAEIOU";
	for (int i=0;i<strlen(vocale);i++)
	{
		int pd[2];
		if(pipe(pd)==-1)
		{
			perror("pipe()");
			exit(1);
		}
		int pid=fork();
		if(pid ==-1)
		{
			perror("fork()");
			exit(1);
		}
		if( pid == 0)
		{
			close(pd[0]);//capatul de read ca in copil fac write
			char* tmp=malloc(MAX_SIZE*sizeof(char));
			int k=0;
			for(int j=0;j<strlen(sir);j++)
			{
				if(sir[j]!=vocale[i])
				{
					tmp[k++]=sir[j];	
				}
			}
			tmp[k]='\0';
			write(pd[1],tmp,MAX_SIZE);	
			close(pd[1]);
			free(tmp);
			exit(0);//obligatoriu pt ca nu mai punem else
		}
		//suntem in parinte
		close(pd[1]);
		char* tmp=malloc(MAX_SIZE*sizeof(char));
		//in parinte fac read
		read(pd[0],tmp,MAX_SIZE);
		strcpy(sir,tmp);
		close(pd[0]);
		free(tmp);
		wait(NULL);
	}
	printf("SIR FINAL: %s\n",sir);
	return 0;
}
