/*Creati doua procese A si B. A genereaza un numar aleator 
intre 50 si 200. Daca este par, il trimite procesului B, daca nu, il 
incrementeaza si apoi il trimite procesului B. B imparte numarul la 2 
si il trimite inapoi procesului A. Procesele repeta pana cand m este 
mai mic decat 5. Procesele vor afisa valoarea lui n la fiecare step.*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc,char**argv){
	int p2c[2],c2p[2];
	int r1=pipe(p2c),r2=pipe(c2p);
	if(r1==-1){perror("error pipe");exit(1);}
        if(r2==-1){perror("error pipe");exit(1);}
	int f=fork();
	if(f==-1){perror("error fork");exit(1);}
	else if(f==0){
		close(p2c[1]);
		close(c2p[0]);
		int n;
		while(1){
			if(read(p2c[0],&n,sizeof(int))<0){perror("error citire p2c");}
			printf("[copil] a primit %d\n",n);
			n=n/2;
			printf("[copil] a trimis %d\n",n);
			if(write(c2p[1],&n,sizeof(int))<0){perror("error trimitere c2p");}
			if(n<5) break;
		}
		close(p2c[0]);
		close(c2p[1]);
		exit(0);
		}
		else{
			close(p2c[0]);
			close(c2p[1]);
			srandom(time(0));
			int n=random()%151+50;
			printf("[parinte] a generat %d\n",n);
			while(n>=5){
				if(n%2==1)
					n++;
				printf("[parinte] a trimis %d\n",n);
				 if(write(p2c[1],&n,sizeof(int))<0){perror("error trimitere p2c");}
				 if(read(c2p[0],&n,sizeof(int))<0){perror("error la primire c2p");}
				 printf("[parinte] a primit %d\n",n);
			}
			wait(0);
			close(p2c[1]);
			close(c2p[0]);
	}
	return 0;
}
