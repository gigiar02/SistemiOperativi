/*
  Creato il 9 giugno 2025 orario: 09:21
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
#define cond_wait pthread_cond_wait
#define cond_signal pthread_cond_signal
#define wait sem_wait
#define signal sem_post

int m = 4;
int n = 4;
int **matrix;
int *vector;
pthread_cond_t cond;
pthread_mutex_t mutex;
int pieno = 0;

void init()
{
  matrix = malloc(sizeof(int *) * n);
  vector = malloc(sizeof(int) * n);
  
  for(int i = 0; i < n; i++)
  {
    matrix[i] = malloc(sizeof(int) * m);
    
    for(int j = 0; j < m; j++)
    {
      matrix[i][j] = rand() % (n*m) + 1;
    }
  }
}


void matrixPrint()
{
  for(int i = 0; i < n; i++)
  {  
    for(int j = 0; j < m; j++)
    {
      printf(" %d ",matrix[i][j]);
    }
    printf("\n");
  }
}


void stampaVettore()
{
  for(int i = 0; i < n; i++)
  {
    printf(" %d ",vector[i]);
  }
  printf("\n");
}

void findMax(void * arg)
{
  int row = (int) arg;
  sem_t *sem_cs = sem_open("sem_cs",O_EXCL);
  if(!sem_cs) return;
  //printf("Mi occupo della riga %d \n",row);
  //Ricerca del massimo alla riga corrente
  int max = -1;
  for(int i = 0; i < m; i++)
  {
    //printf("-%d-%d- max = %d \n",row,i,max);
    if(matrix[row][i] > max)
    {
      max = matrix[row][i];
    }
    //printf("Fine iterazione \n");
  }
  
  //printf("Prima dell'errore \n");
  wait(sem_cs);
  vector[pieno] = max;
  pieno += 1;
  printf("Pieno = %d \n",pieno);
  //Sono l'ultimo
  if(pieno == m) cond_signal(&cond);
  signal(sem_cs);
  
}

void findMaxL(void * arg)
{
  lock(&mutex);
  while(pieno < m)
  {
    cond_wait(&cond,&mutex);
    printf("Aspetto cond \n");
  }
  stampaVettore();
  //Ricerca del messimo
  int max = -1;
  for(int i = 0; i < n; i++)
  {
    if(vector[i] > max)
    {
      max = vector[i];
    }
  }
  
  printf("Stampo il massimo: %d \n",max);
}
int main()
{
  //Inizializzazione di matrice m*n e vettore di dimensione m
  init();
  matrixPrint();
  pthread_t tid[n];
  pthread_t last;
  
  sem_unlink("sem_cs");
  sem_t *sem_cs =  sem_open("sem_cs",O_CREAT,999,1);
  if(!sem_cs) return;
  sem_close(sem_cs);
  
  pthread_create(&last,NULL,(void *) &findMaxL,NULL);
  for(int i = 0; i < n; i++)
  {
    pthread_create(&tid[i],NULL,(void *) &findMax,(void *) i);
  }
  
  pthread_join(last,NULL);
  for(int i = 0; i < n; i++)
  {
    pthread_join(tid[i],NULL);
  }
  
  
  

}
