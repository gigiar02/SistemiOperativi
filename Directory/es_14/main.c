/*
  Si realizzi un programma in C e Posix sotto Linux che data una directory da riga di comando, ne elenchi il
  contenuto e, individuati i link simbolici, stampi i nomi dei file puntati, la dimensione e se hanno il bit set-user id
  impostato.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#define sizeBuff 4096

int main(int argc,char **argv)
{
  DIR * dir;
  struct dirent *file;
  struct stat st;
  int setud = 0;
  
  if(argc != 2){printf("Errore argc"); return 0;}
  
  dir = opendir(argv[1]);
  while(file = readdir(dir))
  {
    char path[sizeBuff] = "";
    char buff[sizeBuff] = "";
    int dim = 0;
    int lnk = 0;
    
    snprintf(path,sizeBuff,"%s/%s",argv[1],file->d_name);
    if(lstat(path,&st) != 0){printf(" Errore lstat"); return 0;}
    if(S_ISLNK(st.st_mode))
    {
      lnk = 1;
      readlink(path,buff,sizeBuff);
      printf("buff : %s \n",buff);
      char filePath[sizeBuff] = "";
      snprintf(filePath,sizeBuff + 1,"%s/%s",argv[1],buff);
      if(stat(filePath,&st) != 0){printf(" Errore stat"); return 0;}
      dim = st.st_size;
      if(st.st_mode & S_ISUID){setud = 1;}

    }
    printf("Nome: %s LINK SIMBOLICO: %s FILE PUNTATO: %s  BYTE: %d SETUD = %d \n",file->d_name, lnk ? "si" : "no",buff,dim,setud);
  }

}
