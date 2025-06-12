/*
  Scrivere un programma in C e Posix sotto Linux che utilizzi la libreria Pthread per risolvere il seguente problema: 
  date due matrici A e B, di dimensioni nxn di numeri interi tra 1 e 100, generati casualmente, 
  creare n thread dove l’i-esimo thread provvede a sommare le entrate delle righe i-esime delle due matrici, 
  in modo da ottenere una matrice Somma di dimensioni nxn. 
  Sincronizzare i thread in modo da sommare le righe delle due matrici A e B nell’ordine 1, 2, ..., n. 
  Inoltre, un thread n+1-esimo attende che la matrice Somma sia calcolata, per stamparne, successivamente, il contenuto. 
  Usare semafori e variabili di condizione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define wait        sem_wait
#define signal      sem_post
#define cond_wait   pthread_cond_wait
#define cond_signal pthread_cond_signal
#define lock        pthread_mutex_lock
#define unlock      pthread_mutex_unlock

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t **sem;
int **A;
int **B;
int **C;
int rigaCorrente = 0;
int n;

void inizializza()
{
  A = malloc(sizeof(int *) * n);
  B = malloc(sizeof(int *) * n);
  C = malloc(sizeof(int *) * n);
  
  for(int i = 0; i < n; i++)
  {
    A[i] = malloc(sizeof(int ) * n);
    B[i] = malloc(sizeof(int ) * n);
    C[i] = malloc(sizeof(int ) * n);
    
    for(int j = 0; j < n; j++)
    {
      A[i][j] = rand() % 50;
      B[i][j] = rand() % 20;
    } 
  }
}

void stampa(int **matrix)
{
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      printf(" %d ",matrix[i][j]);
    } 
    printf("\n");
  }
}

void sommaRiga(void * arg)
{
  int row = (int) arg;
  
  wait(sem[row]);
  //printf("Sono riga %d \n",row);
  //Effettua somma riga
  for(int i = 0; i < n; i++)
  {
    C[row][i] = A[row][i] + B[row][i];
  }
  rigaCorrente++;
  cond_signal(&cond);
  if(row + 1 < n)
  {
    signal(sem[row + 1]);
  }
  //printf("Sono riga %d  e ho finito \n",row);
}

void stampaC()
{
  lock(&mutex);
  while(rigaCorrente != n)
  {
    cond_wait(&cond,&mutex);
    //printf("Sbloccato \n");
  }
  
  //Stampa di c
  printf("Stampo C \n");
  stampa(C);
}


int main(int argc,char **argv)
{
  if(argc != 2)
  {
    printf("Errore argc \n");
    return 0;
  }
  n = atoi(argv[1]);
  pthread_t tid[n+1];
  sem = malloc(n * sizeof(sem_t *));
  
  //Inizializzazione semafori
  for(int i = 0; i < n; i++)
  {
    sem[i] = malloc(sizeof(sem_t));
    int res = sem_init(sem[i],0, (i == 0 ? 1 : 0));
    //printf("risultato = %d \n",res);
  }
  inizializza();
  printf("Stampo A \n");
  stampa(A);
  printf("\n");
  printf("Stampo B \n");
  stampa(B);
  
  pthread_create(&tid[n],NULL,(void *) &stampaC,NULL);
  for(int i = 0; i < n; i++)
  {
    pthread_create(&tid[i],NULL,(void *) &sommaRiga,(void *) i);
  }
  
  for(int i = 0; i < n + 1; i++)
  {
    pthread_join(tid[i],NULL);
  }
  
}
