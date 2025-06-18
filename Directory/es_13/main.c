/*
  Si realizzi un programma in C e Posix sotto Linux che preso come parametro da riga di comando una directory, analizzi tale
  directory e ne stampi il nome dei link simbolici e dei corrispondenti file puntati e per cui questi ultimi ne stampi anche il numero
  di hard link
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#define sizeBuff 4096


int main(int argc, char ** argv)
{
  if(argc != 2){printf("Errore argc \n"); return 0;}
  char *name = argv[1];
  DIR * directory = opendir(name);
  struct dirent *file;
  struct stat st;
  
  while(file = readdir(directory))
  {
    //Controllo se il file è un link simbolico
    char buff[sizeBuff] = "";
    char path[sizeBuff] = "";
    snprintf(path,sizeBuff,"%s/%s",argv[1],file->d_name);
    if(lstat(path,&st) != 0){perror("Errore stat: "); return 0;}
    if(S_ISLNK(st.st_mode))
    {
      //Stampo il file puntato
      if(readlink(path,buff,sizeBuff)){printf("lettura andata a buon fine: %s \n",buff);}
      char filePath[sizeBuff] = "";
      snprintf(filePath,sizeBuff + 1,"%s/%s",argv[1],buff);
      if(stat(buff,&st) != 0){perror("Errore fstat; "); return 0;}
      int numh = st.st_nlink;
      printf("%s -> %s :  %d \n",file->d_name,buff,numh);
      
    }
  }

}
