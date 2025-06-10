/*
  10/06/2025 orario: 09:11
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#define inf (int) INFINITY
int n;
int **matrix;


void inizializzaMatrice()
{
  matrix = malloc(sizeof(int *) * n);
  
  for(int i = 0; i < n; i++)
  {
    matrix[i] = malloc(sizeof(int ) * n);
    
    for(int j = 0; j < n; j++)
    {
      matrix[i][j] = rand() % n;
    }
  }
}

void stampaMatrice()
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

void ricercaValori(void * arg)
{
  int row = (int) arg;
  int max = -inf;
  int min = inf;
  for(int i = 0; i < n; i++)
  {
    if(matrix[row][i] > max)
    {
      max = matrix[row][i];
    }
    
    if(matrix[row][i] < min)
    {
      min = matrix[row][i];
    }
  }
  
  printf("massimo = %d minimo = %d \n",max,min);
}
int main(int argc,char **argv)
{
  if(argc != 2)
  {
    printf("Errore argc \n");
    return 0;
  }
  
  n = atoi(argv[1]);
  pthread_t tid[n];
  inizializzaMatrice();
  stampaMatrice();
  
  for(int i = 0; i < n; i++)
  {
    pthread_create(&tid[i],NULL,(void *) &ricercaValori, (void *) i);
  }
  
  for(int i = 0; i < n; i++)
  {
    pthread_join(tid[i],NULL);
  }
}
