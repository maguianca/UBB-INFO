#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define MAX_CUVINTE 100
#define MAX_CUVANT_SIZE 100

int main() {
    FILE *fd = fopen("fisier.txt", "r");
    if (fd == NULL) {
        perror("fopen");
        exit(1);
    }

    int p[2];
    if (pipe(p) == -1) {
        perror("error pipe");
        fclose(fd);
        exit(1);
    }

    int f = fork();
    if (f == -1) {
        perror("error fork");
        fclose(fd);
        close(p[0]);
        close(p[1]);
        exit(1);
    }

    if (f == 0) {
        // Suntem în procesul A (copil)
        close(p[0]);  // Închidem partea de citire a pipe-ului
        char s[MAX_CUVANT_SIZE];

        while (fscanf(fd, "%s", s)>0) {
            if (write(p[1], s, strlen(s) + 1) == -1) {  // +1 pentru terminatorul '\0'
                perror("write");
                close(p[1]);
                fclose(fd);
                exit(1);
            }
		printf("A->B %s\n",s);sleep(1);
        }

        close(p[1]);
        fclose(fd);
        exit(0);
    }

    // Suntem în procesul B (părinte)
    close(p[1]);  // Închidem partea de scriere a pipe-ului

    int arr[MAX_CUVINTE];
    int numere_index = 0;
    int num;

    printf("Introduceti numere, terminati cu 0:\n");
    while (scanf("%d", &num) && num != 0) {
        arr[numere_index++] = num;
    }

    for (int i = 0; i < numere_index; i++) {
        char propoziție[MAX_CUVANT_SIZE * MAX_CUVINTE] = "";  // Propoziție completă
        for (int j = 0; j < arr[i]; j++) {
            char cuv[MAX_CUVANT_SIZE];
            if (read(p[0], cuv, sizeof(cuv)) <= 0) {
                printf("Nu mai sunt suficiente cuvinte în pipe.\n");
                break;
            }

            if (strlen(propoziție) > 0) {
                strcat(propoziție, " ");  // Adaugă un spațiu între cuvinte
            }

            strcat(propoziție, cuv);
        }
        printf("Propozitie %d: %s\n", i + 1, propoziție);
    }

    close(p[0]);  // Închidem partea de citire a pipe-ului
    fclose(fd);   // Închidem fișierul
    wait(NULL);   // Așteptăm ca procesul copil să termine
    return 0;
}
