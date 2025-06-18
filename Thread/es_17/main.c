/*    
    Scrivere un programma C che crea M thread produttori e N thread consumatori (con M=2*N), con M ed N presi come
    parametro da riga di comando. Tutti i thread condividono una variabile intera. Ogni thread produttore incrementa di due unità
    la variabile condivisa se e solo se il valore della stessa è inferiore a 100. Ogni thread consumatore decrementa di due unità la
    variabile condivisa se e solo se il valore della stessa è superiore a 25. Tutti i thread, dopo l’operazione sulla variabile condivisa
    (di incremento o di decremento) dormono per 2 secondi. Per implementare la sincronizzazione utilizzare i semafori Posix basati
    su nome.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>


#define wait sem_wait
#define signal sem_post

sem_t *semcs;
sem_t *produci;
sem_t *consuma;

int glob = 0;
int val = 0;

void produttore(void * argv)
{
  int id = (int) argv;
  for(int i = 0; i < 400; i++)
  {
  wait(produci);
  wait(semcs);
  glob++;
  printf("%d prod, il valore di glob è %d \n",id,glob);
  if(glob - val > 25)
  {
    val+=2;
    signal(consuma);
  }
  signal(semcs);
  //sleep(1);
  }
}


void consumatore(void * argv)
{
  int id = (int) argv;
  for(int i = 0; i < 200; i++)
  {
  wait(consuma);
  wait(semcs);
  glob-=2;
  val-=2;
  printf("%d cons, il valore di glob è %d val = %d \n",id,glob,val);
  if(glob < 100)
  {
    signal(produci);
  }
  signal(semcs);
  sleep(2);
  }
}


int main(int argc,char **argv)
{
  if(argc != 2){printf("Errore argc "); return 0;}
  int n = atoi(argv[1]);
  int m = 2*n;
  pthread_t p[m];
  pthread_t c[n];
  sem_unlink("produci");
  sem_unlink("consuma");
  sem_unlink("semcs");
  produci = sem_open("produci",O_CREAT,999,100);
  consuma = sem_open("consuma",O_CREAT,999,0);
  semcs = sem_open("semcs",O_CREAT,999,1);
  for(int i = 0; i < m; i++)
  {
    pthread_create(&p[i],NULL,(void *) &produttore,(void *) i);
  }
  
  for(int i = 0; i < n; i++)
  {
    pthread_create(&c[i],NULL,(void *) &consumatore,(void *) i);
  }
  
  int num = 0;
  int i = 0;
  int j = 0;
  while(num < n+m)
  {
    if(i < n) {pthread_join(c[i],NULL); i+=1;}
    if(j < m) {pthread_join(p[j],NULL); j+=1;}
    num +=1;
  }
  
  
}
