/*
  Creato il 07/04/2025 alle ore 16:23
  Si creino n thread e stamparne l'id uno per volta.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread>

void func()
{
  printf("sono un thread");
}


int main()
{
  printf("Sono il padre e sto per creare un nuovo thread \n");
  pthread_t *thread;
  pthread_create(thread,NULL,func,NULL);

}
