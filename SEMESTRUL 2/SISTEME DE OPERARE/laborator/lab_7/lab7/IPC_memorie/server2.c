/* Create two processes A and B. A creates a shared memory segment.
 * A then keeps reading strings from the standard input and places
 * whatever it reads in the shared memory segment(replacing previous
 * data). Process B, on each run, reads the data from the shared
 * memory segment and counts the number of vowels. Process A, upon
 * receiving a SIGINT, deletes the shared memory segment.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include "common.h"

int shmid = 0;
char *data = (char *)(-1);

void handler(int sig) {
    if(data != (char *)(-1)) {
        if(shmdt(data) == -1) {
            perror("Error on detach");
            exit(1);
        }
    }

    if(shmid > 0) {
        if(shmctl(shmid, IPC_RMID, 0) == -1) {
            perror("Error on remove shm");
        }
    }

    exit(0);
}

int main(int argc, char *argv[]) {
    key_t key;
    int k;
    char buf[100];
    
    signal(SIGINT, handler);

    if((key = ftok(filename, id)) == -1) {
        perror("Error on ftok");
        exit(1);
    }
    
    if((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0644)) == -1) {
        perror("Error on getting shared mem");
        exit(1);
    }

    data = shmat(shmid, NULL, 0);
    if(data == (char *)(-1)) {
        perror("Error on attach");
        exit(1);
    }

    while(1) {
        if((k = read(0, buf, 100*sizeof(char))) < 0) {
            perror("Error on reading");
        }
        buf[k-1] = 0;
        strcpy(data, buf);
    }
    
    return 0;
}
