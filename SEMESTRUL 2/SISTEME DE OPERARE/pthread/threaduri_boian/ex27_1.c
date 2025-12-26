//ex 27 horea muresan

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<string.h>

#define SIZE 128

int pos;
int count;
char buffer[SIZE+1];

pthread_cond_t cg = PTHREAD_COND_INITIALIZER;
pthread_cond_t cp = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


void* generate(void* arg){
        while(1){
                char ch='a'+rand()%('z'-'a'+1);

                pthread_mutex_lock(&mtx);
                if(pos==SIZE){
                        pthread_cond_signal(&cp);
                        while(pos==SIZE)
                                pthread_cond_wait(&cg,&mtx);
                }

                if(count==0)
                        break;

                buffer[pos]=ch;
                pos++;
                pthread_mutex_unlock(&mtx);
        }
        //pt cazul in care count =0 si se iese din while, ne asiguram ca se face unlock
        pthread_mutex_unlock(&mtx);
        return NULL;
}

void* print(void* arg){
        while(1){

                pthread_mutex_lock(&mtx);
                if(pos!=SIZE){
                        pthread_cond_broadcast(&cp);
                        while(pos!=SIZE)
                                pthread_cond_wait(&cp,&mtx);
                }

                //afisez sirul de caractere
                printf("%s\n",buffer);

                //reinitializez buffer ul ca sa pot afisa tot altceva
                memset(buffer,0,SIZE*sizeof(char));

                pos=0;
                count--;

                pthread_cond_broadcast(&cg);

                if(count==0)
                        break;//am generat toate cele m siruri
                pthread_mutex_unlock(&mtx);
        }
                pthread_mutex_unlock(&mtx);
        return NULL;
}


//exemplu rulare: ./ex27 n m
int main(int argc,char* argv[]){

        //verif nr arg
        if(argc!=3){
                printf("Prea putine arg!\n");
                exit(EXIT_FAILURE);
        }

        //obtin n si m
        int n=atoi(argv[1]);
        int m=atoi(argv[2]);

        //init var globale
        pos=0;
        count=m;
        memset(buffer,0,(SIZE+1)*sizeof(char)); //init sir caractere

        //initializez geenratorul de numere aleatoare
        srand(time(NULL));

//la craerea thread-urilor, am nevoie de n thr gen si unul printer, cum la join am nevoie ca atat printerul cat si generatoarele sa si termine treaba am nevoie de un singur vector de tid uri cum lucreaza toate odata si se asteapta prin var cond
        pthread_t tid[n+1];

        //creez n thread uri generator
        for(int i=0;i<n;i++)
                pthread_create(&tid[i],NULL,generate,NULL);

        //creez un printer
                pthread_create(&tid[n],NULL,print,NULL);

	for(int i=0;i<=n;i++){
		pthread_join(tid[i],NULL);
	}
        return 0;
}
