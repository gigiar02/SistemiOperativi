/*
  Data Creazione 07/05/2025 orario 10:23
  La traccia è nella directory
  Ho presupposto che la traccia volesse l'elemento di posizione mediano con valore massimo.
  è scritta male e quindi lascia spazio ad un'altra interpretazione nella quale vuole effettivamente il mediano inteso come valore dell'array e non indice. In quel caso basta fare un sort sulla riga e per il resto è uguale
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock

int n;
int glob = 0;
int **mat;
pthread_mutex_t mutex;

void matInit()
{
  mat = malloc(sizeof(int *) * n);
  for(int i = 0; i < n; i++)
  { 
    mat[i] = malloc(sizeof(int ) * n);
  }
  
  //Riempimento matrice
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      int r = rand() % 30;
      mat[i][j] = r;
    }
  }

}


void searchMax(void * arg)
{
  int k = (int) arg;
  int m = n/2;
  int elementoMediano = mat[k][m];
  printf("Elemento mediano %d = %d \n",k,elementoMediano);
  
  lock(&mutex);
  if(elementoMediano > glob) glob = elementoMediano;
  unlock(&mutex);
}

int main(int argc,char **argv)
{
  //Controllo argomenti
  if(argc != 2){printf("Passa come parametro la dimensione della matrice \n"); return 1;}
  n = atoi(argv[1]);
  pthread_t tid[n];
  
  //Generazione thread
  for(int i = 0; i < n; i++)
  {
    pthread_create(&tid[i],NULL,(void *) &searchMax, (void *) i);
  }
  
  //Aspetto che i thread abbiano finito
  for(int i = 0; i < n; i++)
  {
    printf("Aspetto %d \n",i);
    pthread_join(tid[i],NULL);
    printf("Ho finito di aspettare %d \n",i);
  }
  
  //Stampo a video il risultato
  printf("Master: valore massimo = %d \n",glob);
  

}
