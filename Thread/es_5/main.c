/*
  Data di creazione: 14/04/2025 ore 09:54
  La traccia è nella directory
  Note:
  Il mutex non è strettamente necessario poiché si potrebbe utilizzare un array di dimensione tre per salvare i tre risultati e dare il ruolo al master di terminare il lavoro
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <pthread.h>
#include <math.h>

#define lock   pthread_mutex_lock 
#define unlock pthread_mutex_unlock

int n;
float average;
int *array;
int elements = 0;
pthread_mutex_t mutex;

//Stampa il messaggio di errore msg ed esce con ex
int err(char *msg,int ex)
{
  perror(msg);
  exit(ex);
}

void averageMajor(void * argc)
{
  //j rappresenta il punto da cui deve partire il thread es i = 1 e n = 21: j = 1*7 = 7
  int id = (int) argc;
  int size = n/3;
  int j = id * size;
  printf("id = %d start = %d \n",id,j);
  
  //Calcolo valori che sono maggiori del valore medio
  int localElements = 0;
  for(int i = j; i < size + j;i++)
  {
    printf("array[%d] = %d \n",i,array[i]);
    if(array[i] > average)
    {
      localElements++;
    }
  }
  
  //Aggiorno il valore globale
  lock(&mutex);
  printf("local = %d \n",localElements);
  elements += localElements;
  unlock(&mutex);
}

int main(int argc,char *argv[])
{
  //L'utente non ha immesso da riga di comando n
  if(argc != 2) err("Too few arguments: ",-1);
  
  //Controllo del numero inserito
  n = atoi(argv[1]);
  if(n < 21 || n%3 != 0) err("The number must be >= 21 and a three multiple",-2);
  
  //Costruzione vettore
  array = malloc(n * sizeof(int));
  int sum = 0;
  for(int i = 0; i < n; i++)
  {
    int casualNumber = rand() % 6;
    //printf("Casual number = %d \n",casualNumber);
    array[i] = i * casualNumber + 2*i;
    sum+= array[i];
  }
  
  //Calcolo media
  average = sum/n;
  printf("Average is = %f \n",average);
  
  pthread_t tid[3];
  
  //Creo i tre thread a cui far eseguire il calcolo
  for(int i = 0; i < 3; i++)
  {
    pthread_create(&tid[i],NULL,&averageMajor,(void *) i);
    
  }
  
  //Aspetto la terminazione dei thread
  for(int i = 0; i < 3; i++)
  {
    pthread_join(tid[i],NULL);
    
  }
  
  //Stampo l'array
  for(int i = 0; i < n; i++)
  {
    printf(" %d ",array[i]);
  }
  //Stampo il risultato
  printf(" result = %d \n",elements);

}
