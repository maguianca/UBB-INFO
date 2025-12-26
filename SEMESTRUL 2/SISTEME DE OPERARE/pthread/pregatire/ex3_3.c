#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<time.h>
#define MAX_THR 100
#define MAX_NUM 800000

int NR, numere[MAX_NUM], min = INT_MAX, medie, suma = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;
int frecventa[101] = {0};  // Ajustăm dimensiunea pentru a include 100

void* doWork(void* argv) {
    int id = *(int*)argv;
    free(argv);
    int st = id * NR / MAX_THR;
    int dr = st+NR / MAX_THR;  // Corectăm limita superioară

    for (int i = st; i < dr; i++) {
        if (numere[i] <= 100 && numere[i] % 2 == 0) {
            pthread_mutex_lock(&mtx);
            frecventa[numere[i]]++;
            pthread_mutex_unlock(&mtx);
        }
    }

    pthread_barrier_wait(&bar);

    if (id == 0) {
        pthread_mutex_lock(&mtx);
        for (int i = 2; i <= 100; i += 2) {
            suma += frecventa[i];
        }
        medie = suma / 50;
        for (int i = 2; i <= 100; i += 2) {
            if (abs(frecventa[i] - medie) < min) {
                min = abs(frecventa[i] - medie);
            }
        }
        pthread_mutex_unlock(&mtx);
    }

    pthread_barrier_wait(&bar);

    if (id == 0) {
        pthread_mutex_lock(&mtx);
        for (int i = 2; i <= 100; i += 2) {
            if (abs(frecventa[i] - medie) == min) {
                printf("%d are frecventa %d\n", i, frecventa[i]);
            }
        }
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int fd = open("random.c", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("introduceti n:\n");
    scanf("%d", &NR);
    printf("%d\n",NR);
    for (int i = 0; i < NR; i++) {
        if (read(fd, &numere[i], sizeof(int))<0) {
            perror("error");
            close(fd);
            exit(1);
        }
	printf("am citit %d\n",numere[i]);
	//numere[i]=rand()%100;
    }
    //close(fd);

    pthread_t tid[MAX_THR];
    pthread_barrier_init(&bar, NULL, MAX_THR);

    for (int i = 0; i < MAX_THR; i++) {
        int* p = (int*)malloc(sizeof(int));
        *p = i;
        pthread_create(&tid[i], NULL, doWork, p);
    }

    for (int i = 0; i < MAX_THR; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_barrier_destroy(&bar);
    for(int i=2;i<NR;i+=2)
	printf("frecventa %d=%d\n",i,frecventa[i]);
    return 0;
}
