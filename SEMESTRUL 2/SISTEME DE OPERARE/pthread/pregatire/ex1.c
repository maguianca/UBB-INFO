//se va citi de la tastatura un nr n si se va citi n numere pe 1 octet
//din fisierul binar  si se vor stoca intr o variabila globala
//se va crea un numar potrivit de threaduri
//va determina nr de apariti a2,a3,a5,..a97 ale fiecarui nr nr intreg 
//prim din intervalul 0..100
//va calcula m=media aritmetica
//va determina si va afisa toate numerele prime al caror nr de aparitii
//este cel mai apropiat de media aritmetica calculata anterior
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<limits.h>
#define MAX_THR 100
#define MAX_NUM 100000
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;
int buffer[MAX_NUM],NR;
int frecv[100],dif=0,suma,count,dif,medie,min=INT_MAX,max;
int is_prim(int x)
{
	if(x>97)
		return 0;
	if(x<2)return 0;
	if(x%2==0 && x!=2)return 0;
	for(int d=3;d*d<=x;d+=2)
	{	if(x%d==0)
		{return 0;}
	}
	return 1;
}
void* dowork(void*arg){
	int id=*(int*)arg;
	int lsuma,lcount;
	free(arg);
	int st=id*(NR/MAX_THR);
	int dr=st+(NR/MAX_THR);
	for(int i=st;i<dr;i++)
		if(is_prim(buffer[i]))
		{
			printf("[thread %d] %d prim\n",id,buffer[i]);
			pthread_mutex_lock(&mtx);
			frecv[buffer[i]]++;
			suma+=buffer[i];
			lsuma+=buffer[i];
			lcount++;
			count++;
			pthread_mutex_unlock(&mtx);
		}
	pthread_barrier_wait(&bar);
	medie=suma/count;
	//for(int i=2;i<=97;i++)
	//{
	//	if(frecv[i]>0)
	//	{
	//		suma+=frecv[i]*i;
	//		count+=frecv[i];
	//	}

	//}
	//medie=suma/count;
	printf("[thread %d] medie %d  suma %d \n",id,medie,lsuma);
	return NULL;
}
int main(int argc,char*argv[])
{
	srandom(time(NULL));
	printf("Introduceti n:\n");
	scanf("%d",&NR);
	for(int i=0;i<NR;i++)
		buffer[i]=rand()%100;
	pthread_t tid[MAX_THR];
	pthread_barrier_init(&bar,NULL,MAX_THR);
	for(int i=0;i<MAX_THR;i++)
	{
		int*p=malloc(sizeof(int));
		*p=i;
		pthread_create(&tid[i],NULL,dowork,p);
	}
	for(int i=0;i<MAX_THR;i++)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_barrier_destroy(&bar);
	for(int i=2;i<=97;i++)
        {
		if(is_prim(i)){
              	if(abs(frecv[i]-medie)<min)
			min=abs(frecv[i]-medie);
		 printf("frecv[%d]==%d \n",i,frecv[i]);}
        }
	max=abs(medie-min);
	min=medie+min;
	 for(int i=2;i<=97;i++)
        {
                if(frecv[i]==min||frecv[i]==max)
                        printf("%d apare de %d ori\n",i,frecv[i]);
        }
	pthread_barrier_destroy(&bar);
	return 0;
}
