//Scrieti un program C care primeste un numar N ca argument la linia de comanda. Programul cree>//numere aleatoare intre 0 si 111111 (inclusiv) pana cand un thread va genera un numar divizibi>//numerele generate, iar ultimul numar afisat trebuie sa fie cel divizibil cu 1001.
//Niciun thread nu va incepe sa genereze numere pana cand toate celelalte thread-uri au fost cr>//Nu se vor folosi variabile globale.
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
typedef struct{
	int*stop;
	pthread_barrier_t *bar;
	pthread_mutex_t *mtx;
}data;
void* do_work(void*argv)
{
	data td=*((data*)argv);
	pthread_barrier_wait(td.bar);
        while(1)
        {
                pthread_mutex_lock(td.mtx);
                if(*(td.stop)==0){
                        int n=rand()%111112;
                        printf("%d\n",n);
                        if(n%1001==0){
                                *(td.stop)=1;
                                break;
                        }
                }
                else{
                        break;
                }
                pthread_mutex_unlock(td.mtx);

        }
        pthread_mutex_unlock(td.mtx);
        return NULL;
}
int main(int argc,char*argv[])
{
        if(argc!=2){printf("nr argv insuficiente");exit(1);}
        int n=atoi(argv[1]);
        srand(time(NULL));
	int *flag=malloc(sizeof(int));
	pthread_barrier_t *bariera=malloc(sizeof(pthread_barrier_t));
	pthread_mutex_t *mutex=malloc(sizeof(pthread_mutex_t));
        pthread_t tid[n];
	data* args=malloc(n*sizeof(data));
        pthread_barrier_init(bariera,NULL,n);
	pthread_mutex_init(mutex,NULL);
        for(int i=0;i<n;i++)
        {
		args[i].stop=flag;
		args[i].bar=bariera;
		args[i].mtx=mutex;
                pthread_create(&tid[i],NULL,do_work,&args[i]);
        }
         for(int i=0;i<n;i++)
        {
                pthread_join(tid[i],NULL);
        }
        pthread_barrier_destroy(bariera);
	pthread_mutex_destroy(mutex);
	free(args);
	free(flag);
	free(mutex);
	free(bariera);
        return 0;
}
