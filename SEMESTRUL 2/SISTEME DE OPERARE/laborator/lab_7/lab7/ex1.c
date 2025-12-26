//1. Să se scrie un program C care creează un proces copil cu care comunică prin pipe.
//Procesul părinte citeşte de la tastatură un număr natural şi îl trimite prin pipe procesului copil,
//iar procesul copil verifică şi afişează dacă acest număr este par sau impar.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int pd[2];
    int res = pipe(pd);
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
	int n;
	close(pd[1]);
	read(pd[0],&n,sizeof(int));
	close(pd[0]);
	if(n%2==1)
		printf("[in child] numarul %d este impar\n",n);	
	else
		printf("[in child] numarul %d este par\n",n);

	exit(0);
    }
    //suntem in parinte
    int n;
    close(pd[0]);
    printf("introduceti un numar: ");
    scanf("%d",&n);
    write(pd[1],&n,sizeof(int));
    close(pd[1]);
    int status;
    wait(&status);
    return 0;
}
