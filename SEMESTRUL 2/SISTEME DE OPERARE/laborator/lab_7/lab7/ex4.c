//4. Să se scrie un program C care creează un proces copil cu care comunică prin pipe.
//Procesul părinte citeşte de la tastatură două numere întregi pe care le trimite prin pipe procesului copil,
//iar procesul copil returnează prin pipe suma lor.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char**argv){
	int pd[2];
	int res=pipe(pd);
	if (res == -1) {
        	perror("pipe() error: ");
        	exit(EXIT_FAILURE);
    	}
    	int pid = fork();
    	if (pid == -1) { // fork() failed
        	perror("fork() error: ");
        	exit(EXIT_FAILURE);
    	}
	if(pid==0){
		int n[2];
		read(pd[0],&n,sizeof(n));
		int sum=n[0]+n[1];
		close(pd[0]);
		write(pd[1],&sum,sizeof(int));
		close(pd[1]);
		exit(0);
	}
	else{
		int n[2];
		printf("introduceti primul numar: ");
		scanf("%d",&n[0]);
		printf("introduceti al doilea numar: ");
		scanf("%d",&n[1]);
		write(pd[1],&n,sizeof(n));
		close(pd[1]);
		//int status;
		//wait(&status);
		int sum;
		read(pd[0],&sum,sizeof(int));
		close(pd[0]);
		printf("suma: %d\n",sum);
		 int status;
                wait(&status);
	}
	return 0;
}
