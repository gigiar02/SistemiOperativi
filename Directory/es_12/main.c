/*
  Scrivere un programma C che stampi a video il contenuto di un file a byte alterni (ovvero un carattere sì ed uno no). Il nome del file viene passato come parametro su
  riga di comando.
  Esempio di esecuzione:
  $ ./a.out <nome_file.txt>
  Se <nome_file.txt> contiene la scritta "FORZA NAPOLI!" allora il programma scriverà.
  Output:
  FRANPL!

*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char **argv)
{
  if(argc != 2)
  {
    printf("Errore argc ");
    return 0;
  }
  
  int fd = open(argv[1],O_RDONLY);
  if(fd < 0){perror("apertura del file non andata a buon fine \n");}
  char c[1];
  int pos = 0;
  
  while(read(fd,c,sizeof(char)))
  {
    printf("%s",c);
    pos = lseek(fd,SEEK_CUR,1);
  }
  printf("\n");
  
  close(fd);
}
