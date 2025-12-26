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

int main(int argc, char *argv[])
{
	int id = msgget(MSG_KEY, 0);						// get the ID of the message queue

	struct msg_buf msg;									// create and fill the message buffer
	msg.type = getpid();

	printf("Username: ");							// read an integer
	scanf("%s", msg.data.sender);
	getchar();
	printf("To: ");                                          
        scanf("%s", msg.data.receiver);
	getchar();
	printf("message: ");                                         
        scanf("%s", msg.data.message);
	fgets(msg.data.message,200,stdin);
	msgsnd(
		id,
		&msg, sizeof(msg.data),
		IPC_NOWAIT);									// send the message
	printf("Sent: %ld\n", msg.type);
	return 0;
}
