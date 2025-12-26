#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<string.h>
#include<stdlib.h>

int main(){
	int s,c,l;
	struct sockaddr_in server,client;
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s<0){
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}
	memset(&server,0,sizeof(server));
	server.sin_port=htons(1234);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	if(bind(s,(struct sockaddr *)&server,sizeof(server))<0){
		printf("Eroare la bind\n");
		return 1;
	}
	listen(s,5);
	l=sizeof(client);
	memset(&client,0,l);
	while(1){
		uint16_t a;
		uint32_t suma;
		c=accept(s,(struct sockaddr*)&client,&l);
		printf("S-a conectat serverul\n");
		a=-1;
		suma=0;
		int i=0;
		while(a!=0){ 
			recv(c,&a,sizeof(a),MSG_WAITALL);
			a=ntohs(a);
			printf("a[%d]= %hu\n",i,a);
			i++;
			suma+=a;
		}
		printf("Sending... %hu\n",suma);
		suma=htons(suma);
		send(c,&suma,sizeof(suma),0);
		close(c);
	}
}
