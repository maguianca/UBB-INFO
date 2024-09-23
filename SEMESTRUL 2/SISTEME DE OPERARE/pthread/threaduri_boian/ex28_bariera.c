//Scrieti un program C care citeste un numar n si creeaza un sir s de n numere aleatoare intre 0 si 1000. Dupa ce sirul este creat, 
//procesul principal creeaza n + 1 thread-uri. Fiecare din primele n thread-uri repeta urmatorii pasi pana cand sirul s este sortat ascendent:
//- genereaza 2 intregi aleatori intre 0 si n-1, numiti i si j
//- daca i < j si s[i] > s[j] interschimba s[i] si s[j]
//- daca i > j si s[i] < s[j] interschimba s[i] si s[j]
//Thread-ul n+1 asteapta pana cand sirul este sortat, dupa care il afiseaza. Folositi mecanisme de sincronizare 
//corespunzatoare.
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
int numere[20000],NR,MAX_THR;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int sortat()
{
	for(int i=0;i<NR-1;i++)
		if(numere[i+1]<numere[i])return 0;
	return 1;
}
void*do_work(void*argv)
{
	int id=*(int*)argv;
	free(argv);
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if(sortat()){pthread_cond_signal(&cond);break;}
		int i=rand()%NR;
		int j=rand()%NR;
		if(i<j && numere[i]>numere[j]||i>j && numere[i]<numere[j])
		{
			int aux=numere[i];
			numere[i]=numere[j];
			numere[j]=aux;
		}
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx);
	return NULL;
}
void*printer(void*argv){

	if(!sortat())pthread_cond_wait(&cond,&mtx);
	else
	{
		for(int i=0;i<NR;i++)
			printf("numere[%d]=%d\n",i,numere[i]);

	}
	return NULL;
}

int main(int argc,char**argv)
{
	srand(time(NULL));
	printf("introduceti n\n");\
	scanf("%d",&NR);
	for(int i=0;i<NR;i++)
		numere[i]=rand()%1001;
	MAX_THR=NR+1;
	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR-1;i++)
	{
		int *id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);

	}
	pthread_create(&tid[MAX_THR-1],NULL,printer,NULL);
	for(int i=0;i<MAX_THR;i++)
		pthread_join(tid[i],NULL);
	return 0;
}
