/*
Scrivere un programma in C che ( in ambiente Linux e utilizzando la libreria pthread ) crei 2 thread che eseguono
 * la funzione "incrementa" che a sua volta accede alle variabili glob.a e glob.b di una struttura dati condivisa glob e
 * ne incrementi il loro valore di 1 per 100 volte. Al termine, quando i due thread avranno terminato con gli 
 * incrementi, il thread principale stamperà a video i valori delle variabili test.a e test.b. Per la gestione della
 * sincronizzazione si utilizzi i mutex allocati dinamicamente.
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/stat.h>
 #include <pthread.h>
 
 #define lock pthread_mutex_lock
 #define unlock pthread_mutex_unlock
 struct glob
 {
  int a;
  int b;
 };
 
 struct glob test;
 pthread_mutex_t *mutex;
 
 
 void incrementa()
 {
  for(int i = 0; i < 100; i++)
  {
    //printf("Pre \n");
    lock(mutex);
    //printf("Post \n");
    test.a+=1;
    test.b+=1;
    unlock(mutex);
  }
 }
 
 void thread(void * arg)
 {
  incrementa();
 }
 
 int main()
 {
    test.a = 0;
    test.b = 0;
    //printf("Inizio \n");
    pthread_mutexattr_t *attr;
    mutex = malloc(sizeof(pthread_mutex_t));
    attr = malloc(sizeof(pthread_mutexattr_t));
    pthread_mutexattr_init(attr);
   
    pthread_mutex_init(mutex,attr);
    printf("Mutex inizializzati \n");
    pthread_t id[2];
    
    pthread_create(&id[0],NULL,(void *) &thread,NULL);
    pthread_create(&id[1],NULL,(void *) &thread,NULL);
    
    pthread_join(id[0],NULL);
    pthread_join(id[1],NULL);
    
    printf("a = %d b = %d \n",test.a,test.b);
    pthread_mutex_destroy(mutex);
    
    return 0;
 }
