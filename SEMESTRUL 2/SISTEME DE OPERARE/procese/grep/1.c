#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Deschide fișierul b.txt pentru scriere (crează-l dacă nu există, sau trunchiază-l dacă există)
    int fd = open("b.txt", O_RDONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Redirecționează ieșirea standard către fișierul b.txt
    if (dup2(fd, 0) < 0) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Închide descriptorul de fișier original deoarece nu mai este necesar
    close(fd);

    // Execută comanda cat pentru a suprascrie conținutul fișierului b.txt cu cel din a.txt
    execlp("cat","cat", NULL);

    // Dacă exec eșuează
    perror("execlp");
    exit(EXIT_FAILURE);
}

