#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main(int argc,char*argv[])
{
	char vocale[]="aeiouAEIOU",sir[]="ANa are mere pere sssss";
	for(int i=0;i<strlen(vocale);i++)
	{
		int pd[2];
		if(pipe(pd)==-1){
			perror("error");exit(1);}
		int f=fork();
		if(f==-1){
                        perror("error");exit(1);}
		else if(f==0){
			close(pd[0]);
			char s[256]="";
			int k=0;
			for(int j=0;j<strlen(sir);j++)
				if(sir[j]!=vocale[i])
					s[k++]=sir[j];
			s[k]='\0';
			if(write(pd[1],s,strlen(sir))<0){
				perror("error");close(pd[1]);exit(1);}
			close(pd[1]);
			exit(0);
		}
		close(pd[1]);
		char s[256]="";
		if(read(pd[0],s,sizeof(s))<0){
                                perror("error");close(pd[0]);exit(1);} 
		strcpy(sir,s);
		close(pd[0]);
		wait(0);

	}
	printf("sir: %s",sir);
	return 0;
}










