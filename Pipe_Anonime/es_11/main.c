/*
scrivere un programma che esegua il comando di
shell “ls- R | grep <pat>” dove <pat> è un pattern inserito
dall’utente.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char **argv)
{
  int fd[2],fd1[2],fd2[2];
  pipe(fd);
  
  if(argc != 2){printf("Errore argc"); return 0;}
  
  //ls - R
  if(!fork())
  {
    close(fd[0]);
    
    dup2(fd[1],1);
    close(fd[1]);
    execlp("ls","ls","-R",(char *) NULL);
    exit(0);
  }
  
  close(fd[1]);
  //grep <path>
  if(!fork())
  {
    
    dup2(fd[0],0);
    close(fd[0]);
    execlp("grep","grep",argv[1],(char *) NULL);
    exit(0);
    
  }
  close(fd[0]);
  
  for(int i = 0; i < 2; i++)
  {
    wait(NULL);
  }

}
