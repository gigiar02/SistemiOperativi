/*
  Creato il 07/04/2025 alle ore 09:47
  La traccia è nella directory
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#define SIZE 7500
char *buff;
//Si verifica se l'utente digita ctrl + z
void interruptHandler()
{
  int num;
  int result = 1;
  
  printf("Inserisci un numero compreso tra 1 e 20: \n");
  scanf("%d",&num);
  if(num < 1 || num > 20) return;
  
  //Calcolo fattoriale e stampa del risultato
  for(int i = num; i > 1; i--)
  {
    result *= i;
  }
  printf("Il fattoriale di %d è %d \n",num,result);
}

//Gestisce il segnale usr1
void usr1Handler()
{
  int fd,pos;
  size_t size = SIZE;
  
  //Apre il file in sola lettura e alloca memoria per poterne leggere il contenuto
  fd = open("prova.txt",O_RDONLY);
  if(fd < 0) return;
  buff = malloc(size);
  
  pos = lseek(fd,-1,SEEK_END);
  while(pos > 0)
  {
    char appoggio[SIZE];
    read(fd,appoggio,1);
    pos = lseek(fd,-2,SEEK_CUR);
    strcat(buff,appoggio);
  }
  printf("letto = %s \n",buff);
  close(fd);
}

//Scrive il contenuto dell'heap nel file prova1.txt
void usr2Handler()
{
  int fd;
  char read;
  
  //Apre il file in scrittura
  fd = open("prova1.txt",O_CREAT | O_TRUNC | O_WRONLY,S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP);
  if(fd < 0) return;
  
  //Scrivo il contenuto dell'heap e chiudo il file
  write(fd,buff,strlen(buff));
  close(fd);
  printf("Contenuto dell'heap scritto \n");
}

int main()
{
  //Registra la gestione dei tre segnali
  signal(SIGINT,interruptHandler);
  signal(SIGUSR1,usr1Handler);
  signal(SIGUSR2,usr2Handler);
  
  printf("PID = %d \n",getpid());
  //Aspetta un segnale
  while(true)
  {
  
  }
  
}
