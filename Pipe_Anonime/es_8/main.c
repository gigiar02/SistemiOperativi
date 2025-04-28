/*
  Creato il 28/04/2025 orario: 09:42
  Esercizio nella directory
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

#define in STDIN_FILENO
#define out STDOUT_FILENO

//In input riceve dir e nomeFile
int main(int argc, char **argv)
{
  //Dati
  int fd[2],fd1[2],fd2[2];
  //Controllo argomenti e apertura pipe
  if(argc != 3) return 1;
  pipe(fd);
  pipe(fd1);
  pipe(fd2);
  
  //Esecuzione ls -R <directory>
  if(!fork())
  {
    //Chiusura descrittori inutilizzati
    close(fd[0]);
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    
    //Duplicazione del descrittore
    dup2(fd[1],out);
    close(fd[1]);
    
    //Esecuzione comando
    execlp("ls","ls","-R",argv[1],(char *) NULL);
    
    perror("Esecuzione del comando ls - R <directory> non riuscita");
    exit(2);
  }
  //Chiusura descrittori
  close(fd[1]);
  
  //Esecuzione grep
  if(!fork())
  {
    //Chiusura descrittori inutilizzati
    close(fd1[0]);
    close(fd2[0]);
    close(fd2[1]);
    
    //Duplicazione del descrittore
    dup2(fd[0],in);
    dup2(fd1[1],out);
    close(fd1[1]);
    close(fd[0]);
    
    //Esecuzione comando
    execlp("grep","grep",argv[2],(char *) NULL);
    
    perror("Esecuzione del comando grep non riuscita");
    exit(3);
  }
  
  //Chiusura descrittori
  close(fd1[1]);
  close(fd[0]);
  
  //Esecuzione uniq
  if(!fork())
  {
    //Chiusura descrittori inutilizzati
    close(fd2[0]);
    
    //Duplicazione del descrittore
    dup2(fd1[0],in);
    dup2(fd2[1],out);
    close(fd1[0]);
    close(fd2[1]);
    
    //Esecuzione comando
    execlp("uniq","uniq",(char *) NULL);
    
    perror("Esecuzione del comando uniq non riuscita");
    exit(4);
  }
  
  //Chiusura descrittori
  close(fd2[1]);
  close(fd1[0]);
  
  //Esecuzione cat
  if(!fork())
  {
    //Duplicazione del descrittore
    dup2(fd2[0],in);
    close(fd2[0]);
    
    //Esecuzione comando
    execlp("cat","cat",(char *) NULL);
    
    perror("Esecuzione del comando cat non riuscita");
    exit(5);
  }
  //Chiusura descrittori
  close(fd2[0]);
  
  //Aspetto che i figli abbiano finito
  sleep(1);
  for(int i = 0; i < 4; i++)
  {
    printf("Aspetto figlio %d \n",i);
    int exitStatus;
    wait(&exitStatus);
    exitStatus = WEXITSTATUS(exitStatus);
    printf("figlio uscito con stato %d \n",exitStatus);
  }
  return 0;
}

