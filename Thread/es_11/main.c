#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
#define wait pthread_cond_wait
#define signal pthread_cond_signal

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condizione = PTHREAD_COND_INITIALIZER;
//Struttura contente il numero degli elementi messi nell'array e gli elementi stessi
int n;
struct info
{
    pthread_t id;
    int num;
    int *numElementi;

};

int **matrix;
int *vector;
int inserimenti = 0;
int nVector;
int esci = 1;
struct info *msg;

void inizializzaMatrice()
{
    printf("Inizializzazione \n");
    matrix = malloc(sizeof(int *) * n);

    for(int i = 0; i < n; i++)
    {
        matrix[i] = malloc(sizeof(int) * n);
        
        for(int j = 0; j < n; j++)
        {
            int h = (i+j) % n;
            matrix[i][j] = h;
        }
    }
    printf("Fine Inizializzazione \n");
}
void stampaMatrice()
{
    printf("Stampa  \n");
    for(int i = 0; i < n; i++)
    {
        
        for(int j = 0; j < n; j++)
        {
            printf(" %d ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("Fine Stampa  \n");
}

void inserisciElemento(void * id)
{

    int i = (int) id;
    msg[i].id = i;
    msg[i].num = 0;
    //printf("ID START =  %d \n",i);
    //sleep(5);
    while(esci)
    {
        lock(&mutex);
        int c = rand() % n;
        int casualNumber = matrix[i][c];
        if(inserimenti > nVector)
        {
            //printf("Il vettore è pieno \n");
            esci = 0;
            signal(&condizione);
            unlock(&mutex);
            break;
        }

        vector[inserimenti] = casualNumber;
        msg[i].num+=1;
        //printf("ID = %d inserisco: %d \n",i,casualNumber);
        inserimenti+=1;
        unlock(&mutex);
        usleep(10);
    }
}

void estraiElementi(void * id)
{
    lock(&mutex);
    while(esci)
    {
        wait(&condizione,&mutex);
    }

    for(int i = 0; i < nVector; i++)
    {
        printf("%d %d \n",i,vector[i]);

    }

    for(int i = 0; i < n; i++)
    {
        if(msg[i].num == 0) continue;
        printf("ID = %d numero elementi stampati = %d \n",i,msg[i].num);

    }

}

int main()
{
    n = 5000;
    msg = calloc(sizeof(struct  info),sizeof(struct  info) * n);
    nVector = (n+1)/2;
    vector = malloc(sizeof(int ) * nVector);
    inizializzaMatrice();
    //stampaMatrice();
    pthread_t id[n];
    pthread_t es;
    int i = 0;

    pthread_create(&es,NULL,(void *) &estraiElementi,NULL);
    for(i; i < n; i++)
    {
        pthread_create(&id[i],NULL,(void *) inserisciElemento,(void *) i);
    }


    pthread_join(es,NULL);
    for(int i = 0; i < n; i++)
    {
        //printf("Aspetto %d \n",i);
        pthread_join(id[i],NULL);
    }
    
    
}

