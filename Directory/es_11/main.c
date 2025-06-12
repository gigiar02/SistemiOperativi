/*
  Scrivere un programma in C e Posix sotto linux che, presa in input una directory, 
  dopo averne analizzato il suo contenuto, identifichi il file di lunghezza minima 
  e ne stampi la maschera dei permessi relativa agli "altri".
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>
#define fsize 4500
#define inf (int) INFINITY
int main(int argc,char **argv)
{
  DIR *dir;
  struct dirent *file;
  struct stat st;
  
  dir = opendir(argv[1]);
  int min = inf;
  char *minFile = "";
  mode_t mask;
  while(file = readdir(dir))
  {
    char fullPath[fsize] = "";
    snprintf(fullPath,fsize,"%s/%s",argv[1],file->d_name);
    printf("Name = %s \n",fullPath);
    if(stat(fullPath,&st) != 0) {printf(" Errore stat"); return 0;}
    if(st.st_size < min)
    {
      min = st.st_size; 
      minFile = file->d_name; 
      mask = st.st_mode;
    }
  }
  mode_t w = mask & S_IWOTH;
  mode_t r = mask & S_IROTH;
  mode_t x = mask & S_IXOTH;
  printf("Il file di lunghezza minima è : %s  maschera permessi altri = %c%c%c \n",minFile,(mask & S_IROTH) ? 'r' : '-',
               (mask & S_IWOTH) ? 'w' : '-',
               (mask & S_IXOTH) ? 'x' : '-');
}
