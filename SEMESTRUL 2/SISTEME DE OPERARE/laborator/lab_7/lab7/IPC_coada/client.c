#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define QUEUE_KEY 12345

struct message {
    long mtype;  // Tipul mesajului
    int value;   // Valoarea de trimis la server
};

int main() {
    int msgid = msgget(QUEUE_KEY, 0666);  // Obține coada de mesaje
    if (msgid == -1) {
        perror("Error accessing message queue");
        return 1;
    }

    struct message msg;
    msg.mtype = 1;  // Tipul mesajului trimis către server
    printf("Introduceți un număr întreg: ");
    scanf("%d", &msg.value);

    if (msgsnd(msgid, &msg, sizeof(int), 0) == -1) {
        perror("Error sending message");
        return 1;
    }

    printf("Client a trimis: %d\n", msg.value);

    // Așteaptă răspunsul de la server
    if (msgrcv(msgid, &msg, sizeof(int), 2, 0) == -1) {
        perror("Error receiving message");
        return 1;
    }

    printf("Client a primit: %d\n", msg.value);

    return 0;
}
