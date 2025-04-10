/*
  Data Creazione: 10/04/2025 ore 09:27
  La traccia è nella directory
  Note:
  Non sto utilizzando mutex poiché i programmi sembrerebbero funzionare lo stesso, senza problemi.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#define  lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
pthread_mutex_t mutex;

//Matrice di caratteri e numero di righe/colonne
char ***mat;
int n;
char *el;
int trovato = 0;
int coordinate[2];

//Stampa un messaggio di errore e invoca exit(numb)
int err(char *text,int numb)
{
  printf("Errore %s \n",text);
  exit(numb);
}


//Stampa la matrice
void matrixPrint()
{
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      printf("%s\t",mat[i][j]);
    }
    printf("\n");
  }
}


//Alloca la matrice n*n
void matrixInit()
{
  //Righe
  mat = malloc(n * sizeof(char **));
  
  //Colonne
  for(int i = 0; i < n; i++)
  {
    mat[i] = malloc(n * sizeof(char *));
  }
}


//Riempe la matrice
void matrixFill()
{
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      //Numero casuale su cui baserò la mia scelta
      int h = rand() % 4 -1 ;
      printf("h = %d \n",h);
      
      //decidere cosa inserire
      switch(h)
      {
        case 0:
            mat[i][j] = "ciao";
            break;
        case 1:
            mat[i][j] = "ciao";
            break;
        case 2:
            mat[i][j] = "ciao";
        default:
            mat[i][j] = "ciao";
      }
      
    }
  }
}


//Ricerca un elemento nella propria riga
void elementFind(void * argc)
{
  int i = (int) argc;
  
  for(int j = 0; j < n; j++)
  {
     //La sleep l ho messa per renderlo realistico (senza funzionava a prescindere)
     if(i == 0 || i == 1 || i == 2)
     {
      sleep(1);
     }
      
    //ricerca dell'elemento
    //Blocco il mutex
    lock(&mutex);
    
    //Se qualcuno ha trovato l'elemento fermati
    if(trovato)
    {
      printf("Non l ho trovato io: %d x = %d , y = %d \n ",i,coordinate[0],coordinate[1]);
      unlock(&mutex);
      pthread_exit((void *) 1);
    }
    
    //Controllo stringa corrente
    if(strncmp(mat[i][j],el,strlen(el)) == 0)
    { 
      //Ho trovato l'elemento
      printf("Elemento trovato da %d \n",i);
      coordinate[0] = i;
      coordinate[1] = j;
      trovato = 1;
      
      //Rilascia il mutex ed esci
      unlock(&mutex);
      pthread_exit((void *) 1);
    }
    
    //Rilascio del mutex
    unlock(&mutex);
  }
  
  //Se non l'hai trovato e hai finito aspetta che venga trovato
  while(true)
  {
    if(trovato)
    {
      printf("Non l ho trovato io: %d x = %d , y = %d \n ",i,coordinate[0],coordinate[1]);
      pthread_exit((void *) 1);
    }
  }

}


int main(int argc, char *argv[])
{
  //Controllo degli argomenti passati da terminale
  if(argc < 3) err(" inserire size della matrice e elemento da cercare",-1);
  n = atoi(argv[1]);
  el = argv[2];
  pthread_t tid[n];
  
  
  //Allocazione e riempimento della matrice n*n
  matrixInit();
  matrixFill();
  matrixPrint();
  
  //Creazione dei thread
  for(int i = 0; i < n; i++)
  {
    pthread_create(&tid[i],NULL,&elementFind,(void *) i);
  }
  
  //Aspetto che i thread finiscano
  for(int i = 0; i < n; i++)
  {
    pthread_join(tid[i],NULL);
  }
  
  return 0;
}
