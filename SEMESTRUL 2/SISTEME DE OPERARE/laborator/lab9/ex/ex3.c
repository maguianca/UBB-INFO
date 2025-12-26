#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
int main(int argc,char**argv)
{
	char vocale[]="aeiouAEIOU";
	FILE* fd=fopen("text","r");
	char sir[256];int k;
	if((k=fread(sir,256,sizeof(char),fd))<0){perror("error");fclose(fd);exit(1);}
	printf("am citit %s\n",sir);
	for(int i=0;i<strlen(vocale);i++)
	{
		int p=fork();
		if(p==-1){perror("error");fclose(fd);exit(1);}
		else if(p==0){
			int count=0;
			for(int j=0;j<strlen(sir);j++)
			{
				if(sir[j]==vocale[i])count++;
			}
			printf("voc[%d]=%d\n",i,count);

		exit(0);
		}wait(0);
	
	}
	fclose(fd);
	return 0;

}
