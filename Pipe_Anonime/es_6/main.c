/*
  Creato il 07/04/2025 alle ore 13:55
  La traccia è nella directory
  Stato: Da finire
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
//#include <pipes.h>
#define in STDIN_FILENO
#define out STDOUT_FILENO

int main(int argc, char *argv[])
{
  int fd[2],fd2[2];
  
  if(argc < 2)
  {
    printf("Miss an argument");
    exit(-1);
  }
  //Apertura delle pipe
  pipe(fd);
  pipe(fd2);
  
  //Esecuzione ls
  if(!fork())
  {
    //Chiusura descrittori
    close(fd[0]);
    close(fd2[0]);
    close(fd2[1]);
    
    //Chiusura stdout e sostituzione di quest'ultimo con descr pipe
    dup2(fd[1],out);
    close(fd[1]);
    
    //Esecuzione del comando ls
    execlp("ls","ls", (char *) NULL);
    perror("Errore esecuzione comando ls: ");
    exit(-1);
  }
  
  //Esecuzione grep <string> Es: r
  if(!fork())
  {
    //Chiusura descrittori
    close(fd[1]);
    close(fd2[0]);
    
    //gestione stdin e stdout
    dup2(fd[0],in);
    dup2(fd2[1],out);
    close(fd2[1]);
    close(fd[0]);
    
    //Esecuzione del comando grep <stringa>
    execlp("grep","grep",argv[1], (char *) NULL);
    perror("Errore esecuzione comando grep r: ");
    exit(-1);
  }
  
  //Esecuzione sort
  if(!fork())
  {
    //Chiusura descrittori
    close(fd[0]);
    close(fd[1]);
    close(fd2[1]);
    
    //Duplicazione stdin
    dup2(fd2[0],in);
    close(fd2[0]);
    
    //Esecuzione del comando sort -r
    execlp("sort","sort","-r", (char *) NULL);
    perror("Errore esecuzione comando sort -r: ");
    exit(-1);
  }
  
  //Chiusura descrittori
  close(fd[0]);
  close(fd[1]);
  close(fd2[0]);
  close(fd2[1]);
  
  //Attendo la terminazione dei processi (la sleep ha solo lo scopo di dare ordine alle prinft)
  sleep(1);  
  for(int i = 0; i < 3; i++)
  {
    printf("Aspetto la terminazione del mio brother: %d \n",i);
    wait(NULL);
    printf("Il mio brother ha finito: %d \n",i);
  }
}
