#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int pipe1[2]; // Pipe pentru comunicare părinte-copil
    int pipe2[2]; // Pipe pentru comunicare copil-părinte
    
    // Crearea pipe-urilor
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe() error: ");
        exit(EXIT_FAILURE);
    }

    int pid = fork(); // Fork pentru a crea procesul copil
    
    if (pid == -1) { // Eroare la fork()
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Procesul copil
        // Închideți capetele inutile ale pipe-urilor
        close(pipe1[1]); // Copilul nu scrie în pipe1
        close(pipe2[0]); // Copilul nu citește din pipe2

        int nums[2]; // Pentru a citi cele două numere
        read(pipe1[0], nums, sizeof(nums)); // Citire din pipe1

        // Calculați suma și scrieți în pipe2
        int sum = nums[0] + nums[1];
        write(pipe2[1], &sum, sizeof(int));

        // Închideți capetele pipe-urilor
        close(pipe1[0]);
        close(pipe2[1]);

        exit(0);
    } else { // Procesul părinte
        // Închideți capetele inutile ale pipe-urilor
        close(pipe1[0]); // Părintele nu citește din pipe1
        close(pipe2[1]); // Părintele nu scrie în pipe2

        // Citire din fișier
        FILE *file = fopen("input.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        int nums[2];
        fscanf(file, "%d %d", &nums[0], &nums[1]); // Citește două numere
        fclose(file);

        // Trimiteți numerele la copil
        write(pipe1[1], nums, sizeof(nums));
        close(pipe1[1]); // Închideți pipe-ul după scriere

        // Citiți suma din copil
        int sum;
        read(pipe2[0], &sum, sizeof(sum)); // Citește suma din pipe2

        printf("Sum: %d\n", sum); // Afișați suma

        // Închideți capetele pipe-urilor
        close(pipe2[0]);

        int status;
        wait(&status); // Așteptați ca procesul copil să se încheie
    }

    return 0;
}
