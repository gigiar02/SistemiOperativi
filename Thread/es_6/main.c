/*
  Creato il 15/04/2025 alle ore 11:44
  La traccia è nella directory
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <pthread.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#define wait sem_wait
#define signal sem_post
#define row 4500
int n;
int fd;

//Scrittore
void writer(void * arg)
{
  //Apertura semafori
  sem_t *full = sem_open("full",O_EXCL);
  sem_t *empty =  sem_open("empty",O_EXCL);
  
  //Numeri da 1 a N
  for(int j = 1; j <= n; j++)
  {
     //Lo scrittore aspetta che la posizione sia vuota
    wait(empty);
    
    //Apertura file
    fd = open("out.txt",O_WRONLY);
    printf("Sto aspettando di poter scrivere..\n");
    
    //Stampa nel buffer il valore corrente e scrivilo nel file
    char *buff = malloc(row *sizeof(char));
    sprintf(buff,"%d",j);
    printf("Ho scritto %s  strlen = %d \n",buff,strlen(buff));
    write(fd,buff,strlen(buff));
    printf("Ho scritto all'interno del buffer..\n \n \n \n");
    
    //Il buffer ora è pieno
    free(buff);
    close(fd);
    
    signal(full);
  }
}


//Lettore
void reader(void * arg)
{
  //Apertura semafori
  sem_t *full =  sem_open("full",O_EXCL);
  sem_t *empty = sem_open("empty",O_EXCL);
  sem_t *end =   sem_open("end",O_EXCL);
  
  //Numeri da 1 a N
  for(int j = 1; j <= n; j++)
  {
    //Aspetta di poter accedere al file
    wait(full);
    
    //Apertura file
    fd = open("out.txt",O_RDONLY);
    printf("descriptor = %d \n",fd);
    printf("Sto aspettando di poter leggere..\n");
    
    //Leggi da file
    char buff[row];
    ssize_t letto = read(fd,buff,row);
    printf("Letto: %s num = %d \n",buff,letto);
    int number = atoi(buff);
    printf("Ho letto la posizione corrente %d..\n \n \n \n",number);
  
    //Reset con O_TRUNC
    close(fd);
    fd = open("out.txt",O_WRONLY | O_TRUNC);
    close(fd);
    
    signal(empty);
  }
  
  //Sblocco il thread che sta aspettando per poter stampara il messaggio di fine
  signal(end);
}


//Aspetta la lettura di tutti gli n numeri per stampare un messaggio
void endPrint(void * arg)
{
  sem_t *end = sem_open("end",O_EXCL);
  
  //Aspetta di poter stampare
  wait(end);
  int tid = gettid();
  printf("Finito con tid = %d \n",tid);
}


int main(int argc, char **argv)
{
  //I semafori posix sono salvati in memoria fino al reboot, per precauzione è necessario fare l' unlink in modo tale da crearli di sicuro.
  sem_unlink("full");
  sem_unlink("empty");
  sem_unlink("end");
  
  //Creazione semafori
  sem_t *full  = sem_open("full",O_CREAT,0666,0);
  sem_t *empty = sem_open("empty",O_CREAT,0666,1);
  sem_t *end   = sem_open("end",O_CREAT,0666,0);
  
  //Controllo argomento passato in input
  if(argc != 2) exit(2);
  n = atoi(argv[1]);
  if(n < 13 || n > 37) exit(3);
  
  //Creazione dei thread
  pthread_t tid[3];
  pthread_create(&tid[0],NULL,&writer,  (void *) NULL);
  pthread_create(&tid[1],NULL,&reader,  (void *) NULL);
  pthread_create(&tid[2],NULL,&endPrint,(void *) tid[2]);
  
  //Aspetto la terminazione dei thread
  for(int i = 0; i < 3; i++)
  {
    pthread_join(tid[i],NULL);
  }
  
  return 0;
}
