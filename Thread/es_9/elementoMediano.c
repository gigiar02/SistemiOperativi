#include <stdio.h>
#include <string.h>
//#include <srand.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <pthread.h>
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
pthread_mutex_t  mutex;
int n;
int **matrix;
int mediana = -1;
/*
  Elemento mediano
*/

int insertionSort(int k)
{
  for(int i = 2; i < n; i++)
  {
    int j = i - 1;
    int key = matrix[k][i];
    
    while(j >= 0 && key <= matrix[k][j])
    {
      matrix[k][j+1] = matrix[k][j];
      j-=1;
    }
    matrix[k][j+1] = key;
  }
  
  return matrix[k][n/2];
}
void inizializzaMatrice()
{
  matrix = malloc(sizeof(int *) * n);
  
  for(int i = 0; i < n; i++)
  {
    matrix[i] = malloc(sizeof(int ) * n);
  }
  
  //Popolamento i,j = (i + j) * n / (1...n)
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      int h = ((i + j) * n)/(rand() % n + 1);
      matrix[i][j] = h;
    }
  }
}

void stampa()
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

void findMax(void * id)
{
  int j = (int) id;
  printf("Sono id = %d \n",j);
  
  int med = insertionSort(j);
  
  lock(&mutex);
  if(mediana < med) mediana = med;
  unlock(&mutex);
  
}
int main(int argc, char **argv)
{
  srand(time(NULL));
  if(argc != 2) return;
  n = atoi(argv[1]);
  pthread_t id[n];
  
  inizializzaMatrice();
  stampa();
  
  for(int i = 0; i < n; i++)
  {
    printf("Genero %d \n",i);
    pthread_create(&id[i],NULL,(void *) &findMax,(void *) i);
  }
  
  for(int i = 0; i < n; i++)
  {
    pthread_join(id[i],NULL);
  }
  stampa();
  printf("Valore finale = %d \n",mediana);
}
