/*
  Creato il 07/04/2025 alle ore 13:55
  La traccia è nella directory
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <pipe.h>
#define in STDIN_FILENO
#define out SDOUT_FILENO

int main()
{
  int fd[2],fd2[2];
  
  //Apertura delle pipe
  pipe(fd);
  pipe(fd2);
  
  //Esecuzione ls
  if(!fork())
  {
    //Chiudo i descrittori inutilizzati
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
  
  //Esecuzione comando grep <string> Es: r
  if(!fork())
  {
    //Chiusura descrittori
    close(fd[1]);
    close(fd2[0]);
    
    //gestione stdin e stdout
    dup2(fd[0],in);
    dup2(fd2[1],out);
    
    //Esecuzione del comando grep <stringa>
    execlp("grep","grep","r", (char *) NULL);
    perror("Errore esecuzione comando grep r: ");
    exit(-1);
  }
  

}
