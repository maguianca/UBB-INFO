#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<signal.h>
#define QUEUE_KEY 12345
#define MSG_SIZE 128
struct message{
	long mtype;
	int value;
};
volatile int running=1;
void handler(int sig){
	running=0;
}
int main()
{
	signal(SIGINT, handler);
	int msgid=msgget(QUEUE_KEY,0666|IPC_CREAT);
	if(msgid==-1){
		perror("error creating");exit(1);}
	struct message msg;
	while(running)
	{
		if(msgrcv(msgid,&msg,sizeof(int),1,0)==-1){
			if(running){
			perror("error receiving message");}
			continue;
		}
		printf("Serverul a primit %d\n", msg.value);
		msg.mtype=2;
		msg.value*=2;
		if(msgsnd(msgid,&msg,sizeof(int),0)==-1){
			perror("error sending");}
		else{
			printf("serverul a trimie %d\n",msg.value);
		}
	}
	msgctl(msgid, IPC_RMID, NULL);  // Distruge coada de mesaje
        printf("Serverul s-a închis și coada de mesaje a fost distrusă.\n");

	return 0;
}

