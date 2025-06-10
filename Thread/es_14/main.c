/*
Si realizzi un programma in C e Posix sotto Linux che, con l’ausilio della libreria Pthread, lancia m thread per calcolare il prodotto righe-colonne di due matrici di dimensioni mxn e nxp. L’i-esimo thread, dopo aver calcolato l’i-esima riga della matrice risultato ne calcola la somma ed inserisce il risultato in un array m-dimensionale, in modo concorrente, nella prima locazione libera disponibile. Non appena l’array sarà riempito, un m+1-esimo thread, che era in attesa, provvederà a stamparne il contenuto. Le matrici devono essere allocate dinamicamente. Usare mutex e variabili di condizione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
#define cond_wait pthread_cond_wait
#define cond_signal pthread_cond_signal

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int **matrix1;
int **matrix2;
int *vector;
int m;
int n;
int p;
int pos = 0;

void init()
{
  //mxn e nxp
  matrix1 = malloc(sizeof(int *) * m);
  matrix2 = malloc(sizeof(int *) * n);
  vector = malloc(sizeof(int) * m);
  
  for(int i = 0; i < m; i++)
  {
    matrix1[i] = malloc(sizeof(int ) * n);
    for(int j = 0; j < n; j++)
    {
      matrix1[i][j] = rand() % n;
    }
  }
  
  for(int i = 0; i < n; i++)
  {
    matrix2[i] = malloc(sizeof(int ) * p);
    for(int j = 0; j < p; j++)
    {
      matrix2[i][j] = rand() % n;
    }
  }
}

void stampa()
{
  printf("A: \n");
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < n; j++)
    {
      printf(" %d ",matrix1[i][j]);
    }
    printf("\n");
  }
  
  printf("\nB: \n");
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < p; j++)
    {
      printf(" %d ",matrix2[i][j]);
    }
    printf("\n");
  }
}

void calcoloRiga(void *arg)
{
  int row = (int) arg;
  int sum = 0;
  
  
  for(int i = 0; i < p; i++)
  {
    for(int j = 0; j < n; j++)
    {
      sum += matrix1[row][j] * matrix2[j][i];
    }
  }
  
  lock(&mutex);
  vector[pos] = sum;
  pos+=1;
  if(pos == m)
  {
    cond_signal(&cond);
  }
  unlock(&mutex);

}

void stampaRisultato(void * arg)
{
  lock(&mutex);
  while(pos != m)
  {
    cond_wait(&cond,&mutex);
  }
  
  //Stampa vettore
  for(int i = 0; i < m; i++)
  {
    printf(" %d ",vector[i]);
  }
  printf("\n");
}

int main(int argc, char **argv)
{
  if(argc != 4)
  {
    printf("Specificare 3 valori \n");
    return 0;
  }
  //mxn e nxp
  m = atoi(argv[1]);
  n = atoi(argv[2]);
  p = atoi(argv[3]);
  
  pthread_t tid[m + 1];
  init();
  stampa();
  pthread_create(&tid[m],NULL,(void *) &stampaRisultato,NULL);
  for(int i = 0; i < m; i++)
  {
    pthread_create(&tid[i],NULL,(void *) &calcoloRiga,(void *) i);
  }
  
  pthread_join(tid[m],NULL);
  for(int i = 0; i < m; i++)
  {
    pthread_join(tid[i],NULL);
  }
  return 0;
}
