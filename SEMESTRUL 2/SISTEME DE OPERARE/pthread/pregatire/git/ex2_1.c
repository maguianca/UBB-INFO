#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_WORDS 6
#define MAX_LEN 100

char cuvinte[MAX_WORDS][MAX_LEN] = {{0}};
int count[MAX_WORDS] = {0};
int ap[MAX_WORDS] = {0};
int MAX_THR;
char numere[MAX_WORDS][MAX_LEN] = {{0}};
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* do_work(void* argv) {
    int id = *(int*)argv;
    free(argv);

    pthread_mutex_lock(&mtx);
    for (int i = 0; i < MAX_WORDS; i++) {
        for (int j = 0; j < strlen(numere[id]); j++) {
            if (numere[id][j] == 'a' + i) {
                if (ap[i] == 0) {
                    strcat(cuvinte[i], numere[id]);
                    strcat(cuvinte[i], " ");
                    count[i]++;
                    ap[i]++;
                } else {
                    ap[i]++;
                }
            }
        }
    }
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "argv insuf\n");
        exit(1);
    }

    MAX_THR = argc - 1;
    for (int i = 1; i <= MAX_THR; i++) {
        strcpy(numere[i - 1], argv[i]);
    }

    for (int i = 0; i < MAX_THR; i++) {
        printf("%s\n", numere[i]);
    }

    pthread_t tid[MAX_THR];
    for (int i = 0; i < MAX_THR; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&tid[i], NULL, do_work, id);
    }

    for (int i = 0; i < MAX_THR; i++) {
        pthread_join(tid[i], NULL);
    }

    for (int i = 0; i < MAX_WORDS; i++) {
        printf("%c: aparitii %d, cuvinte %d => %s\n", 'A' + i, ap[i], count[i], cuvinte[i]);
    }

    return 0;
}
