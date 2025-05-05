/*
  Creato il 05/05/2025 orario 11:30
  La traccia è nella directory
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#define in STDIN_FILENO
#define out STDOUT_FILENO


int main(int argc,char **argv)
{
  int fd[2],fd2[2];
  pipe(fd);
  pipe(fd2);
  
  //size -t a.out
  if(!fork())
  {
    //Chiusura descrittori inutilizzati
    close(fd[0]);
    close(fd2[0]);
    close(fd2[1]);
    
    //Esecuzione comando
    dup2(fd[1],out);
    close(fd[1]);
    execlp("size","size","-t","a.out",(char *) NULL);
    printf("Errore nell'utilizzo di size");
    exit(1);
  }
  close(fd[1]);
  
  //grep bss
  if(!fork())
  {
    //Chiusura descrittori inutilizzati
    close(fd2[0]);
    
    //Esecuzione comando
    dup2(fd[0],in);
    dup2(fd2[1],out);
    close(fd2[1]);
    close(fd[0]);
    execlp("grep","grep","bss",(char *) NULL);
    printf("Errore nell'utilizzo di bss");
    exit(1);
  }
  
  close(fd2[1]);
  close(fd[0]);
  
  //wc -c
  if(!fork())
  {
    //Esecuzione comando
    dup2(fd2[0],in);
    close(fd2[0]);
    execlp("wc","wc","-c",(char *) NULL);
    printf("Errore nell'utilizzo di wc");
    exit(1);
  }
  
  close(fd2[0]);
  
  sleep(1);
  for(int i = 0; i < 3; i++)
  {
    printf("Aspetto %d \n",i);
    int status;
    wait(&status);
    status = WEXITSTATUS(status);
    printf("Uscito %d con stato = %d \n",i,status);
  }
  
  return 0;
}
