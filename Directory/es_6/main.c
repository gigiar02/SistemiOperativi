/*
  Creato in data 22/04/2025
  La traccia è nella directory
  
  Codice disastroso post pasquetta con 0 voglia
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#define size 4500


//Conta le occorrenze della parola "directory" all'interno del file passato in input e le restituisce
int contaOccorrenze(char *name)
{
  int occorrenze = 0;
  int fd = open(name,O_RDONLY);
  char buff[size];
  char *target = "directory";
  char riga;
  char *word;
  int j;
  
  if(fd < 0) return -1;
  
  //Lettura
  read(fd,buff,size);
  
    //Prendo il token
  word = strtok(buff," ");
  while(word)
  {
    printf("iterazione init \n");
    printf("%s \n",word);
    char app[size];
    int j = 0;
    //Verifica la presenza della parola
    for(int i = 0; i < strlen(word);i++)
    {
       printf("%c ",word[i]);
      
       //Se si va a capo o c'è uno spazio
       if(word[i] == '\n') riga++;
       if(word[i] == '\n' || word[i] == ' ') continue;
       
       //hai trovato una lettera
      if(word[i] == target[j])
      {
        printf("corrispondenza \n");
        j++;
      }else
      {
        printf("nessuna corrispondenza %c %c  \n",word[i],target[j]);
        //Le due parole non sono uguali
        j = 0;
      }
      
      if(word[i] == '\n' || word[i] == ' ' || j == strlen(target)){occorrenze++; j = 0; printf("occorrenza trovata \n");}
    }
    
    word = strtok(NULL," ");
  }
  
  return occorrenze;
}


//Trova la riga a cui si trova la parola directory
int trovaRiga(char *name)
{
  int fd = open(name,O_RDONLY);
  char buff[size];
  char *target = "directory";
  char riga;
  char *word;
  int j;
  
  if(fd < 0) return -1;
  
  //Lettura
  read(fd,buff,size);
  
    //Prendo il token
  word = strtok(buff," ");
  while(word)
  {
    printf("iterazione init \n");
    printf("%s \n",word);
    char app[size];
    int j = 0;
    //Verifica la presenza della parola
    for(int i = 0; i < strlen(word);i++)
    {
       printf("%c ",word[i]);
      
       //Se si va a capo o c'è uno spazio
       if(word[i] == '\n') riga++;
       if(word[i] == '\n' || word[i] == ' ') continue;
       
       //hai trovato una lettera
      if(word[i] == target[j])
      {
        printf("corrispondenza \n");
        j++;
      }else
      {
        printf("nessuna corrispondenza %c %c  \n",word[i],target[j]);
        //Le due parole non sono uguali
        j = 0;
      }
      
      if(word[i] == '\n' || word[i] == ' ' || j == strlen(target)){printf("occorrenza trovata \n"); return riga;}
    }
    
    word = strtok(NULL," ");
  }
}


//Stampa il contenuto del file
void stampaFile(char *name)
{
  char row[size];
  int rows = 0;
  int frequenza;
  
  frequenza = contaOccorrenze(name);
  FILE *file = fopen(name,"r");
  printf("frequenza = %d \n",frequenza);
  
  while(fgets(row,size,file))
  {
    rows++;
    printf("%s \n",row);
    if(frequenza > 2 && rows == 2) break;
    
  }
}

int main(int argc, char **argv)
{
  int scelta;
  
  //Controllo argomenti
  if(argc != 2)
  {
    printf("Passare il nome del file come parametro in ingresso \n");
    return -1;
  }
  
  //Scelta
  while(true)
  {
    printf("MENU: \n");
    printf("1: frequenza della parola directory \n");
    printf("2: numero di riga contenente la parola directory \n");
    printf("3: stampa le prime due righe se il numero di ripetizioni è maggiore di due altrimenti tutto il contenuto \n");
    scanf("%d",&scelta);
    
    switch(scelta)
    {
      case 1:
        int num = contaOccorrenze(argv[1]);
        printf("La parola directory si ripete %d volte \n",num);
        break;
      case 2:
        int riga = trovaRiga(argv[1]);
        printf("La riga a cui ho trovato l'occorrenza è %d",riga);
        break;
      case 3:
        stampaFile(argv[1]);
        break;
    }
    
    
    
  }
}

