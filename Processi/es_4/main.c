/*
  Data creazione 16/04/2025 ore 09:03
  La traccia è nella directory
  Note:
  Ero indeciso se utilizzare semafori e quant'altro, però ho notato che nelle traccie di solito dice tutto ciò che va utilizzato, ad esempio utilizzare i semafori posix per x scopo...
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#define size 4500

pid_t p11;
pid_t p22;
pid_t father;
bool go = false;
int n;


//Gestore segnale usr1
void usr1Handler()
{
  printf("gestisco il segnale dispari\n");
  go = true;
}


int main(int argc,char **argv)
{
  int pa[2],pb[2];
  father = getpid();
  
  //Registro l'handler del segnale
  signal(SIGUSR1,usr1Handler);
  
  //in input deve essere passato n
  if(argc != 2) exit(-1);

  //inizializzazione
  n = atoi(argv[1]);
  pipe(pa);
  pipe(pb);
  int numbers[n];
  char *pari    = malloc(n * sizeof(char));
  char *dispari = malloc(n * sizeof(char));
  
  //Scrittura nella pipe degli n numeri
  for(int i = 0; i < n; i++)
  {
    char *buff = malloc( n * sizeof(char));
    sprintf(buff,"%d",i);
    strcat(buff," ");
    write(pa[1],buff,strlen(buff));
    free(buff);
  }
  
  //Crea il processo P11 e P22
  p11 = fork();
  if(getpid() == father) {p22 = fork();}
  
  //P11
  if(p11 == 0)
  {
    char buffer[size];
  
    //Chiudo i descrittori inutilizzati
    close(pa[1]);
    close(pb[0]);
    
    //Leggi i numeri
    read(pa[0],buffer,size);
    close(pa[0]);
    printf("Letto: %s \n",buffer);
    
    //Estrazione numeri
    char *number = strtok(buffer," ");
    int index = 0;
    
    while(number != NULL)
    {
      //Conversione char int
      int convertedNumber = atoi(number);
      numbers[index] = convertedNumber;
      printf("number = %d array = %d \n",convertedNumber,numbers[index]);
      
      //Se il numero è pari lo salvo nei pari altrimenti nei dispari
      if(convertedNumber % 2 == 0)
      {
        sprintf(pari,"%d",convertedNumber);
        strcat(pari," ");
        
        //Scrivo i numeri pari in pb
        write(pb[1],pari,strlen(pari));
      }else
      {
        //Salvo quelli dispari
        char *appoggio = malloc(n*sizeof(char));
        sprintf(appoggio,"%d",convertedNumber);
        strcat(appoggio," ");
        strcat(dispari,appoggio);
        printf("appoggio = %s dispari = %s \n",appoggio,dispari);
        free(appoggio);
      }
      
      //Successivo
      number = strtok(NULL," ");
      index++;
    }
    
    //Stampo pari e dispari
    printf("pari = %s dispari = %s \n",pari,dispari);
    
    //Aspetta di poter andare avanti quando ricevi sigusr1
    pause();
    
    printf("Procedo a scrivere i dispari \n");
    write(pb[1],dispari,strlen(dispari));
    printf("scritti %s \n", dispari);
    close(pb[1]);
    exit(3);
    
  }else if(getpid() == father)
  {
    //Il padre chiude i descrittori inutilizzati
    close(pa[0]);
    close(pa[1]);
    close(pb[1]);
    
  }
  
  //P22
  if(p22 == 0)
  {
    size_t I = n/2;
    int fd = open("out.txt",O_WRONLY | O_TRUNC);
    int fd2 = open("out2.txt",O_WRONLY | O_TRUNC);
    char temp[size];
    char temp2[size];
    
    //Preleva I <= N/2 interi da pb e li scrive su un file
    read(pb[0],temp,I);
    write(fd,temp,strlen(temp));
    
    //Invia segnale sigusr1 a P11
    //printf("Mando segnale a %d \n",p11);
    kill(p11,SIGUSR1);
    
    //Leggo e scrivo sull'altro file
    read(pb[0],temp2,size);
    write(fd2,temp2,strlen(temp2));
    read(pb[0],temp2,size);
    write(fd2,temp2,strlen(temp2));
    
    //Chiusura descrittori
    close(fd);
    close(fd2);
    close(pb[0]);
  }
  return 0;
}

