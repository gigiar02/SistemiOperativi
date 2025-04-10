/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#define buff 4500


void err(char* name,int status,bool p)
{
  if(!p) printf("Errore %s \n",name);
  if(p)  perror(name);
  
  exit(status);
}


//Assume di dover accorciare fd1
void riduciSize(FILE* file1,FILE* file2)
{
  int row1 = 0;
  int row2 = 0;
  char *line1;
  char *line2;
  char buffer[buff];
  int fd;
  int app = open("appoggio.txt",O_CREAT | O_TRUNC | O_WRONLY | O_RDONLY, S_IRUSR | S_IWUSR | S_IXUSR);
  if(!app) err(" appoggio.txt ",-3,true);
  
  //Scrivi nel file di appoggio
  while(fgets(line1,buff,file1))
  {
    if(fgets(line2,buff,file2))
    {
      write(app,line1,strlen(line1));
      row2++;
    }
    row1++;
  }
  
  //Chiudi file1 per poi riaprirlo in modo da cancellarne il contenuto
  fclose(file1);
  fd = open("file1.txt",O_TRUNC | O_WRONLY);
  lseek(app,0,SEEK_SET);
  
  //Sovrascrivi file1 con la sua copia
  read(app,buffer,buff);
  write(fd,buffer,strlen(buffer));
  close(app);
  close(fd);
}


int main(int argc, char* argv[])
{
  FILE* file1;
  FILE* file2;
  int size1,size2;
  
  //Controllo argomenti
  if(argc < 3) err(" passare file1 e file2 come argomenti",-1,false); 
  
  //Apertura dei file e controllo di eventuali errori
  file1 = fopen(argv[1],"rw");
  file2 = fopen(argv[2],"rw");
  if(!file1 || !file2 ) err(" apartura dei file non andata a buon fine",-2,true);
  
  //Calcolo del size dei due file e mi riposiziono nuovamente all'inizio
  size1 = fseek(file1,0L,SEEK_END); size2 = fseek(file2,0L,SEEK_END);
  size1 = ftell(file1);                size2 = ftell(file2);
  fseek(file1,0,SEEK_SET);         fseek(file2,0,SEEK_SET); 
  printf("size1 = %d size2 = %d \n",size1,size2);
  
  //Confronto del size dei due file
  if(size1 > size2)
  {
    printf("Il file1 è piu grande \n");
    
    //Scelta dell'utente
    while(true)
    {
      int scelta;
      
      //Stampa menu
      printf("Scegli ciò che vuoi fare: \n");
      printf(" 0 - Riduci size del file1 \n");
      printf(" 1 - Elimina le righe 1 e 4 del file 1 \n");
      printf(" 2 - Elimina qualsiasi 'domani' \n");
      
      //Aspetta la scelta da parte dell'utente
      scanf("%d",&scelta);
      
      switch(scelta)
      {
        case 0: 
          riduciSize(file1,file2);
          break;
      }
    }
    
  }else
    printf("Il file2 è piu grande \n");

  return 0;
}
