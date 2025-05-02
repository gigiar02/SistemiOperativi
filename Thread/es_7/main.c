/*
  Creato il 2 maggio 2025 orario: 11:33
  La traccia è nella directory
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#define wait pthread_mutex_lock
#define signal pthread_mutex_unlock

int **matrix;
int n;
pthread_mutex_t mutex;
long double global = -1;

//Inizializza la matrice n*n
void matrixInit()
{
  //Alloco la matrice
  matrix = malloc((sizeof(int*)) * n);
  if(!matrix) {perror("Allocazione non andata a buon fine: "); return;}
  
  for(int i = 0; i < n; i++)
  {
    matrix[i] = malloc(sizeof(int) * n);
  }
  
  //Riempimento della matrice con valori tra 0 e 255
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      long double randNumber = rand() % 256;
      printf("%d %d = %Lf \n",i,j,randNumber);
      matrix[i][j] = randNumber;
    }
  }
}


//Prodotto degli elementi della riga passata in input
void rowProduct(void* arg)
{
  long double localProduct = 1;
  //Cast da void ad intero
  int index = (int) arg;
  printf("Sono %d e inizio a lavorare \n",index);
  
  for(int i = 0; i < n; i++)
  {
    localProduct *= matrix[index][i];
  }
  
  printf("Prodotto locale %Lf \n",localProduct);
  
  //Piu thread cercano di accedere a global per potenzialmente modificarla
  wait(&mutex);
  if(global < localProduct) global = localProduct;
  signal(&mutex);
}


int main(int argc,char **argv)
{
  srand(time(NULL));
  //Controllo argomenti
  if(argc != 2) {printf("Passare n come argomento \n"); return 2;}
  
  n = atoi(argv[1]);
  matrixInit();
  
  pthread_t id[n];
  for(int i = 0; i < n; i++)
  {
    //Creazione thread
    pthread_create(&id[i],NULL,(void *) &rowProduct,(void *) i);
  }
  
  //Aspetto che i thread abbiano terminato
  sleep(1);
  for(int i = 0; i < n; i++)
  {
    printf("%d wait \n",i);
    pthread_join(id[i],NULL);
    printf("%d end \n",i);
  }
  
  printf("Max Value = %Lf \n",global);
  return 0;

}


