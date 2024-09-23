#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include "common.h"

int main(int argc, char *argv[]) {
    int shmid, i, count = 0;
    char *data;
    key_t key;

    if((key = ftok(filename, id)) == -1) {
        perror("Error on ftok");
        exit(1);
    }

    if((shmid = shmget(key, SHM_SIZE, 0)) == -1) {
        perror("Error on getting shared mem");
        exit(1);
    }

    data = shmat(shmid, NULL, 0);
    if(data == (char *)(-1)) {
        perror("Error on attach");
        exit(1);
    }

    printf("%s\n", data);
    for(i = 0; i < strlen(data); i++) {
        if(strchr("aeiouAEIOU", data[i]) != NULL) {
            count++;
        }
    }
    printf("%d\n", count);

    if(shmdt(data) == -1) {
        perror("Error on detach");
        exit(1);
    } 

    return 0;
}
