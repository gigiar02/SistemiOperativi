/*
  Creato il 04/09/2025
  La traccia è nella directory
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
      printf(" %d ",matrix[i][j]);
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
  
  //Creazione pipe
  
  
  //Allocazione della matrice n*n
  n = atoi(argv[1]);
  int fd[(n-1)*2];
  
  //Inizializzazione pipe
  for(int i = 0; i <= (n-1)*2;i+=2)
  {
    pipe(&fd[i]);
    printf("v: %d v: %d \n",fd[i],fd[i+1]);
  }
  
  matrix = malloc( n * sizeof(int *));
  for(int i = 0; i < n; i++)
  {
    matrix[i] = malloc(n * sizeof(int));
  }
  
  //L'utente sceglie i valori della matrice
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
  
  //Utilizzo di pipe per sommare N righe della matrice
  for(int i = 0; i < n; i++)
  {
    //Figlio
    if(fork() == 0)
    {
      //generazione id
      int id = i * 2;
      printf("id = %d i = %d 87 \n",id,i);
      
      //Processo interno alla catena
      if(i > 0)
      {
        
        //Chiudo descrittore per scrivere
        close(fd[id-1]);
        close(fd[id]);
        
        //Chiusura descrittori precedenti 
        for(int off = i-2; off > 0; off--)
        {
          //Chiudo tutti i descrittori che non utilizzerò
          int c_id = off * 2;
          close(fd[off]);
          close(fd[off+1]);
        }
        
        //Chiusura descrittori successivi
        for(int succ = i + 1; succ < n; succ++)
        {
          int c_id = succ * 2;
          close(fd[c_id]);
          close(fd[c_id + 1]);
        }
        
        
        //Calcolo somma locale
        int sum_loc;
        char buff[SIZE];
        read(fd[id-2],buff,SIZE);
        sum_loc = atoi(buff);
        close(fd[id-2]);
        printf("somma [%d] = %d \n",i,sum_loc);
        
        for(int j = 0; j < n; j++)
        {
          sum_loc += matrix[i][j];
        }
        printf("somma [%d] = %d \n",i,sum_loc);
        
        //Scrittura del risultato locale
        sprintf(buff, "%d", sum_loc);
        write(fd[id + 1],buff,strlen(buff));
        close(fd[id+1]);
      }
      //Processo all'inizio della catena
      else if(i == 0)
      {
        printf("id = %d i = %d 135 \n",id,i);
        //Non mi servirà leggere
        close(fd[0]);
        
        //Chiusura descrittori inutilizzati (1 mi serve per scrivere)
        for(int succ = 1; succ < n-1; succ++)
        {
          int c_id = succ * 2;
          close(fd[c_id]);
          close(fd[c_id+1]);
        }
        
        printf("id = %d i = %d 147 \n",id,i);
        //Calcolo della somma locale
        int sum_loc = 0;
        printf("somma [%d] = %d \n",i,sum_loc);
        for(int j = 0; j < n; j++)
        {
          sum_loc += matrix[i][j];
        }
        printf("somma [%d] = %d \n",i,sum_loc);
        char buff[SIZE];
        sprintf(buff, "%d", sum_loc);
        write(fd[1],buff,strlen(buff));
        close(fd[1]);
        
      }
    else
    {
      break;
    }
  }
  
  
  
  
}
//Operazioni padre
if(getpid() == father)
  {
    for(int i = 0; i < (n-1)*2; i++)
    {
      if(i == (n-1)*2) continue;
      close(fd[i]);
    }
    
    //Attende che i figli abbiano finito
    sleep(1);
    for(int i = 0; i < n; i++)
    {
      printf("Aspetto che %d abbia finito \n",i);
      wait(NULL);
      printf(" %d ha finito \n",i);
    }
    
    //Legge il risultato
    int globalSum = 0;
    char buff[SIZE];
    read(fd[(n-1)*2],buff,SIZE);
    globalSum = atoi(buff);
    close(fd[(n-1)*2]);
    
    printf("Risultato = %d \n",globalSum);
    
    //Stampa della matrice
    matrixPrint(matrix,n);
  }
}
