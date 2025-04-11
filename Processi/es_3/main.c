/*
  Data Creazione: 11/04/2025 alle ore 14:49
  La traccia è nella directory
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <dirent.h>
#include <pthread.h>
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock

//Globali
char **arguments;


int readDirectory(int i,int fd2)
{
  DIR* dir;
  struct dirent* file;
  int max = 0;
  
  //Controllo se posso aprire la directory
  if(access(arguments[i],R_OK) < 0) return -1;
  
  //Apri la directory
  dir = opendir(arguments[i]);
  
  //Lettura directory
  while(file = readdir(dir))
  {
    //File non accettati
    if(strncmp(".",file->d_name,1) == 0 || strncmp("..",file->d_name,2) == 0) continue;
    
    struct stat st;
    int   pathSize = strlen(arguments[i]) + strlen(file->d_name) + 1;
    int   size;
    off_t tsize;
    char *pathName = malloc(pathSize * sizeof(char));
    
    //Concatenazione nome path + nome file
    pathName[0] = '\0';
    strcat(pathName,arguments[i]);
    strcat(pathName,"/");
    strcat(pathName,file->d_name);
    
    //size file
    if(stat(pathName,&st) < 0) perror("Errore stat");
    tsize = st.st_size;
    size = tsize;
    
    //Aggiorno il massimo
    max = max < size ? size : max; 
    printf("i = %d name = %s max size = %d \n",i,pathName,size);
    
    //Libero memoria
    free(pathName);
  }
    
  //Scrivi il risultato
  char buffer[255];
  sprintf(buffer,"%d",max);
  write(fd2,buffer,strlen(buffer));
  close(fd2);

  return max;
}


int main(int argc, char *argv[])
{
  int n;
  pid_t father = getpid();
  
  //Verifico gli argomenti passati
  if(argc < 2) return -2;
  n = argc - 1;
  pid_t pid[n];
  arguments = argv;
  int value[n];
  
  //Creazione processi
  for(int i = 1; i <= n; i++)
  {
    //Crea la pipe per comunicare con il figlio
    int fd2[2];
    char buffer[255];
    pipe(fd2);
    
    //FIGLIO
    if(fork() == 0)
    {
      //Chiudo descrittori inutilizzati
      close(fd2[0]);
      
      //Ricavo il risultato
      pid[i-1] = getpid();
      int res = readDirectory(i,fd2[1]);
      printf("res = %d \n",res);
      
      exit(1);
    }
    
    //PADRE: il figlio è uscito chiamando exit
    
    //Leggo il risultato
    close(fd2[1]);
    read(fd2[0],buffer,sizeof(buffer));
    close(fd2[0]);
    value[i-1] = atoi(buffer);
    printf("Value = %d \n",value[i-1]);
    
    //Reset valori
    fd2[0] = 0; fd2[1] = 0;
  }
  
  //Terminazione processi figli
  int max = 0;
  
  if(father == getpid())
  {
    sleep(1);
    for(int i = 0; i < n; i++)
    {
      int status;
      waitpid(pid[i],&status,0);
      printf("status [%d] = %d \n",pid[i],WEXITSTATUS(status));
    }
  }
  
  //Stampa
  for(int i = 0; i < n; i++)
  {
    printf(" value[%d] = %d ",i,value[i]);
    
    max = max < value[i] ? value[i] : max;
  }
  
  //Restituisco il massimo
  printf(" \n MAX = %d \n",max);
  return 0;
}
