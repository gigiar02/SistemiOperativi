/*
  Cerca i link simbolici all'interno della directory e leggine il contenuto
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#define Size 4500

int main(int argc,char **argv)
{
  DIR* directory;
  struct dirent *file;
  struct stat st;
  
  directory = opendir(".");
  
  while(file = readdir(directory))
  {
    if(lstat(file->d_name,&st) != 0){printf("Il file non è un link simbolico %s \n",file->d_name); continue;}
    if(!S_ISLNK(st.st_mode)) continue;
    char *buff = malloc(sizeof(int) * Size);
    readlink(file->d_name,buff,Size);
    printf("Stampo il contenuto del file %s \n %s \n",file->d_name,buff);
    free(buff);
  }
}
