/*
Si scriva un programma in C sotto Linux che implementi
	la seguente pipeline di comandi SHELL:
	ls -la / | sort | tail -10 | wc -l
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#define out 1
#define in 0

int main(int argc, char **argv)
{
  int fd[2],fd1[2],fd2[2];
  pipe(fd);
  pipe(fd1);
  pipe(fd2);
  
  //ls -la /
  if(!fork())
  {
    //Chiusura descrittori inutilizzati
    close(fd[0]);
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    
    dup2(fd[1],out);
    close(fd[1]);
    execlp("ls","ls","-la","/",(char *) NULL);
    perror("comando ls -la fallito");
    return 0;
  }
  close(fd[1]);
  //sort
  if(!fork())
  {
    //Chiusura descrittori inutilizzati
    close(fd1[0]);
    close(fd2[0]);
    close(fd2[1]);
    
    dup2(fd[0],in);
    dup2(fd1[1],out);
    close(fd1[1]);
    close(fd[0]);
    execlp("sort","sort",(char *) NULL);
    perror("comando sort fallito");
    return 0;
  }
  
  close(fd1[1]);
  //tail -10
  if(!fork())
  {
    //Chiusura descrittori inutilizzati
    close(fd2[0]);
    
    dup2(fd1[0],in);
    dup2(fd2[1],out);
    close(fd2[1]);
    close(fd1[0]);
    
    execlp("tail","tail","-10",(char *) NULL);
    perror("comando tail fallito");
    return 0;
  }
  
  close(fd2[1]);
  
  //wc -l
  if(!fork())
  {
    
    dup2(fd2[0],in);
    close(fd2[0]);
    
    execlp("wc","wc","-l",(char *) NULL);
    perror("comando tail fallito");
    return 0;
  }
  
  sleep(5);
  for(int i = 0; i < 4; i++)
  {
    printf("Aspetto il figlio %d \n",i);
    wait();
  }
}
