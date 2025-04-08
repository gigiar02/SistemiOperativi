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


//Messaggio standard da inviare ad ogni thread
struct msg
{
  int **matrix;
  int id;
  int n;
};


//Ricerca il minimo o il massimo sulla riga assegnata
void findMinMax(void * arg)
{
  struct msg *m = (struct msg *) arg;
  int id = m->id;
  int n = m->n;
  int **mat = m->matrix; 
  
  //printf("ID = %d \n",id);
  
  //Search on my row
  for(int i = 0; i < n; i++)
  {
    //printf("Esamino: %d min: %d max: %d \n",mat[id][i],min,max);
    
    //Aggiornamento minimo e massimo
    if(mat[id][i] > max) max = mat[id][i];
    if(mat[id][i] < min) min = mat[id][i];
  }
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
  
  //Creo l'array di messaggi
  struct msg threadMsg[n];
  
  //La matrice viene riempita e stampata
  matrixFill(matrix);
  printf("STAMPO LA MATRICE: \n");
  matrixPrint(matrix);
  
  //Creazione dei thread
  for(int i = 0; i < n; i++)
  {
    //Creazione del messaggio da inviare ai singoli thread
    threadMsg[i].matrix = matrix;
    threadMsg[i].n = n;
    threadMsg[i].id = i;
    pthread_create(&id[i],NULL,findMinMax,(void *) &threadMsg[i]);
    
  }
  
  //Aspetto che i thread abbiano finito
  sleep(1);
  for(int i = 0; i < n; i++)
  {
    printf("Aspetto che il thread %d abbia finito \n",i);
    pthread_join(id[i],NULL);
    printf("thread %d ha finito \n",i);
    
  }
  
  //Stampa del risultato
  printf("Min = %d  Max = %d \n",min,max);
}
