/*Scrieti un program C (numit A) care creeaza un proces fiu B. 
Procesul B genereaza un numar aleator intre 100 si 1000. 
Procesul A genereaza cate un numar aleator intre 50 si 1050 si il 
trimite procesului B pana cand diferenta absoluta intre numarul generat 
de B si numarul trimis de A este mai mica decat 50. B afiseaza fiecare
numar primit de la A. A va afisa la final numarul de numere generate 
pana cand conditia de oprire este indeplinita.*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(int argc, char* argv[]){
	int p2c[2],c2p[2];
	int r1=pipe(p2c),r2=pipe(c2p);
	if(r1==-1||r2==-1){perror("error pipe()");exit(1);}
	int f=fork();
	if(f==-1){
		perror("error fork()");
		close(p2c[0]);close(p2c[1]);
		close(c2p[1]);close(c2p[0]);
		exit(1);
	}
	else if(f==0){
		close(c2p[0]);close(p2c[1]);
		int x,found=0,n;
		srandom(time(0));
		x=random()%901+100;
		printf("Procesul copil a generat %d\n",x);
		while(!found)
		{
			if(read(p2c[0],&n,sizeof(int))<0)
			{
				perror("error c2p");
				close(c2p[1]);close(p2c[0]);
				exit(1);
			}
			if(x<n)
				x=n-x;
			else 
				x=x-n;
			printf("Copil a primit %d; diferenta: %d\n",n,x);
			if(x<50)
				found=1;
			if(write(c2p[1],&found,sizeof(int))<0)
			 {
                                perror("error c2p");
                                close(c2p[1]);close(p2c[0]);
                                exit(1);
                        }
		}
	close(c2p[1]);close(p2c[0]);
	exit(0);
	}
	//parinte
	close(c2p[1]);close(p2c[0]);
	int n,count=0,found=0;
	srandom(time(0));
	while(!found){
	 n=random()%1001+50;
	if(write(p2c[1],&n,sizeof(int))<0)
	{	perror("error p2c");
		close(c2p[0]);close(p2c[1]);
		exit(1);
	}
	if(read(c2p[0],&found,sizeof(int))<0){
		perror("error c2p");
		close(c2p[0]);close(p2c[1]);
		exit(1);
	}
	count++;
	}
	close(p2c[1]);
	close(c2p[0]);
	wait(0);
	printf("Parintele a generat %d numere\n",count);
	return 0;
}
