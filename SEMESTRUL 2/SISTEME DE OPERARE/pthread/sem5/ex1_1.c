#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_THR 100
#define NUM_COUNT 100000
#define NUM_PER_THREAD (NUM_COUNT / MAX_THR)

int sum = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *f(void *a) {
    int k = *(int *)a;
    free(a);

    int local_sum = 0;
    int fd = open("random.bin", O_RDONLY);
    if (fd < 0) {
        perror("open()");
        pthread_exit(NULL);
    }

    // Each thread reads its own segment of the file
    off_t offset = k * NUM_PER_THREAD * sizeof(int);
    if (lseek(fd, offset, SEEK_SET) == (off_t)-1) {
        perror("lseek()");
        close(fd);
        pthread_exit(NULL);
    }

    printf("[Thread %d] Starting...\n", k);
    int number;
    for (int i = 0; i < NUM_PER_THREAD; ++i) {
        if (read(fd, &number, sizeof(int)) != sizeof(int)) {
            perror("read()");
            close(fd);
            pthread_exit(NULL);
        }
        local_sum += number;
    }

    close(fd);

    pthread_mutex_lock(&mtx);
    sum += local_sum;
    pthread_mutex_unlock(&mtx);

    printf("[Thread %d] Finished with local sum: %d\n", k, local_sum);
    return NULL;
}

int main() {
    pthread_t th[MAX_THR];

    for (int i = 0; i < MAX_THR; ++i) {
        int *k = (int *)malloc(sizeof(int));
        *k = i;
        pthread_create(&th[i], NULL, f, k);
    }

    for (int i = 0; i < MAX_THR; ++i) {
        pthread_join(th[i], NULL);
    }

    printf("Total Sum: %d\n", sum);
    return 0;
}
