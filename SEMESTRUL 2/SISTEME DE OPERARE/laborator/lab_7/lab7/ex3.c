//3. Să se scrie un program C care creează un proces copil cu care comunică prin pipe.
//Procesul părinte citeşte de la tastatură un caracter c şi un şir s şi le trimite prin pipe procesului copil,
//iar procesul copil verifică şi afişează numărul de apariţii ale caracterului c în şirul s.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include<string.h>
int nr_aparitii(char c,char sir[50])
{
	int count=0;
	for(int i=0;i<strlen(sir);i++)
		if(sir[i]==c)
			count++;
	return count;
}

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
        close(pd[1]);
	while(1){
	char c='\0',sir[50]="\0";
        read(pd[0],&c,sizeof(char));
	printf("[in child] am citit caracter:%c\n",c);
	read(pd[0],&sir,sizeof(sir));
        printf("[in child] am citit %s\n",sir);
	 if(strcmp(sir,"stop")==0)
                break;
	printf("nr aparitii: %d\n",nr_aparitii(c,sir));
	}
        close(pd[0]);
        exit(0);
    }
    close(pd[0]);
    while(1){
    	char c,sir[50];
    	printf("introduceti un caracter: ");
    	scanf("%c",&c);
    	getchar();
	write(pd[1],&c,sizeof(char));
	sleep(1);
    	printf("introduceti sirul: ");
    	scanf("%s",sir);
	getchar();
    	write(pd[1],&sir,strlen(sir));
	if(strcmp(sir,"stop")==0)
		break;
	sleep(1);
    }
    close(pd[1]);
    int status;
    wait(&status);
    return 0;
}

