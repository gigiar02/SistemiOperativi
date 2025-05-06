/*
  Data di creazione: 6/05/2025 orario: 15:49
  Scorrere una directory e stampare il contenuto dei file su cui il gruppo e gli altri hanno permessi di scrittura
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#define Size 4500

int main(int argc,char **argv)
{
  DIR* directory;
  struct dirent* file;
  struct stat st;
  char buff[4500];
  
  //Apertura directory corrente
  char *currentDirectory = getcwd(buff,Size);
  directory = opendir(currentDirectory);
  if(!directory){printf("Errore nell'apertura della directory"); return -1;}
  
  while(file = readdir(directory))
  {
    printf("Nome = %s \n",file->d_name);
    //stat.st_mode contiene i permessi di accesso sul file
    if(stat(file->d_name,&st) != 0){printf("Errore stat file "); return -1;}
    printf("stampo il campo st_mode %o \n",st.st_mode);
    
    //Controllo di avere i permessi in lettura e che il gruppo e gli altri possano scrivere
    if((S_IRUSR & st.st_mode) && (S_IWGRP & st.st_mode) && (S_IWOTH & st.st_mode))
    {
      printf("Posso leggere, il gruppo può scrivere e gli altri possono scrivere \n");
      
      //Apro il file e ne scrivo il contenuto
      int fd;
      if((fd = open(file->d_name,O_RDONLY)) > 0)
      {
        char buff[Size];
        read(fd,buff,Size);
        printf("Stampo il contenuto del file \n %s",buff);
      }
    } 
  }

  
  
  
}

