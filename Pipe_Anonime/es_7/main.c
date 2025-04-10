/*
  Creato il 04/09/2025
  La traccia è nella directory
  
  NOTE:
  Il vettore fd è un vettore di descrittori pipe del tipo vector[4] = {0,1,0,1}.(gli 0 e 1 non sono i valori dell'array. Infatti lo 0 indica che si può leggere da quel descrittore e 1 che si può scrivere.) A riga 55 viene inizializzato
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#define SIZE 4500


//Stampa il messaggio di errore passato in input ed esci con -1
void err(char *text)
{
  perror(text);
  exit(-1);
}

//Stampa la matrice n*n passata in input
void matrixPrint(int **matrix,int n)
{
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      printf("%d\t",matrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc,char *argv[])
{
  int **matrix;
  int n;
  int sum = 0;
  pid_t father = getpid();
  
  
  //Controllo argomenti
  if(argc < 2) err("The program takes in input one argument ");
 
  n = atoi(argv[1]);
  
  //l' array fd avrà n-1 elementi e ogni elemento occupa uno spazio di dimensione 2. 
  int fd[(n-1)*2];
  
  //Inizializzazione pipe
  for(int i = 0; i <= (n-1)*2;i+=2)
  {
    pipe(&fd[i]);
    printf("v: %d v: %d \n",fd[i],fd[i+1]);
  }
  
  //Allocazione matrice
  matrix = malloc( n * sizeof(int *));
  for(int i = 0; i < n; i++)
  {
    matrix[i] = malloc(n * sizeof(int));
  }
  
  //L'utente sceglie i valori della matrice
  /*
  printf("Popola la matrice \n");
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      int value;
      printf("\n");
      scanf("%d",&value);
      printf("\ninput = %d \n",value);
      matrix[i][j] = value;
    }
  }
  */
  
  //Input senza tastiera
  int glob = 0;
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      int value;
      printf("\n");
      glob += 1;
      //printf("\ninput = %d \n",value);
      matrix[i][j] = glob;
    }
  }
  
  printf("\n");
  //Utilizzo di pipe per sommare N righe della matrice
  for(int i = 0; i < n; i++)
  {
    //Figlio
    if(fork() == 0)
    {
      //generazione id
      int id = i * 2;
      
      //Processo interno alla catena
      if(i > 0)
      {
        int sum_loc;
        char buff[SIZE];
        
        //Chiusura descrittori precedenti 
        for(int off = i-2; off > 0; off--)
        {
          //Chiudo tutti i descrittori che non utilizzerò
          int c_id = off * 2;
          close(fd[off]);
          close(fd[off+1]);
        }
        
        //Lettura della somma ottenuta
        read(fd[id-2],buff,SIZE);
        sum_loc = atoi(buff);
        close(fd[id-2]);
       
        //Calcolo della somma
        for(int j = 0; j < n; j++)
        {
          sum_loc += matrix[i][j];
        }
        
        //Scrittura del risultato locale
        sprintf(buff, "%d", sum_loc);
        write(fd[id + 1],buff,strlen(buff));
        close(fd[id+1]);
        
        //Processo all'inizio della catena
      }else if(i == 0) 
      {
        int sum_loc = 0;

        //Calcolo della somma locale
        for(int j = 0; j < n; j++)
        {
          sum_loc += matrix[i][j];
        }
        
        //Scrivo il risultato
        char buff[SIZE];
        sprintf(buff, "%d", sum_loc);
        write(fd[1],buff,sizeof(int));
        
        //Chiudo il descrittore
        close(fd[1]);
      } 
  }else
  {
    //printf("Sono il padre %d e ho finito \n",getpid());
    break;
  }
}


//Operazioni padre
if(getpid() == father)
{
    int globalSum = 0;
    char buff[SIZE];
    
    //Chiusura di tutti i descrittori
    for(int i = 0; i < (n-1)*2; i++)
    {
      if(i == (n-1)*2) continue;
      close(fd[i]);
    }
    
    //Chiusura descrittore inutilizzato
    int end = (n-1)*2 + 1;
    close(fd[end]);
    
    //Attende che i figli abbiano finito
    for(int i = 0; i < n; i++)
    {
      printf("Aspetto che %d abbia finito \n",i);
      wait(NULL);
      printf(" %d ha finito \n",i);
    }

    //Lettura del risultato
    read(fd[(n-1)*2],buff,SIZE);
    globalSum = atoi(buff);
    close(fd[(n-1)*2]);
    
    //Stampa del risultato e della matrice
    printf("Risultato = %d \n",globalSum);
    matrixPrint(matrix,n);
}
  
  return 0;
}
