/*
  Creato il 28/04/2025 orario: 11:28
  traccia nella directory
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#define SIZEBUFF 4500

//In input prende il nome della directory e il nome del file da creare
int main(int argc,char **argv)
{
  DIR *directory;
  struct dirent *file;
  struct stat info;
  int fd;
  
  //Controllo argomenti,apertura directory e creazione file
  if(argc != 3) return 1;
  directory = opendir(argv[1]);
  fd = open(argv[2],O_CREAT | O_WRONLY,S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if(fd < 0) return 5;
  
  //Lettura directory
  while(file = readdir(directory))
  {
    //Prendo il numero di hardlink
    if(stat(file->d_name,&info) != 0) return 2;
    int hardLinks = info.st_nlink;
    char nlink[SIZEBUFF];
    sprintf(nlink,"%d",hardLinks);
    printf(" name = %s numero di hardLink = %s \n",file->d_name,nlink);
    
    //Scrittura del numero di hardLink all'interno del file
    char *buff = file->d_name;
    strcat(buff," ");
    write(fd,buff,strlen(buff));
    write(fd,nlink,strlen(nlink));
    write(fd,"\n",strlen("\n"));
  }
  
  close(fd);
}
