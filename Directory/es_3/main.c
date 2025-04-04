/*
   Creato il 03/04/2025
   La traccia è nella directory

*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>
#include <dirent.h>



#define PATHMAX 4500


//Controlla se un file è un eseguibile valido
int isExecutable(char *file)
{
    //Controllo che l'eseguibile non sia "a" "." ".."
    if(strncmp(file,"a",1) == 0) return 0;
    if(strncmp(file,".",1) == 0) return 0;
    if(strncmp(file,"..",1) == 0) return 0;
    
    //Se la access va a buon fine è un eseguibile
    if(access(file,X_OK) == 0) return 1;
    
    return 0;
}


int main()
{
  char path[PATHMAX];
  struct dir *dir;
  struct dirent *currentFile;
  struct stat  buff; 
  int j = 0; //Numero di processi da aspettare


  //ottengo la directory corrente
  char *res = getcwd(path,sizeof(path));
  if(res == NULL) return -1;
	
  //Apro la directory
  dir = opendir(path);
  if(dir == NULL) return -1;

  //Scorro tutti i file all'interno della mia directory
  while(currentFile = readdir(dir))
  {
    //Prendo le informazioni sul file
    if(stat(currentFile->d_name,&buff) != 0 || !isExecutable(currentFile->d_name)) {continue;}
    
    //Verifico che gli altri abbiano il permesso di eseguire il file
    if(buff.st_mode & S_IXOTH)
    {
      printf("File : %s Permesso di esecuzione OK \n",currentFile->d_name);

      //Il figlio esegue il file
      j++;
      if(fork() == 0)
      {
        char *name = currentFile->d_name;
        execl(name,name,(char *) NULL);
        perror("execl: ");
	exit(10);
      }
    }	

  }
  
  //Controlla che tutti i processi figli abbiano finito prima di uscire
  sleep(1);
  for(int i = 0; i < j; i++)
  {
      printf("Aspetto processo %d \n",i);
      wait(NULL);
      printf("Attesa finita %d \n",i);
  }
  return 0;
}
