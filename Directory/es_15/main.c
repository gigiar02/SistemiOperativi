/*
  Scrivere un programma in C che, in ambiente Linux, presa una directory come parametro da riga di comando,
     * provvederà a scorrerla allo scopo di stampare i nomi di tutti i file regolari e le loro dimensioni contenuti in tale
     * directory se questi hanno i diritti di scrittura e lettura per il proprietario e per gli altri.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#define s 4096

int main(int argc,char **argv)
{
  if(argc != 2){printf("Errore argc "); return 0;}
  DIR* dir = opendir(argv[1]);
  struct dirent *file;
  struct stat st;
  
  while(file = readdir(dir))
  {
    char path[s] = "";
    snprintf(path,s,"%s/%s",argv[1],file->d_name);
    if(stat(path,&st) != 0){printf("Errore stat"); return 0;}
    
    if((S_ISREG(st.st_mode)) && (S_IRUSR & st.st_mode) && (S_IWUSR & st.st_mode) && (S_IROTH & st.st_mode) && (S_IWOTH & st.st_mode))
    {
      printf("name: %s dimensione = %ld \n",file->d_name,st.st_size);
    }
  
  }
}
