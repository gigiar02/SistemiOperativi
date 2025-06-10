/*
 * Si realizzi un programma in C e Posix sotto linux che, con l'ausilio della libreria Pthread,
 * lancia m thread per calcolare la somma dei prodotti delle colonne di due matrici mxm.
 * 
 * L'i-esimo thread, dopo aver calcolato la somma dei prodotti delle colonne i-esime delle due matrici,
 * inserisce il risultato in un array m-dimensionale, in modo concorrente, nella prima locazione libera disponibile.
 * 
 * Non appena l'array sarà riempito, un m+1-esimo thread, che era in attesa, provvederà a stamparne il contenuto.
 * 
 * Le matrici devono essere allocate dinamicamente.
 * 
 * Usare mutex e variabili di condizione.
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
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
int posizioneCorrente = 0;
int m;
int **matrix1;
int **matrix2;
int *vector;


void inizializza()
{
  matrix1 = malloc(sizeof(int *) * m);
  matrix2 = malloc(sizeof(int *) * m);
  vector  = malloc(sizeof(int ) * m);
  
  for(int i = 0; i < m; i++)
  {
    matrix1[i] = malloc(sizeof(int ) * m);
    matrix2[i] = malloc(sizeof(int ) * m);
    
    for(int j = 0; j < m; j++)
    {
      matrix1[i][j] = rand() % m;
      matrix2[i][j] = rand() % m;
    }
  }
}

void prodottoColonne(void * arg)
{
  int col = (int) arg;
  int sum = 0;
  for(int i = 0; i < m; i++)
  {
    sum += matrix1[i][col] * matrix2[i][col];
  }
  
  lock(&mutex);
  vector[posizioneCorrente] = sum;
  posizioneCorrente+=1;
  if(posizioneCorrente == m) cond_signal(&cond);
  unlock(&mutex);
}
void stampaMatrice()
{
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < m; j++)
    {
      printf(" %d ",matrix1[i][j]);
    }
    printf("\n");
  }
  printf("\n \n \n");
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < m; j++)
    {
      printf(" %d ",matrix2[i][j]);
    }
    printf("\n");
  }

}
void stampaVettore(void * arg)
{
  lock(&mutex);
  while(posizioneCorrente != m)
  {
    printf("Hanno finito \n");
    cond_wait(&cond,&mutex);
  }
  
  //Stampa valori
  for(int i = 0; i < m; i++)
  {
    printf(" %d ",vector[i]);
  }
}

int main(int argc,char **argv)
{
  if(argc != 2)
  {
    printf("Errore argc \n");
    return 0;
  }
  m = atoi(argv[1]);
  pthread_t tid[m+1];
  inizializza();
  stampaMatrice();
  pthread_create(&tid[m],NULL,(void *) &stampaVettore,NULL);
  for(int i = 0; i < m; i++)
  {
    printf("i = %d \n",i);
    pthread_create(&tid[i],NULL,(void *) &prodottoColonne,(void *) i);
  }
  
  for(int i = 0; i < m + 1; i++)
  {
    pthread_join(tid[i],NULL);
  }
}
