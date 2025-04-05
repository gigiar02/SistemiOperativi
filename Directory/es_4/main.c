/*
    Creato il 5/04/2025 alle ore 19:37
    La traccia è nella directory corrente
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#define BUFF 4500
//Chiede all'utente di inserire un prezo e lo maggiora del 30%
void maggiora()
{
  int price;
  int majority;
  
  //Inserisci numero
  printf("Inserisci un prezzo: \n");
  scanf("%d",&price);
  majority = (price/100 * 30) + price;
  printf("Il prezzo maggiorato è: %d \n",majority);
  
}

//Conta e sostituisce tutte le parole "oggi" con "Domani" il risultato è posto nel file OUT.
int conta()
{
  int out,fl1;
  int count = 0;
  char *token;
  char riga[BUFF];
  char content[BUFF];
  char buff[BUFF];
  
  
  if((fl1 = open("file1.txt",O_RDONLY)) < 0) return -5;
  if((out = open("OUT.txt",O_WRONLY))   < 0) return -4;
  
  read(fl1,content,BUFF);
  //Prendo una parola alla volta
  token = strtok(content," ");
  while(token != NULL)
  {
    printf("parola: %s \n",token);
    if(strncmp(token,"oggi",4) == 0)   strcat(buff,"DOMANI");
    if(strncmp(token,"oggi\n",6) == 0) strcat(buff,"DOMANI\n");
    if(strncmp(token,"oggi",4) != 0 && strncmp(token,"oggi\n",6) != 0) strcat(buff,token);
    strcat(buff," ");
    token = strtok(NULL," ");
  }
  
  printf("%s \n",buff);
  write(out,buff,strlen(buff));
  close(out);
}

int main(int argc, char *argv[])
{
  int selection;
  
  //Permetti all'utente di intraprendere una delle possibili azioni
  while(1)
  {
    //Elaboro scelta
    printf(" Scegli l' operazione da eseguire: \n");
    printf("[1] MAGGIORA \n[2] CONTA \n[3] exit \n");
    scanf("%d",&selection);
    switch(selection)
    {
      case 1:
        maggiora();
        break;
      case 2:
        int res = conta();
        if(res == -5 || res == -4) return -1;
        
        break;
      case 3:
        exit(1);
      default:
        exit(1);
    }   
  }
}

