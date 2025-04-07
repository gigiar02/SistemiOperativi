/*
  Creato il 07/04/2025 alle ore 16:23
  Si creino n thread che stampano uno per volta "sono un thread"
  Il numero n è fornito in input.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>

void func(void * ch)
{
  printf("sono un thread \n");
}


int main(int argc, char *argv[])
{
  int n;
  n = atoi(argv[1]);
  pthread_t threadList[n];
  //Controllo gli argomenti passati
  if(argc < 2)
  {
    perror("Usage Error: too few arguments");
    return -1;
  }
  
  //Numero di thread da creare
  
  printf("Sono il padre e sto per creare %d thread \n",n);
  
  //Creazione thread
  for(int i = 0; i < n; i++)
  {
    //Crea i thread
    int res = pthread_create(&threadList[i],NULL,(void *)func,NULL);
    printf("res = %d i = %d \n",res,i);
  }
  
  //NB: La sleep l ho inserita solo per estetica nelle printf. Il programma ovviamente
  //funzionerebbe anche senza
  sleep(1);
  //Aspetta che abbiano finito
  for(int i = 0; i < n; i++)
  {
    printf("Aspetto che il thread %d abbia finito \n",i);
    pthread_join(threadList[i],NULL);
    printf("%d ha finito \n",i);
  }
  
  return 0;

}
