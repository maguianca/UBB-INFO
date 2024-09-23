/*cuvinte_propozitii:în fișier sunt cuvinte, nu contează câte pe 
fiecare linie. 
Procesul a le citește din fișier și le transmite prin pipe. 
Procesul b citește de la tastatură pe rând numere pana se introduce 0. 
Face propoziții cu primele nr cuvinte din fișier și le afișează pe ecran*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
int main(int argc,char* argv[])
{
	FILE* fd=fopen("fisier.txt","r");
	if(fd==NULL){perror("fopen");exit(1);}
	int p[2];
	int r=pipe(p);
	if(r==-1){perror("error pipe");fclose(fd);exit(1);}
	int f=fork();
	if(f==-1){perror("error fork()");fclose(fd);close(p[1]);close(p[0]);exit(1);}
	else if(f==0)
	{
	//SUNTEM IN A
	close(p[0]);
	char s[100]="";
	while((fscanf(fd,"%s",s))>0){
		//s[k]='\0';
	if(write(p[1],s,strlen(s))<0){perror("write");fclose(fd);close(p[1]);exit(1);}
		printf("A->B %s\n ",s);
		strcpy(s,"");
	}

	exit(0);
	}
	//sumtem in B
	close(p[1]);
	int x=1,arr[100],i=0;
	printf("introduceti numere ");
	while (scanf("%d", &x) && x != 0) {
        arr[i++] = x;
    	}
	for(int j=0;j<i;j++)
	{
		char s[256]=""; char cuv[100]="";
		if(read(p[0],cuv,sizeof(cuv))<0){perror("read");close(p[0]);exit(1);}
		strcpy(s,cuv);
		//strcpy(cuv,0);
		int count=arr[i]-1,x;
		while(count>0){
			if((x=read(p[0],cuv,sizeof(cuv)))>0){
				cuv[x]='\0';
			strcat(s," ");
			strcat(s,cuv);
			strcpy(cuv,"");
			count--;
			}
			else {printf("p: %s\n",s);printf("nu mai sunt cuvinte");
				fclose(fd);close(p[1]);exit(1);}

		}
		printf("p: %s\n",s);
	}
	fclose(fd);
	close(p[0]);
	wait(0);
	return 0;
}
