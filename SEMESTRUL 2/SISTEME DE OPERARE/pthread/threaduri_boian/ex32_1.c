#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define MAX_NUM 100000
#define MAX_THR 10

char buffer[MAX_NUM];
int NR;
FILE *fd;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

void *do_work(void *argv) {
    int size = 0;
    char *buf_loc = malloc(sizeof(char) * 100);
    buf_loc[0] = '\0'; // Initialize the buffer

    while (1) {
        pthread_barrier_wait(&barr); // Synchronize at the start of each iteration
        pthread_mutex_lock(&mtx);
        int rep = rand() % 3 + 1;
        char w[21];
        int read_success = 0;

        for (int i = 0; i < rep; i++) {
            if (fscanf(fd, "%20s", w) != 1) {
                pthread_mutex_unlock(&mtx);
                pthread_barrier_wait(&barr); // Synchronize at the end if EOF or error
                free(buf_loc);
                return NULL;
            }
            read_success = 1;
            int word_len = strlen(w);
            buf_loc = realloc(buf_loc, size + word_len + 2); // Ensure enough space
            sprintf(buf_loc + size, "%s ", w);
            size += word_len + 1; // Including the space
        }

        pthread_mutex_unlock(&mtx);
        if (!read_success) {
            break; // Exit the loop if nothing was read
        }
        pthread_barrier_wait(&barr); // Synchronize at the end of each iteration
    }

    buf_loc[size] = '\0';
    return buf_loc;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <num_threads> <filename>\n", argv[0]);
        exit(1);
    }

    NR = atoi(argv[1]);
    fd = fopen(argv[2], "r");
    if (fd == NULL) {
        perror("Error opening file");
        exit(1);
    }

    printf("Number of threads: %d, Filename: %s\n", NR, argv[2]);

    pthread_t tid[NR];
    pthread_barrier_init(&barr, NULL, NR);

    for (int i = 0; i < NR; i++) {
        if (pthread_create(&tid[i], NULL, do_work, NULL) != 0) {
            perror("Error creating thread");
        }
    }

    for (int i = 0; i < NR; i++) {
        char *result;
        if (pthread_join(tid[i], (void **) &result) == 0) {
            if (result != NULL) {
                printf("Thread %d: %s\n", i, result);
                free(result);
            }
        } else {
            perror("Error joining thread");
        }
    }

    fclose(fd);
    pthread_barrier_destroy(&barr);

    return 0;
}
