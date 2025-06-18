/*
  Traccia dell'esercizio:
    Scrivi un programma in linguaggio C che utilizza i thread per eseguire operazioni su due matrici. 
    
    Il programma dovrebbe prendere in input due matrici quadrate di dimensione NxN, dove N è un numero intero definito dall'utente. 
    Successivamente, il programma dovrebbe creare due thread che eseguono le seguenti operazioni:

    1. Il primo thread dovrebbe calcolare la somma degli elementi delle due matrici e salvare il risultato in una terza matrice.
    2. Il secondo thread dovrebbe calcolare il prodotto delle due matrici e salvare il risultato in una quarta matrice.

    Infine, il programma dovrebbe aspettare che entrambi i thread abbiano completato i loro calcoli e quindi stampare i risultati ottenuti.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int **A;
int **B;
int **C;
int **D;
int N;

int ** inizializza(int **M)
{
  M = malloc(sizeof(int *) * N);
  for(int i = 0; i < N; i++)
  {
    M[i] = malloc(sizeof(int ) * N);
    for(int j = 0; j < N; j++)
    {
      M[i][j] = rand() % N;
    }
  }
  return M;
}

void stampa(int **M)
{
  for(int i = 0; i < N; i++)
  {
    for(int j = 0; j < N; j++)
    {
      printf(" %d ",M[i][j]);
    }
    printf("\n");
  }
}

void somma(void * arg)
{
  for(int i = 0; i < N; i++)
  {
    for(int j = 0; j < N; j++)
    {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
}

void prodotto(void * arg)
{
  for(int i = 0; i < N; i++)
  {
    for(int j = 0; j < N; j++)
    {
      D[i][j] = A[i][j] * B[i][j];
    }
  }
}


int main(int argc,char **argv)
{
  if(argc != 2){printf("Errore argc "); return 0;}
  N = atoi(argv[1]);
  A = inizializza(A);
  B = inizializza(B);
  C = inizializza(C);
  D = inizializza(D);
  printf("A \n");
  stampa(A);
  printf("B \n");
  stampa(B);
  pthread_t tid[2];
  
  pthread_create(&tid[0],NULL,(void *) &somma,NULL);
  pthread_create(&tid[1],NULL,(void *) &prodotto,NULL);
  
  pthread_join(tid[0],NULL);
  pthread_join(tid[1],NULL);
  
  printf("Stampo risultati ottenuti \n");
  printf("C \n");
  stampa(C);
  printf("D \n");
  stampa(D);
}
