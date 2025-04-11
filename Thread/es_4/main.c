

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>

#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock

//Insieme di directory
 DIR **directories;
 char **paths;
 pthread_mutex_t mutex;
 int n;  
 int max_size = 0;
 char *name;
 char *path;
 int id = -1;
 
void directoryRead(void * arg)
{
  int i = (int) arg;
  struct dirent *file;
  printf("i = %d \n",(int) arg);
  
  while(file = readdir(directories[i]))
  {
    //Esclusione file non validi
    if(strncmp(file->d_name,".",1) == 0 || strncmp(file->d_name,"..",2) == 0 ) continue;
    
    int pathSize = strlen(paths[i+1]) + strlen(file->d_name) + 1;
    char *pathName = malloc(pathSize * sizeof(char));
    off_t  size;
    struct stat st;
    
    //Creazione del percorso
    strcat(pathName,paths[i+1]);
    strcat(pathName,"/");
    strcat(pathName,file->d_name);
    
    //ricavo size del file
    if(stat(pathName,&st) < 0) return;
    size = st.st_size;
    
    //Sezione Critica
    lock(&mutex);
    
    //Verifico se il file che ho trovato è il piu grande
    if(max_size < size) {max_size = size; name = file->d_name; path = pathName; id = i;}
  
    //Sblocco il mutex
    unlock(&mutex);
    
    //Libero lo spazio
    printf("size = %ld name = %s \n",size,pathName);
    free(pathName);
  }
}


int main(int argc,char *argv[])
{
  //Controllo argomenti
  if(argc < 2) return -1;
  paths = argv;
  
  //Inizializzazione lista directory
  n = argc - 1;
  pthread_t tid[n];
  directories = calloc(sizeof(DIR*),n * sizeof(DIR*));
  if(!directories) return -2;
  
  //Apri tutte le directory
  for(int i = 1; i <= n; i++)
  {
    //test per vedere se la directory può essere aperta e apertura in caso di successo
    if(access(argv[i],R_OK) != 0) printf("Non puoi leggere dalla directory [%d] name = %s ",i,argv[i]);
    directories[i-1] = opendir(argv[i]);
    if(!directories[i-1]) return i;
  }
  
  //Creazione dei thread
  for(int i = 0; i < n; i++)
  {
    pthread_create(&tid[i],NULL,&directoryRead,(void *) i);
  }
  
  //Terminazione thread
  sleep(5);
  for(int i = 0; i < n; i++)
  {
    printf("aspetto %d \n",i);
    pthread_join(tid[i],NULL);
    printf("fine %d \n",i);
  }
  
  //Stampa del File piu grande
  printf(" nome = %s path = %s size = %d index = %d \n",name,path,max_size,id);

  return 0;
}
