/*
  Si realizzi un programma in C e Posix sotto Linux che data una directory da riga di comando, 
  ne elenchi il contenuto e, individuati i link simbolici, 
  indichi se il file puntato ha i diritti di scrittura per il proprietario e per gruppo e stampi la dimensione.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#define fsize 4500
int main(int argc,char **argv)
{
  DIR *directory;
  struct dirent *file;
  struct stat st;
  
  if(argc != 2)
  {
    printf("Errore argc \n");
    return 0;
  }
  
  printf("Elenco il contenuto della directory \n");
  directory = opendir(argv[1]);
  while(file = readdir(directory))
  {
    //Stampa nome file
    char fullpath[fsize] = "";
    snprintf(fullpath,fsize,"%s/%s",argv[1],file->d_name);
    printf("name : %s \n",fullpath);
    
    //Vedo se il file è un link simbolico
    if(lstat(fullpath,&st) < 0){perror("Errore fstat"); return 0;}
    if(S_ISLNK(st.st_mode))
    {
      printf("il file è un link simbolico. \n");
      char buff[fsize] = "";
      readlink(fullpath,buff,fsize);
      printf("Contenuto: %s \n",buff);
      
      //Indico se il file puntato hai diritti di scrittura per il proprietario
      if(stat(buff,&st) < 0){perror("Errore fstat"); return 0;}
      if((st.st_mode & S_IWGRP) && (st.st_mode & S_IWUSR))
      {
        printf("Il gruppo e il proprietario hanno i diritti di scrittura \n");
        printf("Dimensione = %ld \n",st.st_size);
      }

    }
    
    
  }
  
}
