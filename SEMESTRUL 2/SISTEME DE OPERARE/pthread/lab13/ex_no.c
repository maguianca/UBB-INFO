/*
	
	3. Se dau un fișier binar care conține 100.000 de numere aleatoare și un tablou care poate stoca doar 100 de numere.
	Să se determine suma primelor 1000 de numere întregi din acest fișier folosind 10 thread-uri (consumers threads).
	Citirea celor 1000 de numere intregi se va face, pe rând, în variabila buffer folosind alte 10 thread-uri (producers threads).
	
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_THR 10
#define MAX_SIZE 100

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int sum=0;
int flag = 0;   //0 buffer gol// 1 buffer plin

int buffer[MAX_SIZE];

void* consume(void* arg){
	int id=*(int*)arg;
	free(arg);
	
	pthread_mutex_lock(&mtx);
	while(flag==0){
		printf("[consumer %d] wait..\n",id);
		pthread_cond_wait(&empty, &mtx);
	}
	
	for(int i=0;i<MAX_SIZE;i++){
		sum+=buffer[i];
	}
	printf("[consumer %d] sum = %d\n", id, sum);
	
	flag=0;
	pthread_cond_broadcast(&full);  //semnaleaza la producers
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

void* produce(void*arg){
	int id=*(int*)arg;
	free(arg);
	
	int fd = open("file.bin", O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		int ret_val = 1;
		pthread_exit(&ret_val);
	}
	
	for (int i = 0; i < MAX_THR; i++)
	{
        pthread_mutex_lock(&mtx);
        while(flag==1){
			printf("[producer %d] wait ...\n", id);
			pthread_cond_wait(&full, &mtx);
		}
		
		printf("[producer %d] reading ...\n", id);
        for(int i=0; i < MAX_SIZE; i++)
			read(fd, &buffer[i], 2);
		printf("[producer %d] finished reading ...\n", id);
		
        flag=1;
        pthread_cond_broadcast(&empty); //semnaleaza la consumers
        pthread_mutex_unlock(&mtx);
	}
	
	close(fd);
	return NULL;
}


int main(int argc,char**argv)
{
	pthread_t tc[MAX_THR];
	for(int i = 0; i < MAX_THR; i++)
	{
		int *idc=malloc(sizeof(int));
		*idc=i;
		pthread_create(&tc[i],NULL,consume,idc);
	}
	
	pthread_t tp;
	int *idp=malloc(sizeof(int));
	*idp=0;
	pthread_create(&tp, NULL, produce, idp);
	
	for(int i=0;i<MAX_THR;i++)
		pthread_join(tc[i],NULL);
	pthread_join(tp,NULL);
	
	printf("SUMA: %d\n",sum);
	
	return 0;
}
