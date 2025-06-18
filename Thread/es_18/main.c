/*
  Si realizzi un programma in C e Posix sotto Linux che, con l’ausilio della libreria Pthread, lancia m thread per calcolare la somma dei prodotti delle colonne di due 
  matrici mxm. L’i-esimo thread, dopo aver calcolato la somma dei prodotti delle colonne i-esime delle due matrici, inserisce il risultato in un array m-dimensionale, in
  modo concorrente, nella prima locazione libera disponibile. Non appena l’array sarà riempito, un m+1-esimo thread, che era in attesa, provvederà a stamparne il
  contenuto. Le matrici devono essere allocate dinamicamente. Usare mutex e variabili di condizione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
#define cond_wait pthread_cond_wait
#define cond_signal pthread_cond_signal

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int **A;
int **B;
int *C;
int m;
int pos = 0;

int** inizializza(int **M)
{
  M = malloc(m * sizeof(int *));
  for(int i = 0; i < m; i++)
  {
    M[i] = malloc(m * sizeof(int ));
    for(int j = 0; j < m; j++)
    {
      M[i][j] = rand() % m;
      //printf(" %d \n",M[i][j]);
    }
  }
  return M;
}

void stampa(int **M)
{
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < m; j++)
    {
      printf(" %d ",M[i][j]);
    }
    printf("\n");
  }
}

void sommaColonne(void * arg)
{
  int row = *(int *) arg;
  int sum = 0;
  for(int i = 0; i < m; i++)
  {
      sum += A[i][row] * B[i][row];
    
  }
  
  lock(&mutex);
  C[pos] = sum;
  pos+=1;
  if(pos >= m) cond_signal(&cond);
  unlock(&mutex);
}

void ultimo(void * arg)
{
  lock(&mutex);
  while(pos < m)
  {
    cond_wait(&cond,&mutex);
  }
  
  for(int i = 0; i < m; i++)
  {
    printf(" %d ",C[i]);
  }
  printf("\n");
}

int main(int argc,char **argv)
{
  
  if(argc != 2){printf("Errore argc "); return 0;}
  m = atoi(argv[1]);
  
  pthread_t tid[m+1];
  
  A = inizializza(A);
  //printf("Finita inizializzazione A \n");
  B = inizializza(B);
  //printf("Finita inizializzazione B \n");
  printf("A : \n");
  stampa(A);
  printf("B : \n");
  stampa(B);
  //printf("Finita Stampa \n");
  C = malloc(sizeof(int ) * m);
  //printf("Finita inizializzazione \n");
  pthread_create(&tid[m],NULL,(void *) &ultimo,NULL);
  for(int i = 0; i < m; i++)
  {
    int *arg = malloc(sizeof(int));
    *arg = i;
    pthread_create(&tid[i],NULL,(void *) &sommaColonne,arg);
  }
  
  for(int i = 0; i < m+1; i++)
  {
    pthread_join(tid[i],NULL);
  }
}
