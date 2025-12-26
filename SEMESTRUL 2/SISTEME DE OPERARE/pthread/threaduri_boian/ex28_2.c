#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_NUM 100000

int NR, numere[MAX_NUM];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

int is_sorted() {
    for (int i = 0; i < NR - 1; i++) {
        if (numere[i] > numere[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void* do_work(void* argv) {
    while (1) {
        pthread_mutex_lock(&mtx);
        if (is_sorted()) {
            pthread_mutex_unlock(&mtx);
            break;
        }
        pthread_mutex_unlock(&mtx);

        int i = rand() % NR;
        int j = rand() % NR;

        pthread_mutex_lock(&mtx);
        if (i < j && numere[i] > numere[j]) {
            int aux = numere[i];
            numere[i] = numere[j];
            numere[j] = aux;
        } else if (i > j && numere[i] < numere[j]) {
            int aux = numere[i];
            numere[i] = numere[j];
            numere[j] = aux;
        }
        pthread_mutex_unlock(&mtx);
    }
    pthread_barrier_wait(&barr);
    return NULL;
}

void* print(void* argv) {
    pthread_barrier_wait(&barr);
    for (int i = 0; i < NR; i++) {
        printf("numere[%d] = %d\n", i, numere[i]);
    }
    return NULL;
}

int main(int argc, char** argv) {
    printf("Introduceti un nr n\n");
    scanf("%d", &NR);

    srand(time(NULL));
    for (int i = 0; i < NR; i++) {
        numere[i] = rand() % 1001;
    }

    pthread_t tid[NR], printer;
    pthread_barrier_init(&barr, NULL, NR + 1);

    for (int i = 0; i < NR; i++) {
        pthread_create(&tid[i], NULL, do_work, NULL);
    }
    pthread_create(&printer, NULL, print, NULL);

    for (int i = 0; i < NR; i++) {
        pthread_join(tid[i], NULL);
    }
    pthread_join(printer, NULL);

    pthread_barrier_destroy(&barr);
    return 0;
}
