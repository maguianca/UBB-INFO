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
	int x=strlen(s);
        if(write(p[1],&x,sizeof(int))<0){perror("write");fclose(fd);close(p[1]);exit(1);}
        if(write(p[1],s,x*sizeof(char))<0){perror("write");fclose(fd);close(p[1]);exit(1);}
                printf("A->B %s\n ",s);
                strcpy(s,"");
        }
	int x=0;
	if(write(p[1],&x,sizeof(int))<0){perror("write");fclose(fd);close(p[1]);exit(1);}
	close(p[1]);
        exit(0);
        }
	//suntem in B
	close(p[1]);
	char cuvinte[100][100];
	int k=1;int i=0,x;
	while(1){
		if(read(p[0],&k,sizeof(int))<0){perror("read");fclose(fd);close(p[0]);exit(1);}
		if(k==0)break;
        	if(read(p[0],cuvinte[i++],k*sizeof(char))<0){perror("read");fclose(fd);close(p[0]);exit(1);}	
	}
	i=0;
	while(1){
		printf("introduceti numar: ");
		scanf("%d",&x);
		if(x==0)break;
		for(int j=0;j<x;j++)
			printf("%s ",cuvinte[i++]);
		printf("\n");
	}
	close(p[0]);
	fclose(fd);
	wait(0);
	return 0;
}
