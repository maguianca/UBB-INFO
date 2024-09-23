#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_THR 2

int N, numere[1000000];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t c2 = PTHREAD_COND_INITIALIZER;
int stop = 0, pos = 0; // 0-par 1-impar

void* f1(void* argv) {
    while (1) {
        int x = rand() % 1000;
        if (x % 2 == 1) x++;
        
        pthread_mutex_lock(&mtx);
        while (stop != 0) {
            pthread_cond_wait(&c1, &mtx);
        }
        if (pos >= N) {
            pthread_mutex_unlock(&mtx);
            break;
        }
        numere[pos] = x;
        pos++;
        stop = 1;
        pthread_cond_signal(&c2);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void* f2(void* argv) {
    while (1) {
        int x = rand() % 1000;
        if (x % 2 == 0) x++;
        
        pthread_mutex_lock(&mtx);
        while (stop != 1) {
            pthread_cond_wait(&c2, &mtx);
        }
        if (pos >= N) {
            pthread_mutex_unlock(&mtx);
            break;
        }
        numere[pos] = x;
        pos++;
        stop = 0;
        pthread_cond_signal(&c1);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    printf("Introduceti N:\n");
    scanf("%d", &N);
    
    pthread_t tid[MAX_THR];
    pthread_create(&tid[0], NULL, f1, NULL);
    pthread_create(&tid[1], NULL, f2, NULL);
    
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    
    for (int i = 0; i < N; i++) {
        printf("numere[%d]: %d\n", i, numere[i]);
    }
    return 0;
}
