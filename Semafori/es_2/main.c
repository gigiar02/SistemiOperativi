/*
  Si progetti un programma in ambiente Linux che, impiegando  la  libreria  pthread,
   * crei  un  thread  che  estrae N volte ( con N passato da riga di comando )
   * un numero casuale compreso tra 0 e 10 e ne calcoli il fattoriale  ponendolo 
   * in  una  variabile  condivisa e  un  thread  che  stampi  a  video  il  fattoriale 
   * calcolato  N  volte prelevandolo dalla variabile condivisa.
   *
   * Per la sincronizzazione utilizzare i semafori con nome
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <semaphore.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #define wait sem_wait
 #define signal sem_post
 
 sem_t *produci;
 sem_t *consuma;
 int N;
 int glob = 0;
 int start = 0;
 
 void produttore(void * arg)
 {
  for(int i = 0; i < N; i++)
  {
    int value = rand() % 10;
    //printf("value %d \n",value);
    
    int save = value;
    int j = value - 1;
    while(j > 1)
    {
      //printf(" * value %d \n",value);
      value *= j;
      j-=1;
    }
    //printf("%d  %d  \n",save,value);
    wait(produci);
    start = save;
    glob = value;
    signal(consuma);
  }
 }
 
 void consumatore(void * arg)
 {
  for(int i = 0; i < N; i++)
  {
    wait(consuma);
    printf(" start: %d finale = %d \n",start,glob);
    start = 0;
    glob = 0;
    signal(produci);
  }
}
 
 int main(int argc, char **argv)
 {
    pthread_t tid[2];
    if(argc != 2){printf("Errore argc"); return 0;}
    N = atoi(argv[1]);
    sem_unlink("produttore");
    sem_unlink("consumatore");
    produci = sem_open("produttore",O_CREAT,999,1);
    consuma = sem_open("consumatore",O_CREAT,999,0);
    pthread_create(&tid[0],NULL,(void * ) &produttore,NULL);
    pthread_create(&tid[1],NULL,(void * ) &consumatore,NULL);
    
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
 }
