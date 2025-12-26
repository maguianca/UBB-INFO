/*Scrieti un program C care genereaza N numere intregi aleatoate (N dat la linia de comanda). Apoi creeaza un proces fiu si ii trimite 
numerele prin pipe.Procesul fiu calculeaza media numerelor 
si trimite rezultatul inapoi parintelui.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
int main(int argc,char** argv){
	if(argc!=2){
		printf("se da exact un argument");
		exit(1);
	}
	int pc[2],cp[2];
	int r1=pipe(pc),r2=pipe(cp);
	if(r1==-1||r2==-1){
		perror("error on pipe");
		exit(1);
	}
	int f=fork();
	if(f==-1){
		perror("error on fork");
		exit(1);
	}
	else
	if(f==0){
		close(pc[1]);
		close(cp[0]);
		int n=0,i,nr;
		float rez=0;
		if(read(pc[0],&n,sizeof(int))<0)
		{
			perror("eroare la citire");
			close(pc[0]);
			close(cp[1]);
			exit(1);
		}
		for(i=0;i<n;i++){
			if(read(pc[0],&nr,sizeof(int))<0){
		        perror("eroare la citire");
                        close(pc[0]);
                        close(cp[1]);
                        exit(1);
			}
			rez=rez+nr;
		}
		rez=rez/n;
		if(write(cp[1],&rez,sizeof(float))<0){
			 perror("eroare la scriere");
                        close(pc[0]);
                        close(cp[1]);
                        exit(1);
		}
		 close(pc[0]);
                 close(cp[1]);
                 exit(1);
	}
	else{
		close(pc[0]);
		close(cp[1]);
		int n=atoi(argv[1]);
		int i,nr;
		float rez=-1;
		srandom(time(0));
		if(write(pc[1],&n,sizeof(int))<0){
			close(pc[1]);
			close(cp[0]);
			wait(0);
			exit(1);
		}
		for(i =0;i<n;i++)
		{
			nr=random()%100;
			printf("[parent] nr generat:%d\n",nr);
			if(write(pc[1],&nr,sizeof(int))<0){
				perror("eroare la trimitere la copil");
				close(pc[1]);
				close(cp[0]);
			}
		}
		wait(0);
		if(read(cp[0],&rez,sizeof(float))<0){
			perror("eroare la citire rez");
		}
		printf("media este %f\n",rez);
                 close(pc[1]);
                 close(cp[0]);
	}
	return 0;
}
