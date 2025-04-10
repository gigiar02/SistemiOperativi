/*
    Creato il 04/10/2025 alle ore 14:05
    La traccia è nella directory
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
void riduciSize(char *argv[])
{
  FILE* file1;
  FILE* file2;
  
  char line1[buff];
  char line2[buff];
  char buffer[buff];
  int fd;
  
   //Apertura dei file e controllo di eventuali errori
  int app = open("appoggio.txt",O_CREAT | O_TRUNC | O_WRONLY | O_RDONLY, S_IRUSR | S_IWUSR | S_IXUSR);
  if(!app) err(" appoggio.txt ",-3,true);
  printf("arg[1] = %s e argv[2] = %s \n",argv[1],argv[2]);
  file1 = fopen(argv[1],"r+");
  file2 = fopen(argv[2],"r+");
  printf("42 \n");
  if(!file1 || !file2 ) { printf("qui"); err(" apertura dei file ",-1,false);}
  
  fseek(file1,0L,SEEK_SET);
  fseek(file2,0L,SEEK_SET);
  //Scrivi nel file di appoggio
  
  
  while(fgets(line1,buff,file1))
  {
    
    if(fgets(line2,buff,file2))
    {
      write(app,line1,strlen(line1));
      printf("write \n");
    }else
    {
      break;
    }
    
  }
  
  printf("56");
  
  //Chiudi file1 per poi riaprirlo in modo da cancellarne il contenuto
  fclose(file1);
  close(app);
  
  app = open("appoggio.txt", O_RDONLY);
  fd = open("file1.txt",O_TRUNC | O_WRONLY);
  if(!fd) err(" apertura file1.txt non andata a buon fine",-4,true);
  printf("63");
  //Sovrascrivi file1 con la sua copia
  read(app,buffer,buff);
  printf("ho letto %s \n",buffer);
  write(fd,buffer,strlen(buffer));
  
  close(app);
  close(fd);
  printf("70 \n");
  
}

//Calcola il size dei file
void calcolaSize(int *size1,int *size2, char *argv[])
{
  FILE* file1;
  FILE* file2;
  
  //Apertura file
  file1 = fopen(argv[1],"r+");
  file2 = fopen(argv[2],"r+");
  if(!file1 || !file2 ) {err(" apartura dei file non andata a buon fine",-2,true);}
  
  //Calcolo size
  *size1 = fseek(file1,0L,SEEK_END); *size2 = fseek(file2,0L,SEEK_END);
  *size1 = ftell(file1);                *size2 = ftell(file2);
  fseek(file1,0,SEEK_SET);         fseek(file2,0,SEEK_SET); 
  printf("size1 = %d size2 = %d \n",*size1,*size2);
  
  //Chiusura file
  fclose(file1);
  fclose(file2);
  
}


//Elimina le righe 1 e 4 del primo file
void rowDelete(char *argv[])
{
  FILE* file1;
  int fd,fd2,i;
  char buffer[buff];
  
  //Aperture del file1 e appoggio
  i = 0;
  file1 = fopen(argv[1],"r+");
  fd = open("appoggio.txt",O_CREAT | O_TRUNC | O_WRONLY | O_RDONLY, S_IRUSR | S_IWUSR | S_IXUSR);
  
  //Scrittura nel file di appoggio
  while(fgets(buffer,buff,file1))
  {
    i++;
    if(i == 1 || i == 4) continue;
    write(fd,buffer,strlen(buffer));
  }
  
  //Sovrascrittura
  close(fd);
  fd = open("appoggio.txt",O_RDONLY);
  fd2 = open(argv[1],O_TRUNC | O_WRONLY);
  read(fd,buffer,buff);
  write(fd2,buffer,strlen(buffer));
}


//Elimina tutte le parole contenenti la parolina magica
void niggerDelete(char *argv[])
{
  int file1;
  int fd,fd2,i;
  char buffer[buff];
  
  //Aperture del file1 e appoggio
  i = 0;
  file1 = open(argv[1],O_RDONLY);
  fd = open("appoggio.txt",O_CREAT | O_TRUNC | O_WRONLY | O_RDONLY, S_IRUSR | S_IWUSR | S_IXUSR);
  
  //Lettura da file1
  read(file1,buffer,buff);
  char parola[buff];
  while(buffer[i] != '\0')
  {
    int j = 0;
    char carattere;
    while(buffer[i] != '\n' && buffer[i] != ' ' && buffer[i] != '\0')
    {
      parola[j] = buffer[i];
      i+=1;
      j+=1;
    }
    
    if(buffer[i] != '\0')
    {
      parola[j] = buffer[i];
      printf("parola = %s   i = %d j = %d \n",parola,i,j);  
      
      //Controlla la parola
      if(strncmp("nigger",parola,6) == 0 || strncmp("nigger\n",parola,8) == 0 || strncmp("\nnigger\n",parola,10) == 0 || strncmp("\nnigger",parola,8) == 0)
      {
        char name[buff];
        name[0] = 'n'; name[1] = 'e'; name[2] = 'r'; name[3] = 'o';
        name[4] = buffer[i];
        write(fd,name,strlen(name));
        
      }else
      {
        write(fd,parola,strlen(parola));
      }
      //Resetta la parola
      memset(parola,'\0',buff);
       i+=1;
       j+=1;
    }else
    {
      buffer[i] = '\0'; 
      break;
    }
    
  }
  printf("fine = %d\n",i);
  
  //Chiusura
  close(file1);
  close(fd);
  
  //Sovrascrittura
  
  file1 = open(argv[1],O_TRUNC | O_WRONLY);
  fd = open("appoggio.txt",O_RDONLY);
  read(fd,buffer,buff);
  write(file1,buffer,strlen(buffer));
  close(fd);
  close(file1);
  
}


int main(int argc, char* argv[])
{ 
  int size1,size2;
  
  //Controllo argomenti
  if(argc < 3) err(" passare file1 e file2 come argomenti",-1,false); 
  
  //Calcolo del size dei due file
  calcolaSize(&size1,&size2,argv);
  
  //Confronto del size dei due file
  if(size1 > size2)
  {
    printf("Il file1 è piu grande \n");
    
    //Scelta dell'utente
    int scelta;
    while(true)
    {
      
      
      //Stampa menu
      printf("Scegli ciò che vuoi fare: \n");
      printf(" 0 - Riduci size del file1 \n");
      printf(" 1 - Elimina le righe 1 e 4 del file 1 \n");
      printf(" 2 - Elimina qualsiasi 'domani (modificato)' \n");
      
      //Aspetta la scelta da parte dell'utente
      scanf("%d",&scelta);
      printf("Scelta = %d \n",scelta);
      switch(scelta)
      {
        case 0: 
          printf("Carico la scelta \n");
          riduciSize(argv);
          break;
        case 1:
          rowDelete(argv);
          break;
        case 2:
          niggerDelete(argv);
          break;
        default:
          exit(0);
          break;
      }
    }
    
  }else
    printf("Il file2 è piu grande \n");

  return 0;
}
