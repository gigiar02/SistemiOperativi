/*
  Creato il 08/04/2025 alle ore 11:51
  La traccia è nella directory
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <math.h>
int n = 0;
int min = INFINITY;
int max = -500;


//Messaggio inviato ad ogni thread contenente la matrice
struct msg
{
  int **matrix;
  int id;
  int n;
};


void findMinMax(void * arg)
{
  struct msg *m = (struct msg *) arg;
  int id = m->id;
  int n = m->n;
  int **mat = m->matrix; 
   printf("Sono il thread %d e opero sulla riga %d \n",m->id);
   //Search on my row
   for(int i = 0; i < n; i++)
   {
      printf("Esamino: %d min: %d max: %d \n",mat[id][i],min,max);
      if(mat[id][i] > max) {max = mat[id][i];}
      if(mat[id][i] < min){ min = mat[id][i];}
      
      
   }
   printf("Sono il thread %d e ho finito il mio lavoro %d \n",id);
}

//Stampa la matrice passata in input
void matrixPrint(int **matrix)
{
  printf("START \n");
  
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      printf(" %d ",matrix[i][j]);
    }
    printf("\n");
  }
  
  printf("END \n");
}


//Popola una matrice n*n di valori
void matrixFill(int **matrix)
{
  
  //el[i][j] = i + j + 4
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      matrix[i][j] = i + j + 4;
    }
  }
  
}

int main(int argc,char *argv[])
{
  struct msg threadMsg;
  //In input deve essere passato il nunero di thread da creare
  if(argc < 2)
  {
    printf("Miss an argument \n");
    exit(-1);
  }
  
  //converto il valore preso in un intero
  n = atoi(argv[1]);
  pthread_t id[n];
  
  //Alloco la matrice
  int **matrix = malloc(n * sizeof(int*));
  for(int i = 0; i < n; i++)
  {
    matrix[i] = malloc(n * sizeof(int));
  }
  
  //La matrice viene riempita e stampata
  matrixFill(matrix);
  printf("STAMPO LA MATRICE: \n");
  matrixPrint(matrix);
  
  threadMsg.matrix = matrix;
  threadMsg.n = n;
  
  //Creazione dei thread
  for(int i = 0; i < n; i++)
  {
    pthread_create(&id[i],NULL,findMinMax,(void *) &threadMsg);
    threadMsg.id = i;
  }
  
  //Aspetto che i thread abbiano finito
  sleep(1);
  for(int i = 0; i < n; i++)
  {
    printf("Aspetto che il thread %d abbia finito \n",i);
    pthread_join(id[i],NULL);
    printf("thread %d ha finito \n",i);
    
  }
  
  printf("Min = %d e Max = %d \n",min,max);
  
}
