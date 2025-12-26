#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

struct data {
    int nr;
    int tries;
};
int getIdFromCookie() {
    char* cookie = getenv("HTTP_COOKIE");
    int id = -1;
    if (cookie != NULL) {
        char* ptr = strstr(cookie, "session_id=");
        if (ptr != NULL) {
            sscanf(ptr, "session_id=%d", &id);
        }
    }
    return id;
}
int isNewUser() {
    char* cookie = getenv("HTTP_COOKIE");
    return (cookie == NULL || strstr(cookie, "session_id=") == NULL);
}
int getNumberFromQueryString(int* nr_out) {
    char* qs = getenv("QUERY_STRING");
    if (qs == NULL) return 0;
    return sscanf(qs, "nr=%d", nr_out) == 1;
}

int init() {
    int r, id, code;
    char filename[100];
    struct data d;

    srand(GetCurrentProcessId());
    r = rand() % 100;

    do {
        id = rand();
        sprintf(filename, "temp/temp_%d.txt", id);
        code = _open(filename, _O_CREAT | _O_EXCL | _O_WRONLY, _S_IREAD | _S_IWRITE);
    } while (code < 0);

    d.nr = r;
    d.tries = 0;
    _write(code, &d, sizeof(d));
    _close(code);

    printf("Set-Cookie: session_id=%d; path=/\n", id);

    return id;
}

int getNumberFromFile(int id) {
    char filename[100];
    int fd;
    struct data d;

    sprintf(filename, "temp/temp_%d.txt", id);
    fd = _open(filename, _O_RDWR);
    if (fd < 0) return -1;

    _read(fd, &d, sizeof(d));
    d.tries++;
    _lseek(fd, 0, SEEK_SET);
    _write(fd, &d, sizeof(d));
    _close(fd);

    return d.nr;
}

int getNoOfTries(int id) {
    char filename[100];
    int fd;
    struct data d;

    sprintf(filename, "temp/temp_%d.txt", id);
    fd = _open(filename, _O_RDONLY);
    if (fd < 0) return -1;
    _read(fd, &d, sizeof(d));
    _close(fd);
    return d.tries;
}

void destroy(int id) {
    char filename[100];
    sprintf(filename, "temp/temp_%d.txt", id);
    remove(filename);
}

void printForm() {
    printf("<form action='play.cgi' method='get'>\n");
    printf("Nr: <input type='text' name='nr'><br>\n");
    printf("<input type='submit' value='Trimite'>\n");
    printf("</form>");
}


int main() {
    int id, status;
    int shouldPrintCookie = 0;
    int nr, nr2;

    if (isNewUser()) {
        id = init(); 
        shouldPrintCookie = 1;
        status = 0;
    } else {
        id = getIdFromCookie();

        printf("Content-type: text/html\n");
        if (!getNumberFromQueryString(&nr)) {
            status = 5; 
        } else {
            nr2 = getNumberFromFile(id);
            if (nr2 == -1) {
                id = init(); 
                shouldPrintCookie = 1;
                status = 0;
            } else if (nr == nr2)
                status = 2;
            else if (nr < nr2)
                status = 3;
            else
                status = 4;
        }
    }

    if (shouldPrintCookie) {
        printf("Content-type: text/html\n");
    }

    printf("\n\n<html>\n<body>\n");

    switch (status) {
        case 0:
            printf("Ati inceput un joc nou.<br>\n");
            printForm();
            break;
        case 2:
            printf("Ati ghicit din %d incercari!<br>", getNoOfTries(id));
            printf("Click <a href='play.cgi'>aici</a> pentru un joc nou!");
            destroy(id);
            break;
        case 3:
            printf("Prea mic!<br>\n");
            printForm();
            break;
        case 4:
            printf("Prea mare!<br>\n");
            printForm();
            break;
        case 5:
            printf("Nu ati introdus niciun numar!<br>\n");
            printForm();
            break;
    }

    printf("</body>\n</html>");
    return 0;
}
