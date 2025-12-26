#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_THR 10
#define MAX_SIZE 100

int buffer[100];
int fd;
int flag = 0; // 0 - insemana ca bufferul ii gol
              // 1 - insemana ca bufferul ii plin
int sum = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* consume(void* arg){
        int id = *(int*)arg;
        free(arg);
        pthread_mutex_lock(&mtx);
        while (flag == 0){
                printf("\n[Thread comsumer %2d]: ", id);
                pthread_cond_wait(&cond, &mtx);
        }
        for (int i = 0; i < MAX_SIZE; i ++){
                sum += buffer[i];
        }
        flag = 0;

        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mtx);
        return NULL;
}

void* produce(void* arg){
        int id = *(int*)arg;
        free(arg);
        pthread_mutex_lock(&mtx);
        while (flag == 1){
                printf("\n[Thread producer %2d]: ", id);
                pthread_cond_wait(&cond, &mtx);
        }

        for (int i = 0; i < MAX_SIZE; i ++){
                read(fd, &buffer[i], 2);
        }
        flag = 1;

        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mtx);
        return NULL;
}

int main(int argc, char** argv){
        fd = open("file", O_RDONLY);

        pthread_t tc[MAX_THR];
        pthread_t tp[MAX_THR];

        for (int i = 0; i < MAX_THR; i ++){
                int* nrC = malloc(sizeof(int));
                *nrC = i;
                int* nrP = malloc(sizeof(int));
                *nrP = i;
                pthread_create(&tc[i], NULL, consume, nrC);
                pthread_create(&tp[i], NULL, produce, nrP);
        }

        for (int i = 0; i < MAX_THR; i ++){
                pthread_join(tp[i], NULL);
                pthread_join(tc[i], NULL);
        }

        printf("\nSuma: %d\n", sum);

        return 0;
}
