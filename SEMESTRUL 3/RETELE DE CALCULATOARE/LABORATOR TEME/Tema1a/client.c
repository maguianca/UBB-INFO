#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
int main() {
  int c;
  struct sockaddr_in server;
  uint16_t a;
  uint32_t suma;
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socket-ului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  printf("Introduceti numerele pozitive pe rand.Atunci cand terminati de trimis toate numerele apasati 0\n");
  a=-1;
  int i=0;
  while(a!=0){
  	printf("a[%d] = ",i);
	i++;
  	scanf("%hu", &a);
  	a = htons(a);
  	send(c, &a, sizeof(a), 0);
  }
  recv(c, &suma, sizeof(suma), MSG_WAITALL);
  suma = ntohs(suma);
  printf("Suma este %hu\n", suma);
  
close(c);
}
