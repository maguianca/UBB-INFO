/*Scrieti un program C numit A care creeaza 3 procese fiu numite B, 
C si D. A genereaza un numar aleator intre 10 si 20 si il trimite 
procesului D. Procesele B si C genereaza numere aleatoare intre 1 si 
200 si le trimit procesului D care calculeaza diferenta lor. 
Procesele se opresc cand diferenta absoluta dintre numerele generate 
de B si C este mai mica sau egala cu numarul generat de procesul A.*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<time.h>
#include<sys/types.h>
#include<unistd.h>
//A ->D  B,C ->D abs(B-c)< nr gen de A
int main(int argc,char**argv){
	int a2d[2],b2d[2],c2d[2],d2c[2],d2b[2];
	int r1=pipe(a2d),r2=pipe(b2d),r3=pipe(c2d),r4=pipe(d2c),r5=pipe(d2b);
	if(r1==-1||r2==-1||r3==-1||r4==-1||r5==-1){
		close(a2d[0]);close(a2d[1]);close(b2d[0]);close(b2d[1]);
		close(c2d[0]);close(c2d[1]);close(d2c[0]);close(d2c[1]);
		close(d2b[0]);close(d2b[1]);
		perror("error pipe()");exit(1);
	}
	int f1=fork();
	if(f1==-1){
		perror("error fork");exit(1);
	        close(a2d[0]);close(a2d[1]);close(b2d[0]);close(b2d[1]);
                close(c2d[0]);close(c2d[1]);close(d2c[0]);close(d2c[1]);
                close(d2b[0]);close(d2b[1]);
	}else if(f1==0)
	{
		//suntem in D
		int na,nb,nc,dif=0,found=0;
		close(a2d[1]);close(d2c[0]);close(d2b[0]);
		close(b2d[1]);close(c2d[1]);
		if(read(a2d[0],&na,sizeof(int))<0){perror("error a2d");}
		printf("[D] A: %d\n",na);
		while(!found)
		{
			if(read(c2d[0],&nc,sizeof(int))<0)perror("error c2d");
			printf("[D] C: %d\n",nc);
			if(read(b2d[0],&nb,sizeof(int))<0)perror("error b2d");
			printf("[D] B: %d\n",nb);
			if(nb<nc)
				dif=nc-nb;
			else
				dif=nb-nc;
			printf("[D] dif: %d\n",dif);
			if(dif<na){
				found=1;
				printf("[D] stop\n");
			}
			if(write(d2c[1],&found,sizeof(int))<0)perror("error");
			if(write(d2b[1],&found,sizeof(int))<0)perror("error d2b");
		}
		close(d2c[1]);close(a2d[0]);close(d2b[1]);
		close(c2d[0]);close(b2d[0]);
		exit(0);
	}
	 int f2=fork();
        if(f2==-1){
                perror("error fork");exit(1);
                close(a2d[0]);close(a2d[1]);close(b2d[0]);close(b2d[1]);
                close(c2d[0]);close(c2d[1]);close(d2c[0]);close(d2c[1]);
                close(d2b[0]);close(d2b[1]);
        }else if(f2==0){
                //suntem in B
		close(a2d[0]);close(a2d[1]);close(c2d[0]);
		close(c2d[1]);close(b2d[0]);close(d2b[1]);
		int nb,found=0;
		srandom(getpid());
		while(!found){
			nb=random()%201+1;
			if(write(b2d[1],&nb,sizeof(int))<0)perror("error b2d");
			 printf("B->D: %d\n",nb);
			if(read(d2b[0],&found,sizeof(int))<0)perror("error d2b");
		}
		close(b2d[1]);close(d2b[0]);
                exit(0);
        }
	  int f3=fork();
        if(f3==-1){
                perror("error fork");exit(1);
                close(a2d[0]);close(a2d[1]);close(b2d[0]);close(b2d[1]);
                close(c2d[0]);close(c2d[1]);close(d2c[0]);close(d2c[1]);
                close(d2b[0]);close(d2b[1]);
	}else if(f3==0){
                //suntem in C
		 close(a2d[0]);close(a2d[1]);close(b2d[0]);
                close(b2d[1]);close(c2d[0]);close(d2c[1]);
                int nc,found=0;
                srandom(time(0));
                while(!found){
                        nc=random()%201+1;
                        if(write(c2d[1],&nc,sizeof(int))<0)perror("error c2d");
			printf("C->D: %d\n",nc);
                        if(read(d2c[0],&found,sizeof(int))<0)perror("error d2c");
                }
                close(c2d[1]);close(d2c[0]);
                exit(0);
        }
	//suntem in A
	close(b2d[0]);close(b2d[1]);close(c2d[0]);close(c2d[1]);
	close(d2b[0]);close(d2b[1]);close(a2d[0]);
	int n;
	srandom(getppid());
	n=random()%11+10;
	if(write(a2d[1],&n,sizeof(int))<0) perror("error a2d");
	close(a2d[1]);
	printf("A->D: %d\n",n);
	wait(0);
	wait(0);
	wait(0);
	return 0;
}

