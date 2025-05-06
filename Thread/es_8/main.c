/*
  6/05/2025 orario: 11:37
  La traccia è nella directory
  Il contatore viene incrementato una volta in piu 
  Da sistemare il codice
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
#define wait   pthread_cond_wait
#define signal pthread_cond_signal

pthread_mutex_t mutex_somma;
pthread_cond_t cond_somma;
pthread_mutex_t mutex_controllo;
pthread_cond_t cond_controllo;
int soglia = 0;
int global = 0;
int contatore = 0;
bool fine = false;
bool A = false;
bool B = false;
bool fineA = false;
bool fineB = false;

void sommaA(void* arg)
{
  for(int i = 0; i < 500; i++)
  {
    A = false;
    //Generazione numero casuale
    int casualNumber = rand() % 30;
    
    //Aspetto che B mi dia il segnale per poter continuare
    //printf("Sono A e aspetto di essere sbloccato \n");
    printf("Lock mutex");
    lock(&mutex_somma);
    wait(&cond_somma,&mutex_somma);
    printf("Ottenuto \n");
    //printf("Sono A e sono stato sbloccato \n");
    if(soglia <= contatore || fine)
    {
      fine = true;
      fineA = true;
      A = true;
      unlock(&mutex_somma);
      //Finché b non ha finito
      while(!fineB)
      {
        A = true;
        //printf("Sono a e aspetto \n");
        signal(&cond_somma);
      }
      signal(&cond_controllo);
      break;
    }
    
    global += casualNumber;
    contatore++;
    printf(" A Global = %d contatore = %d numero = %d \n",global,contatore,casualNumber);
    A = true;
    unlock(&mutex_somma);
    while(!B)
    {
      //printf("Aspetto B \n");
      signal(&cond_somma);
    }
    //Sblocco B una volta finito
    while(!B)
    {
      //printf("Aspetto B \n");
      signal(&cond_somma);
    }
  }
}


void sommaB(void* arg)
{
  for(int i = 0; i < 500; i++)
  {
     B = false;
    //Generazione numero casuale
    int casualNumber = rand() % 30;
    while(!A)
    {
      //printf("Aspetto A \n");
      signal(&cond_somma);
    }
    //Aspetta che A abbia finito
    lock(&mutex_somma);
    wait(&cond_somma,&mutex_somma);
    if(soglia <= contatore || fine)
    {
      fine = true;
      fineB = true;
      B = true;
      unlock(&mutex_somma);
      while(!fineA)
      {
        //printf("FineA è false \n");
        //printf("B Aspetto \n");
        signal(&cond_somma);
      }
      signal(&cond_controllo);
      
      break;
    }
    
    global += casualNumber;
    contatore++;
    printf(" B Global = %d contatore = %d numero = %d \n",global,contatore,casualNumber);
    B = true;
    unlock(&mutex_somma);
  }
  }


void controllo(void* arg)
{
  lock(&mutex_controllo);
  wait(&cond_controllo,&mutex_controllo);
  unlock(&mutex_controllo);
  //Termina il programma
  
  
  printf("global = %d contatore = %d \n",global,contatore);
}

int main(int argc,char **argv)
{
  srand(time(NULL));
  if(argc != 2){printf("Inserire la soglia \n"); return 1;}
  soglia = atoi(argv[1]);
  pthread_t tid[3];
  //Creazione dei thread
  pthread_create(&tid[0],NULL,(void *) &sommaA,NULL);
  pthread_create(&tid[1],NULL,(void *) &sommaB,NULL);
  pthread_create(&tid[2],NULL,(void *) &controllo,NULL);
  
  sleep(5);
  for(int i = 0; i < 3; i++)
  {
    printf("Aspetto il thread %d \n",i);
    pthread_join(tid[i],NULL);
    printf("Fine thread %d \n",i);
  }
  
  
}
