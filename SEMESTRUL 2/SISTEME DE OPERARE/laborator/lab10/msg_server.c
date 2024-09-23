#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define MSG_KEY 0x7926d947

struct msg_data
{
        char sender[50];
        char receiver[50];
        char message[200];

};

struct msg_buf
{
        long type;
        struct msg_data data;
};
volatile int go =1;
int go = 1;	// execution flag

// Handle the SIGINT signal
void stop(int sig)
{
    go = 0;
}


int main(int argc, char *argv[])
{
	signal(SIGINT, stop);	//set the SIGINT signal handler											// set the SIGINT signal handler
	
	int id = msgget(MSG_KEY,0);// get the message queue id							// create the message queue

	struct msg_buf rbuf;													// create and fill the message to send
	rbuf.type = 0;//punem piduk nostru //citeste orice tip de mesaj
	//rbuf.data.sender;
	//rbuf.data.receiver;
	//rbuf.data.message;
	while (go)															// do until SIGINT
	{
		msgrcv(
			id,
			&rbuf, sizeof(rbuf.data), rbuf.type,
			MSG_NOERROR | IPC_NOWAIT);

		if (rbuf.type > 0)
		{
			printf("Received: PID: %ld message:%s\n", rbuf.type, rbuf.data.message);
			//struct msgbuf sbuf;					// create receive buffer
			//sbuf.type = rbuf.type;
			//sbuf.data.sender=rbuf.sender;
			//sbuf.data.receiver=rbuf.receiver;
			rbuf.type=0;

			//msgsnd(
			//	id,
			//	&sbuf, sizeof(sbuf.mtext),
			//	IPC_NOWAIT);
			//printf("Sent: %d\n", sbuf.mtext);

			//rbuf.mtext = 0;
		}

		sleep(2);
	}

	msgctl(id, IPC_RMID, NULL);											// destroy the message queue

	return 0;
}
