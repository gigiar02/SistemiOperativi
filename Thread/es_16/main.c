/*
  Scrivere un programma C e Posix che prende da riga di comando N interi
  compresi tra 5 e 20. Il valore di N è constante ed indicato nel sorgente.
  Il programma avvia N thread che hanno il seguente comportamento:
  a) Ogni thread va in sospensione ( invocando la funzione sleep() ) per un numero
  di secondi pari al valore del corrispondente parametro e poi stampa il suo indice
  b) Alla fine del periodo di attesa ( sleep ), ogni thread stampa un messaggio: "Thread #: svegliato!".
  c) Tutti i thread si sincronizzano tra di loro ( utilizzando i semafori basati su memoria ).
  d) dopo aver atteso il termine di tutti gli altri thread, ciascun thread scrive sullo schermo
  che ha terminato ( "Thread #: terminato..." ).
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <semaphore.h>
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
#define wait   sem_wait
#define signal sem_post

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct msg
{
  int secondi;
  int id;
};
sem_t *sem;
int N = 5;
int numRisvegliati = 0;
struct msg *msgV;

void waitTh(void * arg)
{
  int id = (int) arg;
  printf("Secondi = %d \n",msgV[id].secondi);
  sleep(msgV[id].secondi);
  printf("Stampo il mio indice: %d  thread svegliato \n",id);
  lock(&mutex);
  numRisvegliati += 1;
  if(numRisvegliati == N) {printf("Ultimo \n "); signal(sem);}
  unlock(&mutex);
  
  wait(sem);
  signal(sem);
  printf("Terminato %d \n",id);
}

int main(int argc, char **argv)
{
  pthread_t tid[N];
  
  //Inizializzazione msgv
  msgV = malloc(sizeof(struct msg) * N);
  for(int i = 0; i < N; i++)
  {
    printf("[%d] Inserisci un numero compreso tra 5 e 20 \n",i);
    scanf("%d",&msgV[i].secondi);
    if(msgV[i].secondi < 5 || msgV[i].secondi > 20){i = i -1; continue;}
    
  }
  
  sem_unlink("sem");
  sem = sem_open("sem",O_CREAT,999,0);
  for(int i = 0; i < N; i++)
  {
    pthread_create(&tid[i],NULL,(void *) &waitTh,(void *) i);
  }
  
  for(int i = 0; i < N; i++)
  {
    pthread_join(tid[i],NULL);
  }
}
