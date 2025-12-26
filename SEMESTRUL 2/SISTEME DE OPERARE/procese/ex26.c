/*Scrieti un program C care primeste ca argument la linia de comanda 
un nume de fisier. Procesul principal creeaza un proces fiu. Procesul 
fiu va citi continutul fisierului specificat si va converti toate literele 
mici precedate de caracterul "." in caractere mari. Daca exista oricate 
spatii albe (spatii, taburi, linii noi, etc.) intre caracterul "." 
si urmatoarea litera mica, acea litera trebuie convertita in litera mare. 
Daca exista cel putin un caracter care nu este spatiu alb intre caracterul
 "." si urmatoarea litera mica, acea litera nu va fi modificata. 
Procesul fiu trimite prin pipe parintelui textul modificat.
Procesul parinte va afisa pe ecran tot ce primeste de la procesul fiu.*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define MAX_SIZE 100

int stubborn_read(int fd, void* buf, int count, int trials) {
  int k=0, total = 0, n = 0;
  while(total < count && n < trials && (k=read(fd, buf+total, count-total)) > 0) {
    total += k;
    n++;
  }
  return k < 0 ? k : total;
}

int stubborn_write(int fd, void* buf, int count, int trials) {
  int k=0, total = 0, n = 0;
  while(total < count && n < trials && (k=write(fd, buf+total, count-total)) > 0) {
    total += k;
    n++;
  }
  return k < 0 ? k : total;
}
int main(int argc, char* argv[])
{
	if(argc<2)
	{
		printf("prea putine argv\n");
		exit(1);
	}
	int p[2];
	pipe(p);
	int f=fork();
	if(f==-1)
	{
		perror("error fork()");
		close(p[0]);close(p[1]);
		exit(1);
	}else if(f==0)
	{
		//copil
		close(p[0]);
		int fd=open(argv[1],O_RDONLY);
		if(fd<0)
		{
			perror("error opening file");
			close(p[1]);
			exit(1);
		}
		int k;
		char* buf=malloc(MAX_SIZE);
		int transform=0;
		while((k=read(fd,buf,MAX_SIZE))>0)
		{
			for(int i=0;i<k;i++)
				if(buf[i]=='.')
					transform=1;
				else
					if(transform){
						if(islower(buf[i])){
							buf[i]+='A'-'a';
							transform=0;
						}else if(!islower(buf[i]) && !isspace(buf[i])){
							transform=0;
						}
					}
			if(stubborn_write(p[1],&k,sizeof(int),3)<0){
				perror("error writing 2");
				free(buf);
				close(p[1]);
				close(fd);
				exit(1);
			}
			if(stubborn_write(p[1],buf,k,3)<0){
				perror("error writing1");
				free(buf);
				close(p[1]);
				close(fd);
				exit(1);
			}
			memset(buf,0,MAX_SIZE);
		}
			int status=0;
			if(k<0){perror("error status");status=1;}
			if(stubborn_write(p[1],&k,sizeof(int),3)<0){
				perror("writing");
				close(p[1]);
				status=1;
			}
			free(buf);
			close(fd);
			close(p[1]);
			exit(status);
	}
		close(p[1]);
		int k,len=1;
		char* buf=malloc(MAX_SIZE);
		while(len>0){
			memset(buf,0,MAX_SIZE);
			if((k=stubborn_read(p[0],&len,sizeof(int),3))<0)
				{perror("size");len=0;
				}
			if((k=stubborn_read(p[0],buf,len,3))<0){
				perror("error read");len=0;
			}
			if(write(1,buf,sizeof(char)*k)<0)
				perror("error displaying");
		}
		free(buf);
		if(len<0)
			printf("child with error");
		close(p[0]);
		wait(0);
		return 0;
}
