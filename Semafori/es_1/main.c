/*
  Data creazione: 17/04/2025 ore 08:20
  La traccia è nella directory
  Do la precedenza allo scrittore
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>

//Variabili globali
#define lock   pthread_mutex_lock
#define unlock pthread_mutex_unlock
#define wait   sem_wait
#define signal sem_post
#define size 4500
pthread_mutex_t mutex;
int n;


//Thread scrittore
void t_Write(void * argc)
{
  //Inizializzazione
  int fd;
  sem_t *writer = sem_open("writer",O_EXCL);
  sem_t *reader = sem_open("reader",O_EXCL);
  if(!writer || !reader) perror("Errore apertura ");
  for(int i = 1; i <= n; i++)
  {
    //Aspetto che il lettore abbia finito
    wait(reader);
    printf("Inizio scrittura \n");
    
    //Apro il file in scrittura e scrivo l'iesimo numero nella terza posizione del file
    fd = open("out.txt",O_WRONLY);
    char *number   = malloc(n * sizeof(char));
    char *appoggio = malloc(n * sizeof(char));
    sprintf(number,"%d",i);
    strcat(appoggio,"  ");
    strcat(appoggio,number);
    printf("scrivo %s lunghezza = %d \n",appoggio,strlen(appoggio));
    write(fd,appoggio,strlen(appoggio));
    
    //Chiudo il descrittore di file per salvaere e comunico al lettore che lo scrittore ha finito
    close(fd);
    free(number);
    free(appoggio);
    printf("Fine scrittura \n\n\n");
    signal(writer);
  }
}


//Thread lettore
void t_Read(void * argc)
{
  //Inizializzazione
  int fd;
  sem_t *writer = sem_open("writer",O_EXCL);
  sem_t *reader = sem_open("reader",O_EXCL);
  
  for(int i = 1; i <= n; i++)
  {
    //Aspetta che lo scrittore abbia finito
    wait(writer);
    printf("Inizio Lettura \n");
    
    //Apri il file in lettura e leggi nella terza posizione
    fd = open("out.txt",O_RDONLY);
    char number[size];
    lseek(fd,2,SEEK_SET);
    read(fd,number,size);
    
    //Chiusura descrittore e reset del file
    printf("ho letto %s \n",number);
    close(fd);
    fd = open("out.txt",O_WRONLY | O_TRUNC);
    close(fd);
    printf("Fine Lettura \n\n\n");
    //Comunico allo scrittore che il lettore ha finito
    signal(reader);
  }
}


int main(int argc,char **argv)
{
  //Controllo argomenti
  if(argc != 2) return -1;
  n = atoi(argv[1]);
  if(n < 13 || n > 37) return -2;
  pthread_t tid[2];
  
  //Apertura sicura dei semafori
  sem_unlink("writer");
  sem_unlink("reader");
  sem_t *writer = sem_open("writer",O_CREAT,0666,0);
  sem_t *reader = sem_open("reader",O_CREAT,0666,1);
  printf("i semafori sono stati creati \n");
  
  //Creazione dei due thread
  pthread_create(&tid[0],NULL,(void *) &t_Write,(void *) NULL);
  pthread_create(&tid[1],NULL,(void *) &t_Read,(void *)  NULL);
  printf("Creazione andata a buon fine \n");
  
  //Aspetto la loro terminazione
  pthread_join(tid[0],NULL);
  pthread_join(tid[1],NULL);
  
  return 0;
}
