/*Scrieti un program C care creeaza doua procese fiu. 
Cele doua procese isi vor trimite alternativ numere intregi intre 1 si 10 (inclusiv) 
pana cand unul din ele trimite numarul 10. 
Afisati mesaje pe masura ce numerele sunt trimise.*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<time.h>
int main(int argc, char**argv){
	int a2b[2],b2a[2];
	int r1=pipe(a2b),r2=pipe(b2a);
	if(r1==-1||r2==-1){
		perror("eroare la pipe");
		exit(1);
	}
	int f=fork();
	if(f==-1){
		perror("eroare la fork");
		exit(1);
	}else if(f==0){
		//suntem in a
		close(a2b[0]);
		close(b2a[1]);
		int n;
		srandom(time(0)*getpid());
		if(read(b2a[0],&n,sizeof(int))<0){
			perror("eroare la cit b2a");
			exit(1);
		}
		printf("[copil a] am primit %d\n",n);
		while(n!=10)
		{
			n=random()%10+1;
			if(write(a2b[1],&n,sizeof(int))<0){
				perror("eroare la scriere a2b");
				exit(1);
			}
			printf("[copil a] am trimis %d\n",n);
			if(n==10)break;
			if(read(b2a[0],&n,sizeof(int))<0){
				perror("eroare la citore b2a");
				exit(1);
			}
			printf("[copil a] am primit %d\n",n);
		}
		close(a2b[1]);
		close(b2a[0]);
		exit(0);
	}
	f=fork();
	if(f==-1){
                perror("eroare la fork");
                exit(1);
        }else if(f==0){
                //suntem in b
                close(b2a[0]);
                close(a2b[1]);
                int n;
                srandom(time(0)*getppid());
                while(n!=10)
                {
                        n=random()%10+1;
                        if(write(b2a[1],&n,sizeof(int))<0){
                                perror("eroare la scriere b2a");
                                exit(1);
                        }
			printf("[copil b] am trimis %d\n",n);
                        if(n==10)break;
                        if(read(a2b[0],&n,sizeof(int))<0){
                                perror("eroare la citore a2b");
                                exit(1);
                        }
                        printf("[copil b] am citit %d\n",n);
                }
                close(b2a[1]);
                close(a2b[0]);
                exit(0);
        }
	//parinte
	wait(0);
	wait(0);
	return 0;
}
